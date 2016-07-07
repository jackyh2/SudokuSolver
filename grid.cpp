#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "grid.h"
#include "DLX.h"


//Following the rows and columns layout in
//http://www.stolaf.edu/people/hansonr/sudoku/exactcovermatrix.htm
const int MULT_R_ROW = 81;
const int MULT_R_COL = 9;
//COND0: only one of value in each of 81 cells
//COND1: only one of 1-9 in each of 9 rows
//COND2: only one of 1-9 in each of 9 columns
//COND3: only one of 1-9 in each of 9 blocks
const int MULT_C = 9;
const int COND0 = 0; //the starting column for each condition
const int COND1 = 80;
const int COND2 = 161;
const int COND3 = 242;
const int NUM_CONDS = 4;
const int NUMBOXES = 81;
const int MULT_9 = 9;
/*_______ sudoku block layout
 *|1|2|3|
 *|-----|
 *|4|5|6|
 *|-----|
 *|7|8|9|
 *|-----|
 */

/*
 * Create the constraints header, then continues to m_create_cells
 */
Matrix_ExactCover *m_create_grid() {

	Node_Constraint *curr, *prev = nullptr;
	//std::vector<Node_Constraint *> header_constraint(NUMCOLS);
	Matrix_ExactCover *m = new Matrix_ExactCover();
	//First contraint node
	//m->head = new Node_Constraint();
	//prev = m->head;
	//m->header_constraint[0] = m->head;

	//All other contraint nodes in doubly LL
	for (int i = 0; i < NUMCOLS; ++i) {
		curr = new Node_Constraint(i);
		curr->head = nullptr;               //added THIS
		m->header_constraint[i] = curr; //could this be an array?
		if (prev == nullptr) prev = curr;
		curr->left = prev;
		prev->right = curr;
		prev = curr;
	}
	m->head = m->header_constraint[0];
	//Circular LL of contraints
	curr->right = m->head;
	m->head->left = curr;
	m_create_cells(m);
	return m;
}


void m_create_cells(Matrix_ExactCover *m) {
	Node *cell, *prev = nullptr;
	int ec_cond[NUM_CONDS];
	int s_block = 0;
	int ec_row;
	Node_Constraint *col_Constraint;
	for (int i = 0; i < 9; ++i) { //9 rows
		for (int j = 0; j < 9; ++j) { //9 columns
			s_block = 1 + 3*(i/3)+(j/3); //index blocks [1,9]
			ec_cond[0] = COND0 + i*MULT_9 + j; //position in sudoku [0,80]
			for (int k = 1; k < 10; ++k) { //9 symbols
				ec_row = i*MULT_R_ROW + j*MULT_R_COL + k;
				ec_cond[1] = COND1 + i*MULT_9 + k; //symbol in row
				ec_cond[2] = COND2 + j*MULT_9 + k; //symbol in row
				ec_cond[3] = COND3 + (s_block - 1)*MULT_9 + k;
				prev = nullptr;
				std::cout << "ECM Row " << ec_row << " Symbol " << k << " at " << "(" << i << "," << j << "): ";
				for (int n = 0; n < NUM_CONDS; ++n) {
					cell = new Node(ec_row, ec_cond[n]);
					col_Constraint = m->header_constraint[cell->colVal];
					col_Constraint->insertNewNode(cell);
					if (prev != nullptr) {
						prev->insertNewRowNode(cell);
					}
					prev = cell;
					std::cout << "(" << cell->rowVal << "," << cell->colVal << ")" << " ";
				}
				std::cout << std::endl;
			}
		}
	}
}


Node_Constraint *Matrix_ExactCover::get_Column_Constraint(int col) {
	return header_constraint[col];
}

Node *Matrix_ExactCover::get_Row_Node(int row) {
	Node *cell;
	for (cell = header_constraint[0]->head; cell->rowVal != row; cell = cell->down) {}
	return cell;
}

/*
void getRidOfCompileErrors() {
	int a;
	a = MULT_R_ROW;
	a = MULT_R_COL;
	a = MULT_C;
	a = COND0;
	a = COND1;
	a = COND2;
	a = COND3;
	a = NUM_CONDS;
	a = NUMBOXES;
}*/

void m_cover_inputs(SolutionSet *s, Matrix_ExactCover *m, const std::vector<int>& input) {
	int val, s_row, s_col, ec_row;
	s_row = 0;
	s_col = 0;
	for (auto it = input.begin(); it != input.end(); ++it) {
		if ((val = *it)) {
			ec_row = val + s_row*MULT_R_ROW + s_col*MULT_R_COL;
			insertNewRow(m->get_Row_Node(ec_row));
		}
		s_col = (s_col+1)%9; //update sudoku position
		s_row += !s_col;
	}
}