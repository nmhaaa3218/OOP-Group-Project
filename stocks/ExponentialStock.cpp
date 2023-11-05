#include "ExponentialStock.h"

// ExponentialStock implementation

// default constructor
ExponentialStock::ExponentialStock() : ExponentialStock(0) {}

// construct with initial value
ExponentialStock::ExponentialStock(float value) : Stock("ExponentialStock", value, 0) {
    increasing = true;
}

// construct with initial value and name
ExponentialStock::ExponentialStock(float value, std::string name) : Stock(name, value, 0) {
    increasing = true;
}

void ExponentialStock::update(int frameNumber) {
    // expo stock doesn't use the frame number, discard it
    update();
}

// update value of stock
void ExponentialStock::update() {
    // update the value
    if (value <= 2) {
        value = 2;
        increasing = true;
    } 
    if (increasing && value < 500) {
        value = pow(value, 1.01);
    } else {
        increasing = false;
        value = pow(value, 1.0 / 1.01);
    }
    // should bounce between high and low values interestingly hopefully

    // add the value to the Stock's Line
    l->add_value(value);
}

// return the type of stock
int ExponentialStock::get_type() { return 0; }

// destructor
ExponentialStock::~ExponentialStock() {}