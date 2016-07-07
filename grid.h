#ifndef GRID_H
#define GRID_H

#include <vector>

#include "node.h"
//#include "DLX.h"

//Standard 9x9 sudoku
const int NUMCOLS = 324;
const int NUMROWS = 729;
const int NUMBOXES = 81;
const int MULT_R_ROW = 81;
const int MULT_R_COL = 9;

//COND0: only one of value in each of 81 cells
//COND1: only one of 1-9 in each of 9 rows
//COND2: only one of 1-9 in each of 9 columns
//COND3: only one of 1-9 in each of 9 blocks
const int COND0 = 0; //the starting column for each condition
const int COND1 = 80;
const int COND2 = 161;
const int COND3 = 242;
const int NUM_CONDS = 4;
const int MULT_9 = 9;

struct Matrix_ExactCover {
	Matrix_ExactCover(): head(nullptr), header_constraint(NUMCOLS) {}
	Node_Constraint *head;
	std::vector<Node_Constraint *> header_constraint;
	//std::vector<std::vector<Node *>> nodes;
	//Operations
	Node_Constraint *get_Column_Constraint(int col);
	Node *get_Row_Node(int row, int col);
	void printRowByRow();
};


Matrix_ExactCover *m_create_grid();
void m_create_cells(Matrix_ExactCover *m);
//void m_create_cells(Matrix_ExactCover *m, const std::vector<int>& input);

#endif 