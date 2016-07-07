all: SudokuSolver

SudokuSolver: main.o node.o grid.o DLX.o
	g++ -std=c++11 -Wall -Werror main.o node.o grid.o DLX.o -o SudokuSolver

main.o: main.cpp DLX.h
	g++ -std=c++11 -Wall -Werror -c main.cpp
	
node.o: node.cpp node.h DLX.h
	g++ -std=c++11 -Wall -Werror -c node.cpp

grid.o: grid.cpp grid.h node.h node.cpp
	g++ -std=c++11 -Wall -Werror -c grid.cpp

DLX.o: grid.cpp grid.h node.h node.cpp DLX.cpp DLX.h
	g++ -std=c++11 -Wall -Werror -c DLX.cpp

clean:
	rm *o SudokuSolver