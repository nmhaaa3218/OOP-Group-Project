#include "TrigStock.h"

// constructor with parameters for defined behaviour
TrigStock::TrigStock(std::string name, float value, float a, float p,
                     float x_off, float y_off)
    : Stock(name, value, 0) {
  amplitude = a;
  period = p;
  x_offset = x_off;
  y_offset = y_off;
}

// construct with a name and random parameters
TrigStock::TrigStock(std::string name) : Stock(name, 0, 0) {
  amplitude = rand() % 200 - 99;
  period = (float)(rand() % 7 + 3) / 1000.0;
  x_offset = rand() % 1000;
  y_offset = rand() % 100;
}

// default constructor
TrigStock::TrigStock() : Stock("TrigStock", 0, 0) {
  amplitude = 1;
  period = 10;
  x_offset = 0;
  y_offset = 0;
}

// destructor
TrigStock::~TrigStock() {}