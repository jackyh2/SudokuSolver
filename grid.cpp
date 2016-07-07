#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "grid.h"


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

/*
 * Create four-way doubly linked nodes at every intersection of NUMCOLS columns
 * and NUMROWS rows.
 */
 /*
void m_create_cells(Matrix_ExactCover *m) {
	Node *curr, *prev; //create columns first
	//Node *prevcol = nullptr; 
	//(void) prevcol;
	//Node *link = nullptr;

	for (int i = 0; i < NUMCOLS; ++i) {
		prev = nullptr;
		for (int j = 0; j < NUMROWS; ++j) {
			curr = new Node(j,i);
			m->nodes[j][i] = curr;
			if (prev == nullptr) {
				m->header_constraint[i]->head = curr;
				prev = curr;
			}
			curr->up = prev;
			prev->down = curr;
			prev = curr;
			if (i > 0 && i < NUMCOLS - 1) {
				m->nodes[j][i]->left = m->nodes[j][i-1];
				m->nodes[j][i-1]->right = m->nodes[j][i];
			} else if (i == NUMROWS - 1) { //last row
				m->nodes[j][i]->left = m->nodes[j][i-1];
				m->nodes[j][i-1]->right = m->nodes[j][i];
				m->nodes[j][i]->right = m->nodes[j][0];
				m->nodes[j][0]->left = m->nodes[j][i];
			}
		}
		curr->down = m->header_constraint[i]->head;
		m->header_constraint[i]->head->up = curr;
	}
*/
	/*for (int i = 0; i < NUMCOLS; ++i) {// any way to chuck this all into one loop instead of having this top bit?
		curr = new Node(); // perhaps a bool flag like in DLX.cpp?
		curr->colVal = i;
		curr->rowVal = 0;
		m->header_constraint[i]->head = curr;
		if (i) {
			link = m->header_constraint[i-1]->head;
		}
		link->right = curr;
		curr->left = link;
		link = link->down;
		for (int j = 1; j < NUMROWS; ++j) {//create two-way doubly linked column
			prev = curr;
			curr = new Node();
			curr->colVal = i;
			curr->rowVal = j;
			prev->down = curr;
			curr->up = prev;
			curr->left = link;
			link->right = curr; //doubly link with previously created column.
			link = link->down;
		}
		curr->down = m->header_constraint[i]->head;
		m->header_constraint[i]->head->up = curr;
	}*/
	/*link = m->header_constraint[0]->head;
	curr = m->header_constraint[NUMCOLS-1]->head;
	for (int i = 0; i < NUMCOLS ; ++i) { //final links to loop around
		curr->right = link;
		link->left = curr;
	}*/
//}
/*
 *
 * Need to use the conditions calculated below to perform DLX on the input sudoku values.
 *
 */


/*
void m_create_cells(Matrix_ExactCover *m, const std::vector<int>& input) {
	(void) NUMROWS; //compiler error
	assert (input.size() == NUMBOXES);
	int val, s_row, s_col, ec_row, s_block;
	int ec_cond[NUM_CONDS];
	Node *cell, *prev = nullptr;
		
	s_row = 0;
	s_col = 0;
	s_block = 0;
	//Construct the matrix
	for (auto it = input.begin(); it != input.end(); ++it) {
		//DEBUG
		int debugInt = *it;

		if ((val = *it)) { //only non-zero values
			std::cout << "Input: " << debugInt << " At: " << "(" << s_row << "," << s_col << ") creates";


			ec_row = val + s_row*MULT_R_ROW + s_col*MULT_R_COL;
			ec_cond[0] = COND0 + it - input.begin(); //position in sudoku 
			ec_cond[1] = COND1 + s_row*MULT_C + val;
			ec_cond[2] = COND2 + s_col*MULT_C + val;
			ec_cond[3] = COND3 + (s_block-1)*MULT_C + val;
			

			for (int j = 0; j < NUM_CONDS; ++j){
				cell = new Node();
				cell->colVal = ec_cond[j];
				cell->rowVal = ec_row;
				cell->left = cell;
				cell->right = cell;

				//For now, super inefficient, just goes along the constraint headers until we find
				Node_Constraint *column_Constraint = m->get_Column_Constraint(cell->colVal);
				column_Constraint->insertNewNode(cell);
				if (prev != nullptr) {
					prev->insertNewRowNode(cell);
				}
				prev = cell;

				//put constraint header into vector for O(1) access?
				//append this node to the column's LL
				//join the entire row doubly horizontally

				//DEBUG
				std::cout << "(" << cell->rowVal << "," << cell->colVal << ")" << " ";
				
			}
			std::cout << std::endl;
		}
		s_col = (s_col+1)%9; //update sudoku position
		s_row += !s_col;
		s_block = 1 + 3*(s_row/3)+(s_col/3);
		//++it;

	}
}
*/
void m_create_cells(Matrix_ExactCover *m) {
	Node *cell, *prev = nullptr;
	int ec_cond[NUM_CONDS];
	int s_block = 0;
	Node_Constraint *col_Constraint;
	for (int i = 0; i < 9; ++i) { //9 rows
		for (int j = 0; j < 9; ++j) { //9 columns
			for (int k = 1; k < 10; ++k) { //9 symbols
				s_block = 1 + 3*(i/3)+(j/3); //index blocks [1,9]
				ec_row = i*MULT_R_ROW + j*MULT_R_COL + k;
				ec_cond[0] = COND0 + i*MULT_9 + j; //position in sudoku [0,80]
				ec_cond[1] = COND1 + i*MULT_9 + k; //symbol in row
				ec_cond[2] = COND2 + j*MULT_9 + k; //symbol in row
				ec_cond[3] = COND3 + (s_block - 1)*MULT_9 + k;
				for (int n = 0; n < NUM_CONDS; ++n) {
					cell = new Node(ec_row, ec_cond[n]);
					//cell->rowVal = ec_row;
					//cell->colVal = ec_cond[n];
					col_Constraint = m->header_constraint[cell->colVal];
					col_Constraint->insertNewNode(cell);
					if (prev != nullptr) {
						prev->insertNewRowNode(cell);
					}
					prev = cell;
				}
			}
		}
	}
}


Node_Constraint *Matrix_ExactCover::get_Column_Constraint(int col) {
	return header_constraint[col];
}

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
}