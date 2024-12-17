#include <iostream>
#include <iomanip>
#include "order.h"
#include <fstream>
#include <windows.h>
using namespace std;

static int num_ords = 0;
static int index = 0;

void menu_orders(int* opt, vector<Client>& lst_clients, vector<Book>& books, vector<Order>& lst_orders) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    do {
        cout << left;
        cout << setw(20) << "\n --- УПРАВЛЕНИЕ ЗАКАЗАМИ ---" << endl;
        cout << "\nВыберите вариант: [1-3]: " << endl;
        cout << "[1]. Добавить заказ" << endl;
        cout << "[2]. Показать заказы" << endl;
        cout << "[3]. Выход" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Введите вариант: ";
        cin >> *opt;

        switch (*opt) {
        case 1:
            lst_orders.emplace_back();
            insert_order(lst_orders.back(), lst_clients, books);
            break;
        case 2:
            print_list_orders(lst_orders);
            break;
        case 3:
            cout << "Возвращаемся в главное меню..." << endl;
            break;
        default:
            cout << "\nНедопустимый вариант" << endl;
            break;
        }

    } while (*opt != 3);
}

void insert_order(Order& ord, vector<Client>& lst_clients, vector<Book>& books) {
    string client_name;
    char cont;

    cout << "\n*** Новый заказ ***" << endl;
    ord.code = ++index;

    cout << "\nВведите имя клиента: ";
    cin.ignore();
    getline(cin, client_name);

    int pos = -1;
    for (size_t i = 0; i < lst_clients.size(); ++i) {
        if (lst_clients[i].name == client_name) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        ord.client = lst_clients[pos];
    }
    else {
        cout << "Клиент с именем \"" << client_name << "\" не найден. Заказ отменён." << endl;
        return;
    }

    do {
        if (ord.details.size() < MAX) {
            ord.details.emplace_back();
            insert_order_detail(ord.details.back(), books);
            ord.totalAmount += ord.details.back().subtotal;
        }
        else {
            cout << "\nДостигнут лимит товаров в заказе!" << endl;
            break;
        }

        cout << "Добавить ещё товар? (д/н): ";
        cin >> cont;
    } while (cont == 'д' || cont == 'Д');

    ord.client.salary -= ord.totalAmount;
    num_ords++;
}


void insert_order_detail(OrderDetail& od, vector<Book>& books) {
    string search_prod;
    int pos;

    cout << "\n*** Новый элемент заказа ***" << endl;
    cout << "\nКнига: ";
    cin.ignore();
    getline(cin, search_prod);
    pos = search_Book(search_prod, books);

    if (pos == -1) {
        cout << "Книга не найдена!" << endl;
        return;
    }

    Book& selectedBook = books[pos];

    do {
        cout << "Количество: ";
        cin >> od.quantity;
        if (od.quantity > selectedBook.stock) {
            cout << "На складе недостаточно товара!" << endl;
        }
    } while (od.quantity > selectedBook.stock);

    od.book = selectedBook;
    od.subtotal = od.quantity * selectedBook.price;
    selectedBook.stock -= od.quantity;
}

void print_order_to_file(const Order& ord, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << " для записи." << endl;
        return;
    }

    file << "Номер заказа: " << ord.code << endl;
    file << "Клиент: " << ord.client.name << endl;
    file << "-------------------------------------------------------------" << endl;
    file << left;
    file << setw(10) << "№" << setw(15) << "Книга" << setw(15) << "Цена за ед."
        << setw(10) << "Кол-во" << setw(10) << "Сумма" << endl;
    file << "-------------------------------------------------------------" << endl;

    for (size_t i = 0; i < ord.details.size(); ++i) {
        file << setw(10) << (i + 1)
            << setw(15) << ord.details[i].book.title
            << setw(15) << ord.details[i].book.price
            << setw(10) << ord.details[i].quantity
            << setw(10) << ord.details[i].subtotal << endl;
    }

    file << "\nИтого: " << ord.totalAmount << endl << endl;

    file.close();
    cout << "Данные заказа успешно записаны в файл: " << filename << endl;
}

void print_list_orders(const vector<Order>& lst_orders) {
    cout << "\n*** Список заказов ***" << endl;

    for (const auto& ord : lst_orders) {
        print_order(ord); // Выводим заказ в терминал
        print_order_to_file(ord, "orders.txt"); // Записываем заказ в файл
    }

    cout << "Все заказы записаны в файл: orders.txt" << endl;
}

void print_order(const Order& ord) {
    print_order_to_file(ord, "orders.txt");;
    cout << "Номер заказа: " << ord.code << endl;
    cout << "Клиент: " << ord.client.name << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << left;
    cout << setw(10) << "№" << setw(15) << "Книга" << setw(15) << "Цена за ед."
        << setw(10) << "Кол-во" << setw(10) << "Сумма" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (size_t i = 0; i < ord.details.size(); ++i) {
        cout << setw(10) << (i + 1)
            << setw(15) << ord.details[i].book.title
            << setw(15) << ord.details[i].book.price
            << setw(10) << ord.details[i].quantity
            << setw(10) << ord.details[i].subtotal << endl;
    }

    cout << "\nИтого: " << ord.totalAmount << endl << endl;
}


