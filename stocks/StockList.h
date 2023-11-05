#ifndef STOCKLIST_H
#define STOCKLIST_H

#include "Stock.h"

class StockList {
private:
    Stock **stocks;
    int stocks_size;
    int stocks_index;
    int frame_number; // used in some stock types

public:
    // constructors
    StockList();

    //construct from an array of stock pointers
    StockList(Stock **s, int size);

    // add a stock to the stocklist
    void add_stock(Stock *s);

    // update all stock values
    void update_stocks();

    // check if a stock exists
    bool stock_exists(std::string name);

    // return the pointer to a stock from its name
    Stock *get_stock(std::string name);

    // return the pointer to a stock from an index
    Stock *get_stock(int i);

    // return the size of the stock array
    int get_size();

    // return the index of the stock array
    int get_index();

    // clear all stocks from the list
    void clear();

    // destructor
    ~StockList();
};

#endif