#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Stock.h"

// Portfolio definitions
class Portfolio {
public:
    // constructors
    Portfolio();

    // construct with a predefined stock parameters
    Portfolio(Stock **stocks, int size);

    // destructor
    ~Portfolio();

    // accessors
    float get_value();

    int get_size();

    Stock **get_stocks();

    // other methods
    // add a stock to the portfolip
    void add_stock(Stock *s, int quantity);

    // remove a stock from the portfolio
    void remove_stock(Stock *s, int quantity);

    // get the quantity of a stock
    int get_stock_quantity(Stock *s);

    // return the available balance of the portfolio
    float get_balance();

    // change the balance
    void set_balance(float value);

    // recalculate the value of the portfolio
    void update();

    // empty the portfolio
    void clear();

private:
    float balance;
    float value;
    int size;
    Stock **stocks;
};

#endif