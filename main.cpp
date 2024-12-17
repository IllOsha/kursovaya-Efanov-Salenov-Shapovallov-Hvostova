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
            cout << "\n������������ �������" << endl;
            break;
        }

        cout << "\n�� ������ ����������? [�/�]: ";
        cin >> cont;
    } while (cont == '�' || cont == '�');

    cout << "��������� ���������!" << endl;

    return 0;
}

void menu_master(int* opt) {
    cout << "-----------------------------------------------" << endl;
    cout << "*** ������� ������ ���� ***" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "\n�������� ������� �� [1-3] �������� ����:" << endl;
    cout << "[1]. ���������� ���������" << endl;
    cout << "[2]. ���������� �������" << endl;
    cout << "[3]. ���������� ��������" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "������� �������: ";
    cin >> *opt;
    cout << endl;
}
