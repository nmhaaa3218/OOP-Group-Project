#ifndef LINE_H
#define LINE_H

class Line {
public:
    //variables
    int values_size;
    int values_index;
    float *values;
    float max, min;
    char draw_char;

    // add a value to the array
    void add_value(float value);

    // check all values to find min and max
    void update_minmax();

    // change the char used for displaying this line
    void set_char(char c);

    //constructor
    Line();

    //destructor
    ~Line();
};

#endif