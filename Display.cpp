#include "Display.h"

#include <climits>

// default constructor
Display::Display() {
    graph = new Graph();
    ui = new UI();
    nodelay(stdscr, true);
}

// refreshes ui and graph classes and handles resizing
void Display::refresh_all() {
    if (is_term_resized(stdscr->_maxy, stdscr->_maxx)) {
        // if terminal is resized, update stdscr
        resize_term(0, 0);
        // call component resize functions to resize windows correctly
        graph->resize();
        ui->resize();
    }

    ui->erase();  // keep ui clean between each frame

    // show scale of the graph to make it easier to understand
    float max = graph->get_max();
    float min = graph->get_min();

    if (min != (float) INT_MAX && max != (float) INT_MIN) {
        ui->print("max of graph: " + std::to_string(max), 1, 1);
        ui->print("min of graph: " + std::to_string(min), 1, 2);
    }

    // refresh both components
    graph->refresh();
    ui->refresh();
}

// displays all stocks from a portfolio
void Display::add_Portfolio(Portfolio *p) {
    graph->remove_all();
    for (int i = 0; i < p->get_size(); i++) {
        graph->add_line(p->get_stocks()[i]);
    }
}

// Pause the display
void Display::pause() {
    paused = true;
    nodelay(stdscr, false);
}

// Resume the display
void Display::unpause() {
    paused = false;
    nodelay(stdscr, true);
}

Display::~Display(){
    delete graph;
    delete ui;
}