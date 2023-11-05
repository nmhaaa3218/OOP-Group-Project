#include "CosStock.h"

// default constructor
CosStock::CosStock() {}

// constructor with name but random parameters
CosStock::CosStock(std::string name) : TrigStock(name) {}

// constructor with parameters
CosStock::CosStock(std::string name, float value, float a, float p, float x_off, float y_off)
                    : TrigStock(name, value, a, p, x_off, y_off) {}

// update without being given a frame_number, defaults to 0
void CosStock::update() { update(0); }

// update with frame_number
void CosStock::update(int frameNumber) {
    // calc value as per standard trig formula
    value = amplitude * cos(period * frameNumber - x_offset) + y_offset;

    // constrain the value above 0
    if (value < 0.01) {
        value = 0.01;
    }

    // add the value to the stock's Line
    l->add_value(value);
}

// return type of the Stock
int CosStock::get_type() { return 2; }

// destructor
CosStock::~CosStock() {}