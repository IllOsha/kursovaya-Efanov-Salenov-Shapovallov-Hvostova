#pragma once
#include <vector>
#include "client.h"
#include "product.h"
using namespace std;

#define MAX 10

struct OrderDetail {
    Book book;
    int quantity;
    double subtotal;
};

struct Order {
    int code;
    Client client;
    vector<OrderDetail> details;
    double totalAmount = 0;
};

void menu_orders(int* opt, vector<Client>& lst_clients, vector<Book>& books, vector<Order>& lst_orders);
void insert_order(Order& ord, vector<Client>& lst_clients, vector<Book>& books);
void insert_order_detail(OrderDetail& od, vector<Book>& books);
void print_list_orders(const vector<Order>& lst_orders);
void print_order(const Order& ord);
