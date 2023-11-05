#include "Merchant.h"
#include <stdexcept>

// constructor
Merchant::Merchant(StockList *stock_list, Portfolio *p, Display *d) {
    this->stock_list = stock_list;
    this->p = p;
    this->d = d;
}

// destructor
Merchant::~Merchant() {}

// handle buying stocks with user input
void Merchant::buy() {
    //clear area of possible stock lines
    display_message("");
    wmove(stdscr, 1, 1);

    std::string name = "";
    int quantity = 0;
    // check input is valid
    bool user_input = handle_input(&name, &quantity);

    // try to buy the stock and give feedback messages
    bool valid_name = stock_list->stock_exists(name);
    if (valid_name && quantity > 0 && user_input) {
        Stock *s = stock_list->get_stock(name);
        float cost = quantity * s->get_value();
        if (p->get_balance() >= cost) {
            display_message("successfully bought stock");
            // success! buy stock.
            p->add_stock(s, quantity);
        } else {
            display_message("balance too low");
            // not enough balance
        }
    } else if (!valid_name && user_input) {
        display_message("cant find that stock");
        // incorrect stock name
    }
}

// handle selling stocks with user input
void Merchant::sell() {
    //clear area of possible stock lines
    display_message("");

    wmove(stdscr, 1, 1);
    std::string name = "";
    int quantity = 0;
    // check input is valid
    bool user_input = handle_input(&name, &quantity);

    // try to sell the stock, check values are valid
    bool valid_name = stock_list->stock_exists(name);
    if (valid_name && quantity > 0 && user_input) {
        // find the stock and how many we own
        Stock *s = stock_list->get_stock(name);
        float stock_quantity = p->get_stock_quantity(s);
        // if we own enough, sell them
        if (stock_quantity >= quantity) {
            display_message("successfully sold stock");
            // success! sell stocks.
            p->remove_stock(s, quantity);
        } else {
            display_message("you dont own enough of that stock");
            // not enough stocks owned
        }
    } else {
        if (!valid_name && user_input) {
            display_message("cant find that stock");
            // incorrect stock name
        }
    }
}

// handle user input, returns the entire input
bool Merchant::handle_input(std::string *name, int *quantity) {

    // clear user_input
    char *u = new char[100];
    // catch user input
    getnstr(u, 99);
    // convert char* to string
    std::string user_input(u);
    delete[] u;
    // break up the user input
    int comma_index = user_input.find(",");
    if (comma_index > 0) {
        *name = user_input.substr(0, comma_index);

        try {
            *quantity = stoi(user_input.substr(comma_index + 1, user_input.length() - 1));
        } catch (const std::out_of_range &e) {
            // number out of int range
            display_message("invalid quantity");
            *quantity = 0;
            return false;
        }
        catch (const std::invalid_argument &e) {
            display_message("command syntax invalid. Correct syntax is \"Example,3\"");
            *quantity = 0;
            return false;
        }

    } else {
        // no comma in command, invalid
        display_message("command syntax invalid. Correct syntax is \"Example,3\"");
        *quantity = 0;
        return false;
    }

    if (*quantity <= 0) {
        // invalid quantity
        display_message("quantity must be greater than 0");
        return false;
    }

    return true;
}

// display a message to the user underneath the user input area
void Merchant::display_message(std::string message) {
    // set up a string for clearing the area
    std::string s = "";
    for (size_t i = 0; i < message.length() + 10; i++) {
        s += " ";
    }

    // clear area around message
    d->graph->print(s, 0, 0);
    d->graph->print(s, 0, 1);
    d->graph->print(s, 0, 2);
    d->graph->print(s, 0, 3);

    // print message
    d->graph->print(message, 1, 2);
    napms(600);

    // clear message to prevent message overlap
    d->graph->print(s, 1, 2);
}
