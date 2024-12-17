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
        cout << setw(20) << "\n --- УПРАВЛЕНИЕ КЛИЕНТАМИ ---" << endl;
        cout << "\nВыберите вариант из [1-8] :" << endl;
        cout << "[1]. Вставить клиента" << endl;
        cout << "[2]. Прочитать список клиентов" << endl;
        cout << "[3]. Поиск клиента" << endl;
        cout << "[4]. Сортировать в алфавитном порядке" << endl;
        cout << "[5]. Обновление клиента" << endl;
        cout << "[6]. Удалить клиента" << endl;
        cout << "[7]. Найдите клиента с самой высокой зарплатой" << endl;
        cout << "[8]. Выход" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "Введите вариант: ";
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
            cout << "\nВведите имя для поиска: ";
            cin.ignore();
            getline(cin, search_name);
            pos = search_client(search_name, lst_clients);

            if (pos != -1) {
                cout << "\nНайден клиент:" << endl;
                print_client(lst_clients[pos]);
            }
            else {
                cout << "\nКлиент не найден" << endl;
            }
            break;
        case 4:
            cout << "\nСписок клиентов, отсортированный по алфавиту:" << endl;
            sort_by_names(lst_clients);
            print_lst_clients(lst_clients);
            break;
        case 5:
            cout << "\nВведите имя клиента для обновления: ";
            cin.ignore();
            getline(cin, search_name);
            update_client(search_name, lst_clients);
            break;
        case 6:
            cout << "\nВведите имя клиента для удаления: ";
            cin.ignore();
            getline(cin, search_name);
            delete_client(search_name, lst_clients);
            break;
        case 7:
            pos = get_highest_salary(lst_clients);
            if (pos != -1) {
                cout << "\nКлиент с самой высокой зарплатой:" << endl;
                print_client(lst_clients[pos]);
            }
            break;
        case 8:
            cout << "Выход в главное меню..." << endl;
            break;
        default:
            cout << "\nНедопустимый вариант" << endl;
            break;
        }
    } while (*opt != 8);
}

void insert_client(Client& c, vector<Client>& lst_clients) {
    cout << "\n*** Ввод нового клиента ***" << endl;
    c.code = lst_clients.size() + 1;

    do {
        cout << "Имя (максимум 40 символов): ";
        cin.ignore();
        cin.getline(c.name, sizeof(c.name));

        if (strlen(c.name) > 40) {
            cout << "Ошибка: Имя не должно превышать 40 символов. Попробуйте снова.\n";
        }
    } while (strlen(c.name) > 40 || strlen(c.name) == 0);

    do {
        cout << "Возраст: ";
        cin >> c.age;
    } while (c.age <= 0);

    do {
        cout << "Зарплата: ";
        cin >> c.salary;
    } while (c.salary < 20000 || c.salary > 500000);

    cout << "\nКлиент добавлен!" << endl;
}

void save_clients_to_file(const vector<Client>& lst_clients) {
    ofstream file("clients.txt");
    if (!file) {
        cout << "Ошибка: невозможно открыть файл для записи!" << endl;
        return;
    }

    file << left;
    file << setw(10) << "Код" << setw(20) << "Имя" << setw(10) << "Возраст" << setw(10) << "Зарплата" << endl;
    file << "------------------------------------------------------------------" << endl;

    for (const auto& client : lst_clients) {
        file << setw(10) << client.code
            << setw(20) << client.name
            << setw(10) << client.age
            << setw(10) << client.salary << endl;
    }

    file.close();
    cout << "\nСписок клиентов сохранен в файл clients.txt!" << endl;
}

void print_lst_clients(const vector<Client>& lst_clients) {
    cout << "\n*** Список клиентов ***" << endl;
    cout << left;
    cout << setw(10) << "Код" << setw(20) << "Имя" << setw(10) << "Возраст" << setw(10) << "Зарплата" << endl;
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
        cout << "\nОбновление клиента:" << endl;

        do {
            cout << "Новое имя (максимум 40 символов): ";
            cin.ignore();
            cin.getline(lst_clients[pos].name, sizeof(lst_clients[pos].name));

            if (strlen(lst_clients[pos].name) > 40) {
                cout << "Ошибка: Имя не должно превышать 40 символов. Попробуйте снова.\n";
            }
        } while (strlen(lst_clients[pos].name) > 40 || strlen(lst_clients[pos].name) == 0);

        do {
            cout << "Новый возраст: ";
            cin >> lst_clients[pos].age;
        } while (lst_clients[pos].age <= 0);

        do {
            cout << "Новая зарплата: ";
            cin >> lst_clients[pos].salary;
        } while (lst_clients[pos].salary < 20000 || lst_clients[pos].salary > 500000);

        cout << "\nКлиент обновлен!" << endl;
    }
    else {
        cout << "\nКлиент не найден!" << endl;
    }
}

void delete_client(const string& search_name, vector<Client>& lst_clients) {
    int pos = search_client(search_name, lst_clients);
    if (pos != -1) {
        lst_clients.erase(lst_clients.begin() + pos);
        cout << "\nКлиент удален!" << endl;
    }
    else {
        cout << "\nКлиент не найден!" << endl;
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
