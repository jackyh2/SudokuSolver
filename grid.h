#ifndef GRID_H
#define GRID_H

#include <vector>

#include "node.h"

struct Matrix_ExactCover {
	Node_Constraint *head;

	//Operations
	Node_Constraint *get_Column_Constraint(int col);
};


Matrix_ExactCover *m_create_header();
void m_create_cells(Matrix_ExactCover *m, const std::vector<int>& input);

#endif 