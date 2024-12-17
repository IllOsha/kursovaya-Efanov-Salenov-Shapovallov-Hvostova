#include <iostream>
#include <cstring>
#include <vector>
#include "client.h"
#include "product.h"
#include "order.h"
#include <windows.h>
using namespace std;

void menu_master(int* opt);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int opt;
    char cont;
    vector<Client> lst_clients;
    vector<Book> books;
    vector<Order> lst_orders;

    do {
        menu_master(&opt);

        switch (opt) {
        case 1:
            menu_clients(&opt, lst_clients);
            break;
        case 2:
            menu_Books(&opt, books);
            break;
        case 3:     // orders
            menu_orders(&opt, lst_clients, books, lst_orders);
            break;
        default:
            cout << "\nНедопустимый вариант" << endl;
            break;
        }

        cout << "\nВы хотите продолжить? [д/н]: ";
        cin >> cont;
    } while (cont == 'д' || cont == 'Д');

    cout << "Программа завершена!" << endl;

    return 0;
}

void menu_master(int* opt) {
    cout << "-----------------------------------------------" << endl;
    cout << "*** СИСТЕМА ПРОДАЖ КНИГ ***" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "\nВыберите вариант из [1-3] согласно меню:" << endl;
    cout << "[1]. Управление клиентами" << endl;
    cout << "[2]. Управление книгами" << endl;
    cout << "[3]. Управление заказами" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Введите вариант: ";
    cin >> *opt;
    cout << endl;
}
