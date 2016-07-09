#include <iostream>
#include <vector>

#include "DLX.h"

int main() {
	SolutionSet s;
	s.solved = false;
	std::vector<int> input(NUMBOXES);
	//Need to check correct number of inputs
	for (int i = 0; i < NUMBOXES; ++i) {
		std::cin >> input[i];
	}

	Matrix_ExactCover *ecm = m_create_grid();

	s.m = ecm;

	bool valid = s.m_cover_inputs(input);

	
	if (valid) {
		s.solve();
	} else {
		std::cout << "No Solution Found." << std::endl;
	}
}	