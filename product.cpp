#include <iostream>
#include <cstring>
#include <iomanip>
#include "product.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <stdexcept>
using namespace std;

static int num_prods = 0;
static int index = 0;

Category intToCategory(int cat) {
    switch (cat) {
    case 0: return Category::Fantasy;
    case 1: return Category::Fantastic;
    case 2: return Category::Romance;
    case 3: return Category::History;
    default: throw invalid_argument("Неверная категория");
    }
}

string categoryToString(Category category) {
    switch (category) {
    case Category::Fantasy: return "Фэнтези";
    case Category::Fantastic: return "Фантастика";
    case Category::Romance: return "Роман";
    case Category::History: return "История";
    default: return "Неизвестно";
    }
}

void addBook(vector<Book>& books) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Book newBook;
    cout << "Введите данные книги:\n";
    newBook.code = books.empty() ? 1 : books.back().code + 1;
    cin.ignore();

    do {
        cout << "Автор (не более 40 символов): ";
        getline(cin, newBook.author);
        if (newBook.author.length() > 40) {
            cout << "Ошибка: Длина имени автора превышает 40 символов.\n";
        }
    } while (newBook.author.length() > 40);

    do {
        cout << "Название книги (не более 40 символов): ";
        getline(cin, newBook.title);
        if (newBook.title.length() > 40) {
            cout << "Ошибка: Длина названия превышает 40 символов.\n";
        }
    } while (newBook.title.length() > 40);

    cout << "Количество на складе: ";
    cin >> newBook.stock;

    do {
        cout << "Цена (от 100 до 50000): ";
        cin >> newBook.price;
        if (newBook.price < 100 || newBook.price > 50000) {
            cout << "Ошибка: Цена должна быть в диапазоне от 100 до 50000.\n";
        }
    } while (newBook.price < 100 || newBook.price > 50000);

    do {
        cout << "Год выпуска (не меньше 2000): ";
        cin >> newBook.year;
        if (newBook.year < 2000) {
            cout << "Ошибка: Год выпуска должен быть не меньше 2000.\n";
        }
    } while (newBook.year < 2000);

    int cat;
    cout << "Категория (0-Фэнтези, 1-Фантастика, 2-Роман, 3-История): ";
    cin >> cat;
    newBook.category = intToCategory(cat);

    books.push_back(newBook);

    ofstream outFile("data/book.txt", ios::app);
    outFile << newBook.code << "," << newBook.author << "," << newBook.title << "," << newBook.stock
        << "," << newBook.price << "," << newBook.year << "," << cat << "\n";
    outFile.close();

    cout << "Книга успешно добавлена.\n";
}

void saveBooksToFile(const vector<Book>& books, const string& filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << " для записи.\n";
        return;
    }

    outFile << left << setw(5) << "Код" << setw(20) << "Автор" << setw(20) << "Название" << setw(10)
        << "Склад" << setw(10) << "Цена" << setw(6) << "Год" << "Категория\n";
    outFile << string(75, '-') << "\n";

    for (const auto& book : books) {
        outFile << left << setw(5) << book.code
            << setw(20) << book.author
            << setw(20) << book.title
            << setw(10) << book.stock
            << setw(10) << fixed << setprecision(2) << book.price
            << setw(6) << book.year
            << categoryToString(book.category) << "\n";
    }

    outFile.close();
    cout << "\nДанные книг успешно сохранены в файл: " << filename << "\n";
}

void displayBooks(const vector<Book>& books) {
    cout << left << setw(5) << "Код" << setw(20) << "Автор" << setw(20) << "Название" << setw(10)
        << "Склад" << setw(10) << "Цена" << setw(6) << "Год" << "Категория\n";
    cout << string(75, '-') << "\n";

    for (const auto& book : books) {
        cout << left << setw(5) << book.code
            << setw(20) << book.author
            << setw(20) << book.title
            << setw(10) << book.stock
            << setw(10) << fixed << setprecision(2) << book.price
            << setw(6) << book.year
            << categoryToString(book.category) << "\n";
    }

    saveBooksToFile(books, "books.txt");
}


