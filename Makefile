all: SudokuSolver

SudokuSolver: main.o node.o
	g++ main.o node.o -o SudokuSolver

main.o: main.cpp 
	g++ -std=c++11 -Wall -Werror -c main.cpp
	
node.o: node.cpp node.h
	g++ -std=c++11 -Wall -Werror -c node.cpp

clean:
	rm *o SudokuSolver