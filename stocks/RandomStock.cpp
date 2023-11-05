#include "RandomStock.h"

// RandomStock implementation

// default constructor
RandomStock::RandomStock() : RandomStock(0, "RandomStock") {}

// construct with initial value
RandomStock::RandomStock(float value, std::string name) : Stock(name, value, 0) {
    // no dividing by zero >:D
    tendency = (float) (rand() % 9) / ((float) (rand() % 9) + 1);
}

// random stock doesn't use frame_number, overload it
void RandomStock::update(int frameNumber) { update(); }

// update value of stock
void RandomStock::update() {
    value = value + (rand() % 5 - 2) + tendency;
    if (value < 0.01) {
        value = 0.01;
    }
    l->add_value(value);
    tendency /= (value / 10);
}

// return tendency of the stock
float RandomStock::get_tendency() { return tendency; }

// return type of the Stock
int RandomStock::get_type() { return 1; }

RandomStock::~RandomStock() {}
