#ifndef MERCHANT_H
#define MERCHANT_H

#include "Display.h"

class Merchant {
private:
    StockList *stock_list;
    Portfolio *p;
    Display *d;

public:
    // constructor
    Merchant(StockList *stock_list, Portfolio *p, Display *d);

    // destructor
    ~Merchant();

    // handle buying stocks with user input
    void buy();

    // handle selling stocks with user input
    void sell();

    // display a message to the user underneath the user input area
    void display_message(std::string message);

    // process user input, returns the entire input
    bool handle_input(std::string *name, int *quantity);
};

#endif