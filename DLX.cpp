#include <iostream>
#include <cstring>

#include "DLX.h"

/*
 *Add a chosen ec_row to the solution set.
 *As per Algo X, all other rows that satisfy contraints satisfied by the chosen row are covered
 */
void SolutionSet::insertNewRow(Node *n) {
	solRows.push(n);
	Node *rowCurr, *colCurr, *remCurr;//removeCurr
	rowCurr = n;
	do { //for the entire row at n, at each column of these nodes:
		for (colCurr = rowCurr->up; colCurr != rowCurr; colCurr = colCurr->up) {//for whole col, non-inclusive of n
			//for the entire row, non-inclusive of starting node
			for (remCurr = colCurr->right; remCurr != colCurr; remCurr = remCurr->right) {
				remCurr->removeUpDown(); //cover vertical links
				Node_Constraint *tmp = m->get_Column_Constraint(remCurr->colVal);
				tmp->size--; //a row has been removed
				//adjust the constraint head
				if (tmp->head == remCurr) tmp->head = remCurr->down;
				if (tmp->head == remCurr) tmp->head = nullptr;
			}
		}
		Node_Constraint *currConstraint = m->get_Column_Constraint(rowCurr->colVal);
		currConstraint->removeLeftRight(); //hide the satisfied constraints
		if (m->head == currConstraint) m->head = currConstraint->right;
		if (m->head == currConstraint) m->head = nullptr;

		rowCurr = rowCurr->right;
	} while (rowCurr != n);
}


/*
 *Remove the most recent row added to the solution set and return a pointer
 *Dancing Links is performed in the reverse order
 */
Node *SolutionSet::restorePrevRow() {
	Node *n = solRows.top();
	solRows.pop();
	Node *rowCurr, *colCurr, *remCurr;
	rowCurr = n;
	do {
		for (colCurr = rowCurr->down; colCurr != rowCurr; colCurr = colCurr->down) {
			for (remCurr = colCurr->left; remCurr != colCurr; remCurr = remCurr->left) {
				remCurr->restoreUpDown();
				Node_Constraint *tmp = m->get_Column_Constraint(remCurr->colVal);
				tmp->size++;
				if (tmp->head == nullptr) tmp->head = remCurr;//no longer empty column
			}
		}
		Node_Constraint *currConstraint = m->get_Column_Constraint(rowCurr->colVal);
		currConstraint->restoreLeftRight(); //restore a hidden constraint
		if (m->head == nullptr) m->head = currConstraint;
		if (currConstraint->colVal < m->head->colVal) m->head = currConstraint;//m->head points to lowest constraint

		rowCurr = rowCurr->left;
	} while (rowCurr != n);

	return n;
}

/*
 *Solve the ECM recursively by appliaction of Algo X
 *bool solved can be used to print one or multiple solutions.
 */
void SolutionSet::solve() {
	if (m->head == nullptr) { //we are done.
		solved = true; //early return after first solution printed
		//Print without altering stack if multiple solutions desired
		std::stack<Node *> tmp = solRows;
		std::cout << "Solution number " << ++solutionNum << std::endl << std::endl;
		printSolution();
		std::cout << std::endl;
		solRows = tmp;
		return;
	} else {
		if (solved == true) return; //optional statement for faster completion
		int size = m->head->size; //Pick via S heuristic.
		Node_Constraint *min = m->head;
		Node_Constraint *curr = m->head->right;
		while (curr != m->head) {
			if (curr->size < size) {
				size = curr->size;
				min = curr;
			}
			curr = curr->right;
		} //found the column with least rows

		//no rows in this column
		if (min->head == nullptr) {
			return;//backtrack and pick another row
		} 

		Node *row = min->head;
		do { //for every row in the unsatisfied constraint
			if (solved == true) return;//early return for first solution
			insertNewRow(row);
			solve(); //continue to solve recursively.
			//At this point one of the early returns have been reached OR no rows in a column
			//Respectively, we can exit OR restore from solution set and pick the next row.
			if (solved == true) return;
			restorePrevRow();

			row = row->down;
		} while (row != min->head);
	}
}

/*
 *Cover rows and columns in accordance to Algo X for the given inputs
 *Inputs of sudoku are taken left to right, top to bottom. '0' input indicates empty cell
 *Will return false for invalid grids, i.e. those that do not satisfy all four sudoku conditions
 *
 *Note
 *If the conditions are broken with regards to input_A and input_B. 
 *i.e. they both satisfy one or more same conditions, adding input_A to the 
 *solution set will hide rows (in accordance to Algo X) that input_B will 
 *attempt to hide later. This is used to detect invalid grids.
 */
bool SolutionSet::m_cover_inputs(const std::vector<int>& input) {
	int val, s_row, s_col, ec_row, ec_col;
	s_row = 0;
	s_col = 0;
	for (auto it = input.begin(); it != input.end(); ++it) {
		if ((val = *it)) { //for each non-zero input
			ec_row = val + s_row*MULT_R_ROW + s_col*MULT_R_COL;
			ec_col = COND0 + s_row*MULT_9 + s_col; //A column associated with COND0
			Node *row = m->get_Node(ec_row, ec_col);
			if (row == nullptr) return false; //see Note above.
			insertNewRow(row);
		}
		//update sudoku position
		s_col = (s_col+1)%9; 
		s_row += !s_col;
	}
	return true;
}

/*
 *Restore the grid to the original state before inputs were covered.
 */
void SolutionSet::m_restore_inputs() {
	while (!(solRows.empty())) {
		restorePrevRow();
	}
}

/*
 *Print the solution after solving to stdout in a format resembling the sudoku grid
 */
void SolutionSet::printSolution() {
	int Sudoku[9][9];
	while (!(solRows.empty())) {
		int row,col,symbol;
		Node *currRow = solRows.top();
		solRows.pop();

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
