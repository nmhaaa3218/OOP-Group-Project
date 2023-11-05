// Stock class implementation

#include "Stock.h"

#include <bits/stdc++.h>

Stock::Stock() : Stock("Unnamed", 0, 0) {}  // default constructor

// constructor with parameters
Stock::Stock(std::string name, float value, int count) {
    this->name = name;
    this->value = value;
    this->count = count;
    l = new Line();
    l->set_char(this->get_char());
}

// return value of the Stock
float Stock::get_value() { return value; }

// return count of the Stock
int Stock::get_count() { return count; }

// set count of the Stock
void Stock::set_count(int count) { this->count = count; }

// return name of the Stock
std::string Stock::get_name() { return name; }

// return Line of the Stock
Line *Stock::get_line() { return l; }

// return name of the Stock
char Stock::get_char() {
    char copy[name.length() + 1];
    std::strcpy(copy, name.c_str());
    char c = copy[0];
    return c;
}

// destructor
Stock::~Stock() {
    delete l;
}
