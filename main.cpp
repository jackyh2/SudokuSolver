#include <iostream>
#include <vector>

#include "DLX.h"

int main() {
	//DO SOMETHING:
	SolutionSet s;
	s.solved = false;
	std::vector<int> input(NUMBOXES);
	for (int i = 0; i < NUMBOXES; ++i) {
		std::cin >> input[i];
	}
	std::cout << "1" << std::endl;
	Matrix_ExactCover *ecm = m_create_grid();
	std::cout << "2" << std::endl;
	s.m = ecm;
	std::cout << "3" << std::endl;
	s.m->printRowByRow();
	std::cout << "4" << std::endl;
	s.m_cover_inputs(input);
	std::cout << "5" << std::endl;
	s.m->printRowByRow();
	std::cout << "6" << std::endl;
	//s.m_restore_inputs();
	
	s.solve();
	std::cout << "7" << std::endl;
	s.m->printRowByRow();
	std::cout << "8" << std::endl;
	s.printSolution();
}	