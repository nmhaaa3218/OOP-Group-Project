#include "StockList.h"

#include <fstream>

// default constructor
StockList::StockList() {
    stocks_size = 8;
    stocks_index = 0;
    stocks = new Stock *[stocks_size];
    frame_number = 0;
}

// creates the StockList with a premade array of stock pointers
StockList::StockList(Stock **s, int size) {
    stocks_size = size;
    stocks_index = size;
    stocks = s;
}

// adds a Stock to the StockList
void StockList::add_stock(Stock *s) {
    // check if space
    if (stocks_index < stocks_size) {
        // just add it
        stocks[stocks_index] = s;
        stocks_index++;
    } else {
        // double stocks array size
        Stock **temp = new Stock *[stocks_size * 2];
        for (int i = 0; i < stocks_size; i++) {
            temp[i] = stocks[i];
        }
        delete[] stocks;
        stocks = temp;
        stocks[stocks_index] = s;
        stocks_index++;
        stocks_size *= 2;
    }
}

// check if the StockList contains a Stock
bool StockList::stock_exists(std::string name) {
    for (int i = 0; i < stocks_index; i++) {
        if (stocks[i]->get_name() == name) {
            return true;
        }
    }
    return false;
}

// returns the Stock with the given name
Stock *StockList::get_stock(std::string name) {
    // return fallback if cannot find stock.
    //!!always call stock_exists() on user input before calling find_stock().!!
    Stock *fallback = NULL;
    for (int i = 0; i < stocks_index; i++) {
        if (stocks[i]->get_name() == name) {
            return stocks[i];
        }
    }
    return fallback;
}

// returns the Stock at the given index
Stock *StockList::get_stock(int i) {
    if (i < stocks_index) {
        return stocks[i];
    }
    return NULL;
}

// calls update on every Stock in the list
void StockList::update_stocks() {
    for (int i = 0; i < stocks_index; i++) {
        stocks[i]->update(frame_number);
    }
    frame_number++;
}

// clears the StockList
void StockList::clear() {
    delete[] stocks;
    stocks_size = 8;
    stocks_index = 0;
    stocks = new Stock *[stocks_size];
}

// returns the number of Stocks in the list
int StockList::get_size() { return stocks_size; }

// returns the index of the next available space in the list
int StockList::get_index() { return stocks_index; }

// destructor
StockList::~StockList() { delete[] stocks; }