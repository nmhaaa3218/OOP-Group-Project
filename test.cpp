// stock types
#include "stocks/CosStock.h"
#include "stocks/ExponentialStock.h"
#include "stocks/RandomStock.h"
#include "stocks/SinStock.h"

// user interaction and save/loading
#include "SaveAndLoad.h"
#include "stocks/Portfolio.h"

// classes that use ncurses cannot be tested without using debug functions.
// ncurses mode blocks sending strings to std::cout on ubuntu.

// basic class used in stocks, used *by* display to create graph
#include "stocks/Line.h"

// cant test abstract classes Stock and TrigStock,
// as they have pure virtual methods

#include <iostream>
using namespace std;

int main() {
  // create objects to test
  Stock* expo = new ExponentialStock(2, "expo");
  Stock* cos = new CosStock("cos");
  Stock* sin = new SinStock("sin");
  Stock* rand = new RandomStock(0, "rand");

  StockList* stock_list = new StockList();

  Portfolio* portfolio = new Portfolio();
  SaveAndLoad* saver = new SaveAndLoad();

  Line* line = new Line();

  cout << "---beginning tests---" << endl;

  {  // stocks
    // get_char()
    if (expo->get_char() != 'e') {
      cout << "expo char incorrect" << endl;
    }
    if (cos->get_char() != 'c') {
      cout << "cos char incorrect" << endl;
    }
    if (sin->get_char() != 's') {
      cout << "sin char incorrect" << endl;
    }
    if (rand->get_char() != 'r') {
      cout << "rand char incorrect" << endl;
    }

    // get_name()
    if (expo->get_name() != "expo") {
      cout << "expo get name incorrect" << endl;
    }
    if (cos->get_name() != "cos") {
      cout << "cos get name incorrect" << endl;
    }

    if (sin->get_name() != "sin") {
      cout << "sin get name incorrect" << endl;
    }

    if (rand->get_name() != "rand") {
      cout << "rand get name incorrect" << endl;
    }

    // get_count(), should default to 0 in constructor
    if (expo->get_count() != 0) {
      cout << "expo get count incorrect" << endl;
    }
    if (cos->get_count() != 0) {
      cout << "cos get count incorrect" << endl;
    }
    if (sin->get_count() != 0) {
      cout << "sin get count incorrect" << endl;
    }
    if (rand->get_count() != 0) {
      cout << "rand get count incorrect" << endl;
    }
  }

  {  // stocklist
    // add stocks to stocklist
    stock_list->add_stock(expo);
    stock_list->add_stock(cos);
    stock_list->add_stock(sin);
    stock_list->add_stock(rand);

    // test stocklist methods
    // stocklist starts with size 8 and increases if necessary
    if (stock_list->get_size() != 8) {
      cout << "stock_list size isnt = 8" << endl;
    }

    // check that the indexing is correct when adding stocks
    if (stock_list->get_index() != 4) {
      cout << "stock_list index incorrect" << endl;
    }

    // check the stocklist can find stocks using their name
    if (stock_list->stock_exists("expo") == false) {
      cout << "couldnt find expo stock" << endl;
    }
    if (stock_list->stock_exists("cos") == false) {
      cout << "couldnt find cos stock" << endl;
    }
    if (stock_list->stock_exists("sin") == false) {
      cout << "couldnt find sin stock" << endl;
    }
    if (stock_list->stock_exists("rand") == false) {
      cout << "couldnt find rand stock" << endl;
    }

    // check clear function behaves correctly
    stock_list->clear();
    if (stock_list->get_index() != 0) {
      cout << "stock_list clear did not change the index correctly" << endl;
    }

    // add stocks to stocklist again for use in later tests
    stock_list->add_stock(expo);
    stock_list->add_stock(cos);
    stock_list->add_stock(sin);
    stock_list->add_stock(rand);
  }

  {  // portfolio
    // add a stock and then check that values have changed correctly
    portfolio->add_stock(expo, 1);

    // tell portfolio to calc it's value
    portfolio->update();

    if (portfolio->get_size() != 1) {
      cout << "portfolio did not resize correctly" << endl;
    }
    if (portfolio->get_stock_quantity(expo) != 1) {
      cout << "portfolio did not update stock count correctly" << endl;
    }
    if (portfolio->get_value() != 2) {
      cout << "portfolio value calculated incorrectly or floating error"
           << endl;
    }
    if (portfolio->get_balance() != 4998) {
      cout << "portfolio balance not updated correctly or floating error"
           << endl;
    }
  }

  {  // saveandload
    // save the data to save.log file
    saver->save(stock_list, portfolio);

    // store some values directly from the stock_list and portfolio, and compare
    // the values before and after loading.

    bool expo_exists = stock_list->stock_exists("expo");
    int expo_quantity = portfolio->get_stock_quantity(expo);
    int stock_list_index = stock_list->get_index();
    int stock_list_size = stock_list->get_size();
    float balance = portfolio->get_balance();
    float value = portfolio->get_value();

    // override stocklist and portfolio using data from file
    saver->load(stock_list, portfolio);
    portfolio->update();  // recalc portfolio value again

    // compare values before and after using saveandload class
    if (expo_exists != stock_list->stock_exists("expo")) {
      cout << "expo exists saveload test failed" << endl;
    }
    if (expo_quantity != portfolio->get_stock_quantity(expo)) {
      cout << "expo quantity saveload test failed" << endl;
    }
    if (stock_list_index != stock_list->get_index()) {
      cout << "stocklist index saveload test failed" << endl;
    }
    if (stock_list_size != stock_list->get_size()) {
      cout << "stocklist size saveload test failed" << endl;
    }
    if (balance != portfolio->get_balance()) {
      cout << "portfolio balance  saveload test failed" << endl;
    }
    if (value != portfolio->get_value()) {
      cout << "portfolio value saveload test failed" << endl;
    }
  }

  {  // line class tests
     // add a value to the values array
    line->add_value(-5.0);

    // update the minimum and maximum of the line
    line->update_minmax();

    if (line->values_index != 1) {
      cout << "line values index test 1 failed" << endl;
    }
    if (line->min != -5.0) {
      cout << "line min test 1 failed" << endl;
    }
    if (line->max != -5.0) {
      cout << "line max test 1 failed" << endl;
    }

    // add anther value and test again to see min max changes
    line->add_value(15.0);
    line->update_minmax();

    if (line->values_index != 2) {
      cout << "line values index test 2 failed" << endl;
    }
    if (line->min != -5.0) {
      cout << "line min test 2 failed" << endl;
    }
    if (line->max != 15.0) {
      cout << "line max test 2 failed" << endl;
    }

    // test draw_char default and set_char()
    if (line->draw_char != 'o') {
      cout << "line draw_char default incorrect" << endl;
    }
    // change line draw_char
    line->set_char('F');
    if (line->draw_char != 'F') {
      cout << "line draw_char changed incorrectly" << endl;
    }
  }

  // stocks are also deleted in stocklist destructor
  delete stock_list;
  delete portfolio;
  delete saver;
  delete line;

  // tests completed
  cout << "---tests completed---" << endl;
  return 0;
}
