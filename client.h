#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>
using namespace std;

struct Client {
    int code;
    char name[40];
    int age;
    double salary;
};

void save_clients_to_file(const vector<Client>& lst_clients);
void menu_clients(int* opt, vector<Client>& lst_clients);
void insert_client(Client& c, vector<Client>& lst_clients);
int get_num_clients(const vector<Client>& lst_clients);
void print_client(const Client& c);
void print_lst_clients(const vector<Client>& lst_clients);
int search_client(const string& search_name, const vector<Client>& lst_clients);
Client get_client(int pos, const vector<Client>& lst_clients);
Client default_client();
void sort_by_names(vector<Client>& lst_clients);
void update_client(const string& search_name, vector<Client>& lst_clients);
void delete_client(const string& search_name, vector<Client>& lst_clients);
int get_highest_salary(const vector<Client>& lst_clients);

#endif
