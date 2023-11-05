#ifndef GRAPH_H
#define GRAPH_H

#include <curses.h>

#include "stocks/Line.h"
#include "stocks/Stock.h"

class Graph {
protected:
    WINDOW *w;
    Line **lines;
    int lines_size;
    int lines_index;
    double scale;
    float min, max;
    int latestPoint;

public:
    // default constructor
    Graph();

    // refresh the graph to show changes
    void refresh();

    // resize the graph window with respect to terminal size
    void resize();

    // draw lines to the window
    void draw();

    // add a line to the graph
    void add_line(Line *l, char c);

    // add a line from a stock
    void add_line(Stock *s);

    // update the scaling of the graph based on line values
    void update_scaling();

    // return the minimum value in the graph's lines
    float get_min();

    // return the maximum value in the graph's lines
    float get_max();

    // return the scale of the graph
    float get_scale();

    // return the latest drawn point value
    int get_latest();

    // return the size of the lines array
    int get_size();
    
    // return the current index of the lines array
    int get_index();

    // print a message somewhere on the graph window
    void print(std::string s, int x, int y);

    // remove all lines from the graph
    void remove_all();

    //destructor
    ~Graph();
};

#endif