int search_Book(const string& search_title, const vector<Book>& books) {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].title == search_title) {
            return i;
        }
    }
    return -1;
}

void update_Book(const string& search_title, vector<Book>& books) {
    int pos = search_Book(search_title, books);
    if (pos == -1) {
        cout << "\nКнига не найдена!\n";
        return;
    }

    cout << "Обновление данных книги: " << books[pos].title << "\n";

    cout << "Новое количество на складе: ";
    cin >> books[pos].stock;

    do {
        cout << "Новая цена (от 100 до 50000): ";
        cin >> books[pos].price;
        if (books[pos].price < 100 || books[pos].price > 50000) {
            cout << "Ошибка: Цена должна быть в диапазоне от 100 до 50000.\n";
        }
    } while (books[pos].price < 100 || books[pos].price > 50000);

    cout << "Книга успешно обновлена.\n";
}

void delete_Book(const string& search_title, vector<Book>& books) {
    int pos = search_Book(search_title, books);
    if (pos == -1) {
        cout << "\nКнига не найдена!\n";
        return;
    }

    books.erase(books.begin() + pos);
    cout << "\nКнига успешно удалена.\n";
}

void sort_by_prices(vector<Book>& books) {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.price < b.price;
        });
}

int get_cheapest_Book(const vector<Book>& books) {
    if (books.empty()) return -1;

    return distance(books.begin(), min_element(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.price < b.price;
        }));
}

void menu_Books(int* opt, vector<Book>& books) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    do {
        cout << left;
        cout << setw(20) << "\n --- УПРАВЛЕНИЕ КНИГАМИ ---" << endl;
        cout << "\nВыберите вариант из [1-8] согласно меню:\n";
        cout << "[1]. Вставить книгу\n";
        cout << "[2]. Показать список книг\n";
        cout << "[3]. Найти книгу\n";
        cout << "[4]. Отсортировать по цене\n";
        cout << "[5]. Обновить данные книги\n";
        cout << "[6]. Удалить книгу\n";
        cout << "[7]. Найти книгу с минимальной ценой\n";
        cout << "[8]. Выйти\n";
        cout << "------------------------------------------------\n";
        cout << "Введите вариант: ";
        cin >> *opt;

        switch (*opt) {
        case 1:
            addBook(books);
            break;
        case 2:
            displayBooks(books);
            break;
        case 3: {
            string search_title;
            cout << "\nВведите название книги для поиска: ";
            cin.ignore();
            getline(cin, search_title);

            int pos = search_Book(search_title, books);

            if (pos != -1) {
                cout << "\nНайденная книга: \n";
                displayBooks({ books[pos] });
            }
            else {
                cout << "\nКнига не найдена.\n";
            }
            break;
        }
        case 4:
            sort_by_prices(books);
            cout << "\nКниги отсортированы по цене.\n";
            break;
        case 5: {
            string search_title;
            cout << "\nВведите название книги для обновления: ";
            cin.ignore();
            getline(cin, search_title);

            update_Book(search_title, books);
            break;
        }
        case 6: {
            string search_title;
            cout << "\nВведите название книги для удаления: ";
            cin.ignore();
            getline(cin, search_title);

            delete_Book(search_title, books);
            break;
        }
        case 7: {
            int pos = get_cheapest_Book(books);
            if (pos != -1) {
                cout << "\nКнига с минимальной ценой: \n";
                displayBooks({ books[pos] });
            }
            else {
                cout << "\nНет доступных книг.\n";
            }
            break;
        }
        case 8:
            cout << "Выход в главное меню...\n";
            break;
        default:
            cout << "\nНеверный вариант.\n";
        }
    } while (*opt != 8);
}
