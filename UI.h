#ifndef UI_H
#define UI_H

#include <curses.h>
#include "stocks/StockList.h"

class UI {
protected:
    WINDOW *w;

public:
    // constructor
    UI();

    // refresh UI window to show changes
    void refresh();

    // resize based on terminal size
    void resize();

    // print a message somewhere in the ui
    void print(std::string s, int x, int y);

    // clear the entire UI of chars
    void erase();

    // format and display all stocklist information
    void show_stock_info(StockList *stock_list);

    // format and display keybind information
    void show_controls();

    // destructor
    ~UI();
};

#endif