#ifndef EXPOSTOCK_H
#define EXPOSTOCK_H

#include "Stock.h"

// ExponentialStock definitions

using namespace std;

class ExponentialStock : public Stock {
private:
    bool increasing;

public:
    // constructors
    ExponentialStock();

    // construct with an initial value but no name
    ExponentialStock(float value);

    // construct with an initial value and name
    ExponentialStock(float value, std::string name);

    // overload update method in derived class
    void update();

    // update with respect to frame_number
    void update(int frameNumber);

    // return the stock type for saving and loading
    int get_type();

    // destructor
    ~ExponentialStock();
};

#endif