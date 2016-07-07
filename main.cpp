#include <iostream>
#include <vector>

#include "DLX.h"

int main() {
	//DO SOMETHING:
	SolutionSet s;
	std::vector<int> input(NUMBOXES);
	for (int i = 0; i < NUMBOXES; ++i) {
		std::cin >> input[i];
	}
	
	Matrix_ExactCover *ecm = m_create_grid();
	s.m = ecm;
	//s.m_cover_inputs(input);
	Node *node = s.m->get_Row_Node(1,0); s.insertNewRow(node);
	s.m->printRowByRow();

}