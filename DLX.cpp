#include <iostream>
#include <cstring>

#include "DLX.h"


void SolutionSet::insertNewRow(Node *n) {
	rows.push(n);
	Node *rowCurr, *colCurr, *removeCurr;
	bool flag = true;
	for (rowCurr = n; rowCurr != n || flag; rowCurr = rowCurr->right) {
		flag = false;
		for (colCurr = rowCurr->up; colCurr != rowCurr; colCurr = colCurr->up) {
			for (removeCurr = colCurr->right; removeCurr != colCurr; removeCurr = removeCurr->right) {
				removeCurr->removeUpDown();
				Node_Constraint *tmp = m->get_Column_Constraint(removeCurr->colVal);
				tmp->size--;
				//std::cout << tmp->size << std::endl;
				if (tmp->head == removeCurr) tmp->head = removeCurr->down;
				if (tmp->head == removeCurr) tmp->head = nullptr;
			}
		}
		Node_Constraint *currConstraint = m->get_Column_Constraint(rowCurr->colVal);
		currConstraint->removeLeftRight();
		if (m->head == currConstraint) m->head = currConstraint->right;
		if (m->head == currConstraint) m->head = nullptr;
	}
}

Node *SolutionSet::deletePrevRow() {
	Node *n = rows.top(); 
	rows.pop();
	Node *rowCurr, *colCurr, *removeCurr;
	bool flag = true;
	for (rowCurr = n; rowCurr != n || flag; rowCurr = rowCurr->left) {
		flag = false;
		for (colCurr = rowCurr->down; colCurr != rowCurr; colCurr = colCurr->down) {
			for (removeCurr = colCurr->left; removeCurr != colCurr; removeCurr = removeCurr->left) {
				removeCurr->restoreUpDown();
				Node_Constraint *tmp = m->get_Column_Constraint(removeCurr->colVal);
				tmp->size++;
				if (tmp->head == nullptr) tmp->head = removeCurr;
			}
		}
		Node_Constraint *currConstraint = m->get_Column_Constraint(rowCurr->colVal);
		currConstraint->restoreLeftRight();
		if (m->head == nullptr) m->head = currConstraint;
		if (currConstraint->colVal < m->head->colVal) m->head = currConstraint;
	}
	return n;
}

void SolutionSet::solve() {

	if (m->head == nullptr) { //we are done.
		return;
	} else {
		//Pick via S heuristic.
		int size = m->head->size;
		Node_Constraint *min = m->head;
		Node_Constraint *curr = m->head->right;
		while (curr != m->head) {
			if (curr->size < size) {
				size = curr->size;
				min = curr;
			}
			curr = curr->right;
		}
		//Pick any row:
		Node *row = min->head;
		if (row == nullptr) { //no rows:
			Node *prev = deletePrevRow();
			row = prev->down;
		}
		insertNewRow(row);
		solve();
	}

	/*int size = MAXSIZE;
	Node_Constraint *colCurr, *col_SH;
	Node *rowTest;

	while (head != nullptr) {
		colCurr = head->right;
		col_SH = head->right;
		do { //check sizes
			if (colCurr->size < size) {
				size = colCurr->size;
				sol_SH = colCurr
			} 
		} while (colCurr != head);
		//we have a column - now pick rows
		rowTest = col_SH->head->down;
		if (rowTest = nullptr) {
			deletePrevRow;
		}
		do {
			insertNewRow(rowTest);
		} while (rowTest != col_SH->head)
		
	}*/
			
}

void SolutionSet::m_cover_inputs(const std::vector<int>& input) {
	int val, s_row, s_col, ec_row;
	s_row = 0;
	s_col = 0;
	for (auto it = input.begin(); it != input.end(); ++it) {
		if ((val = *it)) {
			ec_row = val + s_row*MULT_R_ROW + s_col*MULT_R_COL;
			insertNewRow(m->get_Row_Node(ec_row, COND0 + s_row*MULT_9 + s_col));
		}
		s_col = (s_col+1)%9; //update sudoku position
		s_row += !s_col;
	}
}

void SolutionSet::m_restore_inputs() {
	while (!(rows.empty())) {
		deletePrevRow();
	}
}

void SolutionSet::printSolution() {
	int Sudoku[9][9];
	memset(Sudoku, 0, 81*sizeof(int));
	while (!(rows.empty())) {
		int row,col,symbol;

		Node *currRow = rows.top();
		rows.pop();

		symbol = ((currRow->rowVal - 1) % 9) + 1;
		row = (currRow->rowVal - 1)/ 81;
		col = ((currRow->rowVal - 1)/ 9) % 9;
		Sudoku[row][col] = symbol;
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			std::cout << Sudoku[i][j] << " ";
		}
		std::cout << std::endl;
	}

}
