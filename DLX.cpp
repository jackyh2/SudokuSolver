#include "DLX.h"


void SolutionSet::insertNewRow(Node *n) {
	rows.push(n);
	Node *rowCurr, *colCurr, *removeCurr;
	for (rowCurr = n->right; rowCurr != n; rowCurr = rowCurr->right) {
		for (colCurr = rowCurr->up; colCurr != rowCurr; colCurr = colCurr->up) {
			for (removeCurr = colCurr->right; removeCurr != colCurr; removeCurr = removeCurr->right) {
				removeCurr->removeUpDown();
			}
		}
		Node_Constraint *currConstraint = m->get_Column_Constraint(rowCurr->colVal);
		currConstraint->removeLeftRight();
	}
}

void SolutionSet::deletePrevRow() {
	Node *n = rows.top(); 
	rows.pop();
	Node *rowCurr, *colCurr, *removeCurr;
	for (rowCurr = n->left; rowCurr != n; rowCurr = rowCurr->left) {
		for (colCurr = rowCurr->down; colCurr != rowCurr; colCurr = colCurr->down) {
			for (removeCurr = colCurr->left; removeCurr != colCurr; removeCurr = removeCurr->left) {
				removeCurr->restoreUpDown();
			}
		}
		Node_Constraint *currConstraint = m->get_Column_Constraint(rowCurr->colVal);
		currConstraint->restoreLeftRight();
	}
}