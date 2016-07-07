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
				if (tmp->head == removeCurr) tmp->head = removeCurr->down;
			}
		}
		Node_Constraint *currConstraint = m->get_Column_Constraint(rowCurr->colVal);
		currConstraint->removeLeftRight();
		if (m->head == currConstraint) m->head = currConstraint->right;
	}
}

void SolutionSet::deletePrevRow() {
	Node *n = rows.top(); 
	rows.pop();
	Node *rowCurr, *colCurr, *removeCurr;
	bool flag = true;
	for (rowCurr = n; rowCurr != n || flag; rowCurr = rowCurr->left) {
		flag = false;
		for (colCurr = rowCurr->down; colCurr != rowCurr; colCurr = colCurr->down) {
			for (removeCurr = colCurr->left; removeCurr != colCurr; removeCurr = removeCurr->left) {
				removeCurr->restoreUpDown();
			}
		}
		Node_Constraint *currConstraint = m->get_Column_Constraint(rowCurr->colVal);
		currConstraint->restoreLeftRight();
		if (currConstraint->colVal < m->head->colVal) m->head = currConstraint;
	}
}

void SolutionSet::solve() {
	//Recursive function Algorithm X goes here..
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