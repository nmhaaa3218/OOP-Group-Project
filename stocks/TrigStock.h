#ifndef TRIG_STOCK
#define TRIG_STOCK

#include "Stock.h"

// generalised abstract base TrigStock for sin and cos trig Stocks
class TrigStock : public Stock {
protected:
    // controls behaviour of trig functions
    float amplitude;  // must be > 0
    float period;     // must be > 0
    float x_offset;   // -PI to PI
    float y_offset;   // must be > -amplitude

public:
    // constructor with parameters for defined behaviour
    TrigStock(std::string name, float value, float a, float p, float x_off, float y_off);

    // construct with a name and random parameters
    TrigStock(std::string name);

    // default constructor
    TrigStock();

    // destructor
    ~TrigStock();
};

#endif