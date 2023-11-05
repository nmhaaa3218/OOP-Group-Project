#ifndef STOCK_H
#define STOCK_H

#include <math.h>
#include <random>
#include <string>
#include "Line.h"

// Stock class definitions
class Stock {
protected:
    // variables
    std::string name;
    int count;
    float value;
    Line *l;

public:
    // constructors
    Stock();

    // constructor with name, initial value and initial portfolio count
    Stock(std::string name, float initialValue, int count);

    // methods
    // return value of stock
    float get_value();

    // return quantity of stock
    int get_count();

    // change the quantity of the stock
    void set_count(int count);

    // get name of stock
    std::string get_name();

    // return a pointer to the Stock's Line
    Line *get_line();

    // get the first char in the Stock's name
    char get_char();

    // get the stock type, used in save/loading
    virtual int get_type() = 0;

    // virtual update method
    virtual void update() = 0;

    // virtual update method for stocks that use the frame number
    virtual void update(int frameNumber) = 0;

    // destructor
    ~Stock();
};

#endif