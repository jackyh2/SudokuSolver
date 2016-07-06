all: SudokuSolver

SudokuSolver: main.o node.o grid.o
	g++ main.o node.o grid.o -o SudokuSolver

main.o: main.cpp grid.h
	g++ -std=c++11 -Wall -Werror -c main.cpp

grid.o: grid.cpp grid.h node.h node.cpp
	g++ -std=c++11 -Wall -Werror -c grid.cpp
	
node.o: node.cpp node.h
	g++ -std=c++11 -Wall -Werror -c node.cpp

clean:
	rm *o SudokuSolver