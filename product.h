#pragma once

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

enum class Category {
    Fantasy,
    Fantastic,
    Romance,
    History
};

struct Book {
    int code;
    std::string author;
    std::string title;
    int stock;
    double price;
    int year;
    Category category;
};

void saveBooksToFile(const std::vector<Book>& books, const std::string& filename);
int search_Book(const std::string& search_title, const std::vector<Book>& books);
void menu_Books(int* opt, std::vector<Book>& books);
void addBook(std::vector<Book>& books);
void displayBooks(const std::vector<Book>& books);
void update_Book(const std::string& search_title, std::vector<Book>& books);
void delete_Book(const std::string& search_title, std::vector<Book>& books);
void sort_by_prices(std::vector<Book>& books);
int get_cheapest_Book(const std::vector<Book>& books);

Category intToCategory(int cat);
std::string categoryToString(Category category);

#endif
