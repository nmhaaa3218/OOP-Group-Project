#include "Graph.h"

#include <bits/stdc++.h>
#include <climits>

Graph::Graph() {
    w = newwin(stdscr->_maxy - 10, stdscr->_maxx, 0, 0);
    lines_size = 12;
    lines_index = 0;
    lines = new Line *[lines_size];
    scale = 1;

    for (int i = 0; i < lines_size; i++) {
        lines[i] = new Line();
    }

    nodelay(w, true);
    keypad(w, true);
}

float Graph::get_max() { return this->max; }

float Graph::get_min() { return this->min; }

// returns latest (rightmost) point that was drawn to display
int Graph::get_latest() { return this->latestPoint; }

float Graph::get_scale() { return this->scale; }

int Graph::get_size() { return this->lines_size; }

int Graph::get_index() { return this->lines_index; }

// refreshes window to show changes, also adds a border around edge
void Graph::refresh() {
    wclear(w);
    update_scaling();
    draw();
    wrefresh(w);
}

// resizes window when terminal resizes. deletes window w and remakes
void Graph::resize() {
    werase(w);
    if (stdscr->_maxy > 10) {
        delwin(w);
        w = newwin(stdscr->_maxy - 10, stdscr->_maxx, 0, 0);

    } else {
        delwin(w);
        w = newwin(stdscr->_maxy, stdscr->_maxx, 0, 0);
    }

    update_scaling();
}

// adds a line to the graph from a Stock
void Graph::add_line(Stock *s) { add_line(s->get_line(), s->get_char()); }

// remove all lines from graph
void Graph::remove_all() { lines_index = 0; }

// adds a Line to the graph
void Graph::add_line(Line *l, char c) {
    // only add a line if theres space in the array
    if (lines_index < lines_size) {
        lines[lines_index] = l;
        lines_index++;
        update_scaling();
    } else {
        // resize if lines is full
        Line **temp = new Line *[lines_size * 2];
        for (int i = 0; i < lines_index; i++) {
            temp[i] = lines[i];
        }
        lines_size *= 2;
        delete[] lines;
        lines = temp;
        // add line after resizing
        lines[lines_index] = l;
        lines_index++;
        update_scaling();
    }
}

// update the scaling of the graph based on all it's Lines
void Graph::update_scaling() {
    this->max = (float) INT_MIN;
    this->min = (float) INT_MAX;
    for (int i = 0; i < lines_index; i++) {
        lines[i]->update_minmax();

        // ensure graph knows biggest and lowest values from all it's lines
        float max_diff = lines[i]->max - this->max;
        float min_diff = lines[i]->min - this->min;
        if (max_diff > 0.5) {
            this->max = lines[i]->max;
        }
        if (min_diff < -0.5) {
            this->min = lines[i]->min;
        }
    }

    // find number to scale all line values by
    float range = max - min;

    // if range is too small, assume range is 0 and set scale to 1.
    // avoid dividing by 0
    if (range > 0.05) {
        scale = (float) w->_maxy / range;
    } else {
        scale = 1;
    }
}

//draw all lines to screen
void Graph::draw() {
    for (int i = 0; i < lines_index; i++) {
        Line *a = lines[i];

        // loop through line values in a way to always show latest added value
        // at the right edge of screen.
        for (int x = 0; x < a->values_index && x <= w->_maxx; x++) {
            // actual window x coordinate
            int win_x = w->_maxx - x;
            // current line value
            float curr_value = a->values[a->values_index - x - 1];
            // offset to allow showing negative values
            float offset = abs(this->min);
            // calc the actual window y coordinate
            int win_y = w->_maxy - ((curr_value - offset) * this->scale);
            if (x == 0) {
                latestPoint = win_y;
            }

            // check the point is within the window
            //print to a debug file to find of errors during development
            if (win_x > w->_maxx || win_x < 0) {
                // debug("x value out of bounds!");
                // debug("window max: " + std::to_string(w->_maxx));
                // debug(" value of line: " + std::to_string(curr_value));
                // debug(" x: " + std::to_string(x));
                // debug(" win_x: " + std::to_string(win_x));

            } else if (win_y > w->_maxy || win_y < 0) {
                // debug("y value out of bounds!");
                // debug(" window max: " + std::to_string(w->_maxy));
                // debug(" value of line: " + std::to_string(curr_value));
                // debug(" offset: " + std::to_string(offset));
                // debug(" scale: " + std::to_string(scale));
                // debug(" win_y: " + std::to_string(win_y));
                // debug(" graph min: " + std::to_string(min));
                // debug(" graph max: " + std::to_string(max));

            } else {
                // draw character at the coordinates!
                wmove(w, win_y, win_x);
                waddch(w, a->draw_char);
            }
        }
    }
}

// print a message to the user somewhere on the graph screen
void Graph::print(std::string s, int x, int y) {
    wmove(w, y, x);
    char print_chars[s.length() + 1];
    strcpy(print_chars, s.c_str());
    wprintw(w, "%s", print_chars);
    wrefresh(w);
}

//destructor
Graph::~Graph(){
    delwin(w);
}