#ifndef DISPLAY_H
#define DISPLAY_H

#include "Graph.h"
#include "UI.h"
#include "stocks/Portfolio.h"

// Display class
class Display {
public:
    Graph *graph;
    UI *ui;
    bool paused = false;

    // default constructor
    Display();

    // refreshes ui and graph classes and handles resizing
    void refresh_all();

    // displays all stocks from a portfolio
    void add_Portfolio(Portfolio *p);

    // Pause the display
    void pause();

    // Resume the display
    void unpause();

    // destructor
    ~Display();
};

#endif