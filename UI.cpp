#include "UI.h"

#include <bits/stdc++.h>

// constructor
UI::UI() {
    w = newwin(10, stdscr->_maxx, stdscr->_maxy - 10, 0);
    nodelay(w, true);
    keypad(w, true);
}

// refresh ui window
void UI::refresh() {
    wborder(w, '|', '|', '-', '-', '+', '+', '+', '+');

    wrefresh(w);
}

// print a message to the ui
void UI::print(std::string s, int x, int y) {
    wmove(w, y, x);
    char print_chars[s.length() + 1];
    strcpy(print_chars, s.c_str());
    wprintw(w, "%s", print_chars);
    refresh();
}

// clear the ui
void UI::erase() { werase(w); }

// resizes window when terminal resizes. deletes window w and remakes
void UI::resize() {
    wclear(w);
    if (stdscr->_maxy > 10) {
        delwin(w);
        w = newwin(10, stdscr->_maxx, stdscr->_maxy - 10, 0);
    } else {
        delwin(w);
    }
}

// format and display all stocklist information
void UI::show_stock_info(StockList *stock_list) {
    std::string v = "VALUES: ";
    std::string o = "OWNED:  ";
    for (int i = 0; i < stock_list->get_index(); i++) {
        Stock *curr = stock_list->get_stock(i);
        std::string curr_value = std::to_string(curr->get_value());
        std::string curr_name = curr->get_name();
        std::string curr_count = std::to_string(curr->get_count());

        // remove trailing zeros
        curr_value = curr_value.substr(0, curr_value.find('.') + 3);

        v += curr_name + ": " + curr_value + "   ";

        o += curr_name + ": " + curr_count + "   ";
        // align the owned string with the values string
        for (size_t i = 0; i < curr_value.length() - curr_count.length(); i++) {
            o += " ";
        }
    }
    print(v, 1, 3);
    print(o, 1, 4);

    
}

//format and display keybind information
void UI::show_controls() {
    // arrange strings
    std::string buysell_line = "b to buy   | s to sell |"
        " buy/sell syntax: stockname,quantity ";
    std::string saveload_line = "k to save  | l to load";
    std::string pausequit_line = "p to pause | q to quit";

    // print keybind info to ui
    print(buysell_line,40,6);
    print(saveload_line,40,7);
    print(pausequit_line,40,8);
}

//destructor
UI::~UI(){
    delwin(w);
}