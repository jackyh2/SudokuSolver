#include <iostream>
#include <vector>

#include "grid.h"

int main() {
	//DO SOMETHING:
	std::vector<int> input(81);
	for (int i = 0; i < 81; ++i) {
		std::cin >> input[i];
	}
	Matrix_ExactCover *ecm = m_create_header();
	m_create_cells(ecm, input);

}