//
// Created by gabriel on 16/10/22.
//

#include "SaveAndLoad.h"

#include <fstream>

#include "stocks/ExponentialStock.h"
#include "stocks/RandomStock.h"
#include "stocks/SinStock.h"
#include "stocks/CosStock.h"

std::vector <std::string> split(const std::string &s, char delimiter) //function to split strings on comma
{
    std::vector <std::string> splits;
    std::string split;
    std::istringstream ss(s);
    while (std::getline(ss, split, delimiter)) {
        splits.push_back(split);
    }
    return splits;
}

// save the portfolio to a file
bool SaveAndLoad::save(StockList *stocklist, Portfolio *portfolio) {


    // Open save file
    ofstream saveFile;
    saveFile.open("save.dat");

    // Write balance of portfolio
    saveFile << portfolio->get_balance() << endl;

    // Write stocklist header
    saveFile << endl << endl << "stocklist" << endl;

    saveFile << stocklist->get_index() << endl;

    // Write the properties of each stock in the stock list, format: name,value,count,type (see type.txt in stocks)
    for (int i = 0; i < stocklist->get_index(); i++) {
        saveFile << (stocklist->get_stock(i))->get_name() << "," << (stocklist->get_stock(i))->get_value() << ","
                 << (stocklist->get_stock(i))->get_count() << "," << (stocklist->get_stock(i))->get_type() << endl;
    }

    // Close file
    saveFile.close();
    return true;
}

// load the portfolio from a file
bool SaveAndLoad::load(StockList *stocklist, Portfolio *portfolio) {

    // Open file for reading
    ifstream saveFile;

    string line; // Temp string for line of text to be stored to
    saveFile.open("save.dat");
    stocklist->clear(); // Clear current stocklist and portfolio
    portfolio->clear();

    // Portfolio loading

    getline(saveFile, line); // Balance
    float balance = stof(line); // store balance to be written last

    // Stocklist loading

    do {
        getline(saveFile, line);
    } while (line != "stocklist"); // Go until stocklist header is reached

    getline(saveFile, line);
    int totalStocks = stoi(line);

    for (int i = 0; i < totalStocks; i++) { // For each stock, add them to the stocklist and portfolio as needed
        getline(saveFile, line); // format: name, value, count, type
        auto splitLine = split(line, ',');
        switch (stoi(splitLine[3])) { // Create new stocks according to type
            case 0:
                stocklist->add_stock(new ExponentialStock(stof(splitLine[1]), splitLine[0]));
                break;
            case 1:
                stocklist->add_stock(new RandomStock(stof(splitLine[1]), splitLine[0]));
                break;
            case 2:
                stocklist->add_stock(new CosStock(splitLine[0]));
                break;
            case 3:
                stocklist->add_stock(new SinStock(splitLine[0]));
                break;
        }
        if (stoi(splitLine[2]) > 0) { // Add stocks to portfolio if needed
            Stock *stockToAdd = stocklist->get_stock(splitLine[0]);
            portfolio->add_stock(stockToAdd, stoi(splitLine[2]));
        }
    }
    portfolio->set_balance(balance); // Set final balance of portfolio
    saveFile.close(); // Close file for reading
    return true;
}

// constructor
SaveAndLoad::SaveAndLoad() = default;

// destructor
SaveAndLoad::~SaveAndLoad() = default;