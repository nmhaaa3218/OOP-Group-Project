build:
	g++ -g -Wall main.cpp Display.cpp Graph.cpp UI.cpp stocks/Line.cpp stocks/Portfolio.cpp stocks/ExponentialStock.cpp stocks/Stock.cpp stocks/RandomStock.cpp stocks/StockList.cpp SaveAndLoad.cpp Merchant.cpp stocks/TrigStock.cpp stocks/SinStock.cpp stocks/CosStock.cpp -o stockchart.o -lcurses
	
run:
	g++ -g -Wall main.cpp Display.cpp Graph.cpp UI.cpp stocks/Line.cpp stocks/Portfolio.cpp stocks/ExponentialStock.cpp stocks/Stock.cpp stocks/RandomStock.cpp stocks/StockList.cpp SaveAndLoad.cpp Merchant.cpp stocks/TrigStock.cpp stocks/SinStock.cpp stocks/CosStock.cpp -o stockchart.o -lcurses
	./stockchart.o

clean:
	rm -rf ./stockchart.o ./main_log.txt ./save.dat ./test.o

test:
	g++ -g -Wall test.cpp Display.cpp Graph.cpp UI.cpp stocks/Line.cpp stocks/Portfolio.cpp stocks/ExponentialStock.cpp stocks/Stock.cpp stocks/RandomStock.cpp stocks/StockList.cpp SaveAndLoad.cpp Merchant.cpp stocks/TrigStock.cpp stocks/SinStock.cpp stocks/CosStock.cpp -o test.o -lcurses
	./test.o