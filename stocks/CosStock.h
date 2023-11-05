#ifndef COSSTOCK_H
#define COSSTOCK_H

#include "TrigStock.h"

class CosStock : public TrigStock {
public:
    // default constructor
    CosStock();

    // construct with name but random parameters
    CosStock(std::string name);

    // construct with defined parameters
    CosStock(std::string name, float value, float a, float p, float x_off, float y_off);

    // update without being given a frame_number, defaults to 0
    void update();

    // update with frame_number
    void update(int frameNumber);

    // return type of stock
    int get_type();

    // destructor
    ~CosStock();
};

#endif