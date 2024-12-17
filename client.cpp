#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include "client.h"
#include <fstream>
#include <windows.h>
using namespace std;

void menu_clients(int* opt, vector<Client>& lst_clients) {
    int pos;
    string search_name;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    do {
        cout << left;
        cout << setw(20) << "\n --- ���������� ��������� ---" << endl;
        cout << "\n�������� ������� �� [1-8] :" << endl;
        cout << "[1]. �������� �������" << endl;
        cout << "[2]. ��������� ������ ��������" << endl;
        cout << "[3]. ����� �������" << endl;
        cout << "[4]. ����������� � ���������� �������" << endl;
        cout << "[5]. ���������� �������" << endl;
        cout << "[6]. ������� �������" << endl;
        cout << "[7]. ������� ������� � ����� ������� ���������" << endl;
        cout << "[8]. �����" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "������� �������: ";
        cin >> *opt;

        switch (*opt) {
        case 1:
            lst_clients.emplace_back();
            insert_client(lst_clients.back(), lst_clients);
            break;
        case 2:
            print_lst_clients(lst_clients);
            break;
        case 3:
            cout << "\n������� ��� ��� ������: ";
            cin.ignore();
            getline(cin, search_name);
            pos = search_client(search_name, lst_clients);

            if (pos != -1) {
                cout << "\n������ ������:" << endl;
                print_client(lst_clients[pos]);
            }
            else {
                cout << "\n������ �� ������" << endl;
            }
            break;
        case 4:
            cout << "\n������ ��������, ��������������� �� ��������:" << endl;
            sort_by_names(lst_clients);
            print_lst_clients(lst_clients);
            break;
        case 5:
            cout << "\n������� ��� ������� ��� ����������: ";
            cin.ignore();
            getline(cin, search_name);
            update_client(search_name, lst_clients);
            break;
        case 6:
            cout << "\n������� ��� ������� ��� ��������: ";
            cin.ignore();
            getline(cin, search_name);
            delete_client(search_name, lst_clients);
            break;
        case 7:
            pos = get_highest_salary(lst_clients);
            if (pos != -1) {
                cout << "\n������ � ����� ������� ���������:" << endl;
                print_client(lst_clients[pos]);
            }
            break;
        case 8:
            cout << "����� � ������� ����..." << endl;
            break;
        default:
            cout << "\n������������ �������" << endl;
            break;
        }
    } while (*opt != 8);
}

void insert_client(Client& c, vector<Client>& lst_clients) {
    cout << "\n*** ���� ������ ������� ***" << endl;
    c.code = lst_clients.size() + 1;

    do {
        cout << "��� (�������� 40 ��������): ";
        cin.ignore();
        cin.getline(c.name, sizeof(c.name));

        if (strlen(c.name) > 40) {
            cout << "������: ��� �� ������ ��������� 40 ��������. ���������� �����.\n";
        }
    } while (strlen(c.name) > 40 || strlen(c.name) == 0);

    do {
        cout << "�������: ";
        cin >> c.age;
    } while (c.age <= 0);

    do {
        cout << "��������: ";
        cin >> c.salary;
    } while (c.salary < 20000 || c.salary > 500000);

    cout << "\n������ ��������!" << endl;
}

void save_clients_to_file(const vector<Client>& lst_clients) {
    ofstream file("clients.txt");
    if (!file) {
        cout << "������: ���������� ������� ���� ��� ������!" << endl;
        return;
    }

    file << left;
    file << setw(10) << "���" << setw(20) << "���" << setw(10) << "�������" << setw(10) << "��������" << endl;
    file << "------------------------------------------------------------------" << endl;

    for (const auto& client : lst_clients) {
        file << setw(10) << client.code
            << setw(20) << client.name
            << setw(10) << client.age
            << setw(10) << client.salary << endl;
    }

    file.close();
    cout << "\n������ �������� �������� � ���� clients.txt!" << endl;
}

void print_lst_clients(const vector<Client>& lst_clients) {
    cout << "\n*** ������ �������� ***" << endl;
    cout << left;
    cout << setw(10) << "���" << setw(20) << "���" << setw(10) << "�������" << setw(10) << "��������" << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (const auto& client : lst_clients) {
        print_client(client);
    }

    save_clients_to_file(lst_clients);
}

void print_client(const Client& c) {
    cout << setw(10) << c.code
        << setw(20) << c.name
        << setw(10) << c.age
        << setw(10) << c.salary << endl;
}

int search_client(const string& search_name, const vector<Client>& lst_clients) {
    for (size_t i = 0; i < lst_clients.size(); ++i) {
        if (search_name == lst_clients[i].name) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void sort_by_names(vector<Client>& lst_clients) {
    sort(lst_clients.begin(), lst_clients.end(), [](const Client& a, const Client& b) {
        return strcmp(a.name, b.name) < 0;
        });
}

void update_client(const string& search_name, vector<Client>& lst_clients) {
    int pos = search_client(search_name, lst_clients);
    if (pos != -1) {
        cout << "\n���������� �������:" << endl;

        do {
            cout << "����� ��� (�������� 40 ��������): ";
            cin.ignore();
            cin.getline(lst_clients[pos].name, sizeof(lst_clients[pos].name));

            if (strlen(lst_clients[pos].name) > 40) {
                cout << "������: ��� �� ������ ��������� 40 ��������. ���������� �����.\n";
            }
        } while (strlen(lst_clients[pos].name) > 40 || strlen(lst_clients[pos].name) == 0);

        do {
            cout << "����� �������: ";
            cin >> lst_clients[pos].age;
        } while (lst_clients[pos].age <= 0);

        do {
            cout << "����� ��������: ";
            cin >> lst_clients[pos].salary;
        } while (lst_clients[pos].salary < 20000 || lst_clients[pos].salary > 500000);

        cout << "\n������ ��������!" << endl;
    }
    else {
        cout << "\n������ �� ������!" << endl;
    }
}

void delete_client(const string& search_name, vector<Client>& lst_clients) {
    int pos = search_client(search_name, lst_clients);
    if (pos != -1) {
        lst_clients.erase(lst_clients.begin() + pos);
        cout << "\n������ ������!" << endl;
    }
    else {
        cout << "\n������ �� ������!" << endl;
    }
}

int get_num_clients(const vector<Client>& lst_clients) {
    return static_cast<int>(lst_clients.size());
}

int get_highest_salary(const vector<Client>& lst_clients) {
    if (lst_clients.empty()) return -1;

    size_t pos_max = 0;
    for (size_t i = 1; i < lst_clients.size(); ++i) {
        if (lst_clients[i].salary > lst_clients[pos_max].salary) {
            pos_max = i;
        }
    }
    return static_cast<int>(pos_max);
}
