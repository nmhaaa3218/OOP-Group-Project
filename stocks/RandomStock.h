#ifndef RANDOMSTOCK_H
#define RANDOMSTOCK_H

#include "Stock.h"

// RandomStock definitions

using namespace std;

class RandomStock : public Stock {
private:
    // determines the random stock's general direction
    float tendency = 0;

public:
    // constructors
    RandomStock();

    // construct with initial value and name
    RandomStock(float value, std::string name);

    // return the tendency of the random stock
    float get_tendency();

    // overload update methods in derived class
    // default update()
    void update();

    // update wih respect to frame_number
    void update(int frameNumber);

    // return the type of stock
    int get_type();

    //destructor
    ~RandomStock();
};

#endif