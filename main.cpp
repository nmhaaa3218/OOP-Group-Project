#include "Merchant.h"
#include "SaveAndLoad.h"
#include "stocks/CosStock.h"
#include "stocks/ExponentialStock.h"
#include "stocks/RandomStock.h"
#include "stocks/SinStock.h"

int main() {
  // set random seed for all the rand() calls in Stocks
  srand(time(0));

  // initialise ncurses
  initscr();

  // construct ui outside the Display class to enable access to it from main
  UI *ui = new UI();

  // create saveandload object
  SaveAndLoad saver = SaveAndLoad();

  // create display
  Display *display = new Display();

  // assign the ui to the display
  display->ui = ui;

  // create a StockList which holds every Stock
  StockList *stock_list = new StockList();
  Portfolio *portfolio = new Portfolio();

  // give merchant the relevant objects
  Merchant merchant = Merchant(stock_list, portfolio, display);

  {  // adding to stock list
    stock_list->add_stock(new RandomStock(0, "BGA"));
    stock_list->add_stock(new RandomStock(0, "MYR"));
    stock_list->add_stock(new ExponentialStock(2, "NAB"));
    stock_list->add_stock(new ExponentialStock(2, "GME"));
    stock_list->add_stock(new SinStock("HSA"));
    stock_list->add_stock(new SinStock("BHP"));
    stock_list->add_stock(new CosStock("WES"));
    stock_list->add_stock(new CosStock("CBA"));
  }

  bool loop = true;
  while (loop) {
    // catch all user inputted chars
    char c = getch();

    // if not paused, update everything
    if (!display->paused) {
      // add any new stocks to the display
      display->add_Portfolio(portfolio);

      // update the Portfolio once per frame
      portfolio->update();

      // update all stocks
      stock_list->update_stocks();

      // refresh display
      display->refresh_all();

      // print all stock value's to ui neatly
      ui->show_stock_info(stock_list);

      // show keybinds on ui
      ui->show_controls();

      // print portfolio value and balance to user ui
      ui->print("portfolio value: " + std::to_string(portfolio->get_value()), 1,
                7);

      ui->print(
          "portfolio balance: " + std::to_string(portfolio->get_balance()), 1,
          8);
    }

    // perform actions depending on input
    switch (c) {
      case 'q':
      case 'Q':
        // end game
        loop = false;

        // save game state
        saver.save(stock_list, portfolio);
        break;

      case 'p':
      case 'P':
        // toggle display pause
        if (display->paused) {
          display->unpause();
        } else {
          display->pause();
        }
        break;

      case 'k':
      case 'K':
        // manually save stocklist and portfolio to a file
        saver.save(stock_list, portfolio);
        break;

      case 'l':
      case 'L':
        // load stocklist and portfolio from file
        saver.load(stock_list, portfolio);
        break;

      case 'b':
      case 'B':
        // pause updates
        display->pause();

        // enter buying mode
        merchant.buy();

        // resume updates
        display->unpause();
        break;

      case 's':
      case 'S':
        // pause updates
        display->pause();

        // enter selling mode
        merchant.sell();

        // resume updates
        display->unpause();
        break;
    }

    // delay between each frame
    napms(100);
  }

  // clean up memory
  delete display;
  delete stock_list;
  delete portfolio;
  // ui is deleted within display despite being used in main
  // stocks are deleted within stock_list

  // end ncurses, deleting all window objects and freeing memory correctly
  endwin();
  return 0;
}
