#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H

#include "stocks/StockList.h"
#include "stocks/Portfolio.h"

#include <sstream>

class SaveAndLoad {
public:
    // constructor
    SaveAndLoad();

    // destructor
    ~SaveAndLoad();

    // save the portfolio to a file
    bool save(StockList *stocklist, Portfolio *portfolio);

    // load the portfolio from a file
    bool load(StockList *stocklist, Portfolio *portfolio);

};


#endif //SAVEANDLOAD_H
