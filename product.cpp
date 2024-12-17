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
    default: throw invalid_argument("�������� ���������");
    }
}

string categoryToString(Category category) {
    switch (category) {
    case Category::Fantasy: return "�������";
    case Category::Fantastic: return "����������";
    case Category::Romance: return "�����";
    case Category::History: return "�������";
    default: return "����������";
    }
}

void addBook(vector<Book>& books) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Book newBook;
    cout << "������� ������ �����:\n";
    newBook.code = books.empty() ? 1 : books.back().code + 1;
    cin.ignore();

    do {
        cout << "����� (�� ����� 40 ��������): ";
        getline(cin, newBook.author);
        if (newBook.author.length() > 40) {
            cout << "������: ����� ����� ������ ��������� 40 ��������.\n";
        }
    } while (newBook.author.length() > 40);

    do {
        cout << "�������� ����� (�� ����� 40 ��������): ";
        getline(cin, newBook.title);
        if (newBook.title.length() > 40) {
            cout << "������: ����� �������� ��������� 40 ��������.\n";
        }
    } while (newBook.title.length() > 40);

    cout << "���������� �� ������: ";
    cin >> newBook.stock;

    do {
        cout << "���� (�� 100 �� 50000): ";
        cin >> newBook.price;
        if (newBook.price < 100 || newBook.price > 50000) {
            cout << "������: ���� ������ ���� � ��������� �� 100 �� 50000.\n";
        }
    } while (newBook.price < 100 || newBook.price > 50000);

    do {
        cout << "��� ������� (�� ������ 2000): ";
        cin >> newBook.year;
        if (newBook.year < 2000) {
            cout << "������: ��� ������� ������ ���� �� ������ 2000.\n";
        }
    } while (newBook.year < 2000);

    int cat;
    cout << "��������� (0-�������, 1-����������, 2-�����, 3-�������): ";
    cin >> cat;
    newBook.category = intToCategory(cat);

    books.push_back(newBook);

    ofstream outFile("data/book.txt", ios::app);
    outFile << newBook.code << "," << newBook.author << "," << newBook.title << "," << newBook.stock
        << "," << newBook.price << "," << newBook.year << "," << cat << "\n";
    outFile.close();

    cout << "����� ������� ���������.\n";
}

void saveBooksToFile(const vector<Book>& books, const string& filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "������: �� ������� ������� ���� " << filename << " ��� ������.\n";
        return;
    }

    outFile << left << setw(5) << "���" << setw(20) << "�����" << setw(20) << "��������" << setw(10)
        << "�����" << setw(10) << "����" << setw(6) << "���" << "���������\n";
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
    cout << "\n������ ���� ������� ��������� � ����: " << filename << "\n";
}

void displayBooks(const vector<Book>& books) {
    cout << left << setw(5) << "���" << setw(20) << "�����" << setw(20) << "��������" << setw(10)
        << "�����" << setw(10) << "����" << setw(6) << "���" << "���������\n";
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
        cout << "\n����� �� �������!\n";
        return;
    }

    cout << "���������� ������ �����: " << books[pos].title << "\n";

    cout << "����� ���������� �� ������: ";
    cin >> books[pos].stock;

    do {
        cout << "����� ���� (�� 100 �� 50000): ";
        cin >> books[pos].price;
        if (books[pos].price < 100 || books[pos].price > 50000) {
            cout << "������: ���� ������ ���� � ��������� �� 100 �� 50000.\n";
        }
    } while (books[pos].price < 100 || books[pos].price > 50000);

    cout << "����� ������� ���������.\n";
}

void delete_Book(const string& search_title, vector<Book>& books) {
    int pos = search_Book(search_title, books);
    if (pos == -1) {
        cout << "\n����� �� �������!\n";
        return;
    }

    books.erase(books.begin() + pos);
    cout << "\n����� ������� �������.\n";
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
        cout << setw(20) << "\n --- ���������� ������� ---" << endl;
        cout << "\n�������� ������� �� [1-8] �������� ����:\n";
        cout << "[1]. �������� �����\n";
        cout << "[2]. �������� ������ ����\n";
        cout << "[3]. ����� �����\n";
        cout << "[4]. ������������� �� ����\n";
        cout << "[5]. �������� ������ �����\n";
        cout << "[6]. ������� �����\n";
        cout << "[7]. ����� ����� � ����������� �����\n";
        cout << "[8]. �����\n";
        cout << "------------------------------------------------\n";
        cout << "������� �������: ";
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
            cout << "\n������� �������� ����� ��� ������: ";
            cin.ignore();
            getline(cin, search_title);

            int pos = search_Book(search_title, books);

            if (pos != -1) {
                cout << "\n��������� �����: \n";
                displayBooks({ books[pos] });
            }
            else {
                cout << "\n����� �� �������.\n";
            }
            break;
        }
        case 4:
            sort_by_prices(books);
            cout << "\n����� ������������� �� ����.\n";
            break;
        case 5: {
            string search_title;
            cout << "\n������� �������� ����� ��� ����������: ";
            cin.ignore();
            getline(cin, search_title);

            update_Book(search_title, books);
            break;
        }
        case 6: {
            string search_title;
            cout << "\n������� �������� ����� ��� ��������: ";
            cin.ignore();
            getline(cin, search_title);

            delete_Book(search_title, books);
            break;
        }
        case 7: {
            int pos = get_cheapest_Book(books);
            if (pos != -1) {
                cout << "\n����� � ����������� �����: \n";
                displayBooks({ books[pos] });
            }
            else {
                cout << "\n��� ��������� ����.\n";
            }
            break;
        }
        case 8:
            cout << "����� � ������� ����...\n";
            break;
        default:
            cout << "\n�������� �������.\n";
        }
    } while (*opt != 8);
}
