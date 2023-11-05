#include "SinStock.h"

// default constructor
SinStock::SinStock() {}

// construct with name but random parameters
SinStock::SinStock(std::string name) : TrigStock(name) {}

// construct with defined parameters
SinStock::SinStock(std::string name, float value, float a, float p, float x_off,
                   float y_off) {}

// update without being given a frame_number, defaults to 0
void SinStock::update() { update(0); }

// update with frame_number
void SinStock::update(int frameNumber) {
  value = amplitude * sin(period * frameNumber - x_offset) + y_offset;
  if (value < 0.01) {
    value = 0.01;
  }
  l->add_value(value);
}

// return type of the Stock
int SinStock::get_type() { return 3; }

SinStock::~SinStock() {}