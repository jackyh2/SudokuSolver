all: SudokuSolver

SudokuSolver: main.o node.o grid.o DLX.o
	g++ -std=c++11 -Wall -Werror -g main.o node.o grid.o DLX.o -o SudokuSolver

main.o: main.cpp DLX.h grid.h
	g++ -std=c++11 -Wall -Werror -g -c main.cpp
	
node.o: node.cpp node.h DLX.h
	g++ -std=c++11 -Wall -Werror -g -c node.cpp

grid.o: grid.cpp grid.h node.h node.cpp
	g++ -std=c++11 -Wall -Werror -g -c grid.cpp

DLX.o: grid.cpp grid.h node.h node.cpp DLX.cpp DLX.h
	g++ -std=c++11 -Wall -Werror -g -c DLX.cpp

clean:
	rm *o SudokuSolver