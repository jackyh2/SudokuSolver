#include <iostream>
#include <vector>

#include "DLX.h"

int main() {
	//We read in the input: First input is in Sudoku grid position (0,0), next is (0,1) etc.
	//Numbers 1-9 for a known symbol, number 0 for an unknown symbol.
	std::vector<int> input(NUMBOXES);
	
	for (int i = 0; i < NUMBOXES; ++i) {
		std::cin >> input[i];
	}
	
	SolutionSet s;
	//If this function returns false, then the input grid is invalid.
	if (s.m_cover_inputs(input)) {
		s.solve();
	} else {
		std::cout << "No Solution Found." << std::endl;
	}
}	