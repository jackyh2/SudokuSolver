#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "grid.h"


static void m_create_cells(Matrix_ExactCover *m);
//Following the rows and columns layout in
//http://www.stolaf.edu/people/hansonr/sudoku/exactcovermatrix.htm

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
	Matrix_ExactCover *m = new Matrix_ExactCover();

	for (int i = 0; i < NUMCOLS; ++i) {
		curr = new Node_Constraint(i);
		m->header_constraint[i] = curr;
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
 *Create the ECM, with cells determined by the 4 conditions
 */
static void m_create_cells(Matrix_ExactCover *m) {
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
				for (int n = 0; n < NUM_CONDS; ++n) {
					cell = new Node(ec_row, ec_cond[n]);
					col_Constraint = m->header_constraint[cell->colVal];
					col_Constraint->insertNewNode(cell);
					if (prev != nullptr) { //wait till one node already exists in row
						prev->linkWithRow(cell);
					}
					prev = cell;
				}
			}
		}
	}
}

/*
 *Return pointer to a specified contraint node
 */
Node_Constraint *Matrix_ExactCover::get_Column_Constraint(int col) {
	return header_constraint[col];
}

/*
 *Return the pointer to the specified node
 */
Node *Matrix_ExactCover::get_Node(int row, int col) {
	Node *cell = header_constraint[col]->head;
	do {
		if (cell->rowVal == row) return cell;
		cell = cell->down;
	} while (cell != header_constraint[col]->head);
	return nullptr;
}

/*
 *Print to stdout the ECM a row at a time.
 */
void Matrix_ExactCover::printRowByRow() {
	std::vector<std::vector<Node *>> matrix(NUMROWS);
	Node_Constraint *iter = head, *currCol;
	Node *currNode;
	do {
		if (head == nullptr) break;//empty ECM
		currCol = get_Column_Constraint(iter->colVal);//for each column
		currNode = currCol->head; 
		if (currNode == nullptr) {//empty column
			iter = iter->right;
			continue;
		}
		do { //for each node in a column
			int row = currNode->rowVal;
			matrix[row - 1].push_back(currNode);//push to appropriate row vector (row [1,729])
			currNode = currNode->down;
		} while (currNode != currCol->head);
		iter = iter->right;
	} while (iter != head);

	for (int i = 0; i < NUMROWS; ++i) {
		std::cout << "G: " << (i+1)/9 + 1 << " | R: " << i+1 << "  ";
		for (auto it = matrix[i].begin(); it != matrix[i].end(); ++it) {
			std::cout << "(" << (*it)->rowVal << "," << (*it)->colVal << ") ";
		}
		std::cout << std::endl;
	}

}