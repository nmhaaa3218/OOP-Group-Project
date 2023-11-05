#include "Portfolio.h"

// default constructor
Portfolio::Portfolio() {
    value = 0;
    size = 0;
    balance = 5000;
    stocks = NULL;
}

// constructs with a pre-made Stock pointer array
Portfolio::Portfolio(Stock **s, int size) {
    stocks = s;
    this->size = size;
    update();
}

// destructor
Portfolio::~Portfolio() { delete[] stocks; }

// returns the total value of the Portfolio
float Portfolio::get_value() { return value; }

// returns how many Stocks are inside the Portfolio
int Portfolio::get_size() { return size; }

// returns the array of Stock pointers
Stock **Portfolio::get_stocks() { return stocks; }

// adds a new Stock to the Portfolio, decreasing portfolio balance
void Portfolio::add_stock(Stock *s, int quantity) {
    Stock **temp = new Stock *[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = stocks[i];
    }
    temp[size] = s;
    delete[] stocks;
    stocks = temp;
    size++;
    balance -= s->get_value() * quantity;
    int currCount = s->get_count();
    s->set_count(currCount + quantity);
    update();
}

// removes a Stock from the portfolio, increasing portfolio balance
void Portfolio::remove_stock(Stock *s, int quantity) {
    int currCount = s->get_count();
    s->set_count(currCount - quantity);
    // if stock count is 0, remove stock from portfolio and resize
    if (s->get_count() == 0) {
        Stock **temp = new Stock *[size - 1];
        int j = 0;
        for (int i = 0; i < size; i++) {
            if (stocks[i] != s) {
                temp[j] = stocks[i];
                j++;
            }
        }
        delete[] stocks;
        stocks = temp;
        size--;
    }
    balance += s->get_value() * quantity;

    update();
}

// updates the value of the Portfolio
void Portfolio::update() {
    value = 0;
    for (int i = 0; i < size; i++) {
        value += stocks[i]->get_value() * stocks[i]->get_count();
    }
}

//clears the Portfolio
void Portfolio::clear() {
    value = 0;
    size = 0;
    balance = 0;
    stocks = NULL;
}

// returns the balance of the Portfolio
float Portfolio::get_balance() { return balance; }

// sets the balance of the Portfolio
void Portfolio::set_balance(float value) { balance = value; }

//return the quantity of a stock that is owned
int Portfolio::get_stock_quantity(Stock *s) { return s->get_count(); }