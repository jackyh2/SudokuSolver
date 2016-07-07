#ifndef GRID_H
#define GRID_H

#include <vector>

#include "node.h"

//Standard 9x9 sudoku
const int NUMCOLS = 324;
const int NUMROWS = 729;

struct Matrix_ExactCover {
	Matrix_ExactCover(): head(nullptr), header_constraint(NUMCOLS), nodes(NUMROWS, std::vector<Node *>(NUMCOLS)) {}
	Node_Constraint *head;
	std::vector<Node_Constraint *> header_constraint;
	std::vector<std::vector<Node *>> nodes;
	//Operations
	Node_Constraint *get_Column_Constraint(int col);
};


Matrix_ExactCover *m_create_grid();
void m_create_cells(Matrix_ExactCover *m);
//void m_create_cells(Matrix_ExactCover *m, const std::vector<int>& input);

#endif 