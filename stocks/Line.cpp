#include "Line.h"

#include <limits.h>

//default constructor
Line::Line() {
    values_size = 235;
    values = new float[values_size];
    min = (float) INT_MAX;
    max = (float) INT_MIN;
    values_index = 0;
    values[0] = 0;
    draw_char = 'o';
}

void Line::set_char(char c) { draw_char = c; }

// loop through all values and find min and max
void Line::update_minmax() {
    // only check the end 300 values to keep graph scaling based on window
    int begin_index = 0;
    if (values_index > 250) {
        begin_index = values_index - 250;
    }
    min = values[begin_index];
    max = values[begin_index];
    for (int i = begin_index; i < values_index; i++) {
        if (values[i] < min) {
            min = values[i];
        }
        if (values[i] > max) {
            max = values[i];
        }
    }
}

// adds a value to the values array
void Line::add_value(float value) {
    if (value < min) {
        min = value;
    }
    if (value > max) {
        max = value;
    }

    // if still space in array, just add it
    if (values_index < values_size) {
        values[values_index] = value;
        values_index++;
    } else {  // otherwise resize array
        float *temp = new float[values_size * 2];
        for (int i = 0; i < values_index; i++) {
            temp[i] = values[i];
        }
        delete[] values;
        values = temp;
        values_size *= 2;

        values[values_index] = value;
        values_index++;
    }
}

Line::~Line() { delete[] values; }