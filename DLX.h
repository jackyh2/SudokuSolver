#ifndef DLX_H
#define DLX_H

#include <stack>

#include "grid.h"


struct SolutionSet {
	std::stack<Node *> rows;
	Matrix_ExactCover *m;

	void insertNewRow(Node *n);
	void deletePrevRow();
	void solve();
	void m_cover_inputs(const std::vector<int>& input);
	void m_restore_inputs();
	void printSolution();
};


#endif