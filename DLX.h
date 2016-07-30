#ifndef DLX_H
#define DLX_H

#include <stack>

#include "grid.h"

const int MAXSIZE = 9;

class SolutionSet {
	
private:
	std::stack<Node *> solRows;
	Matrix_ExactCover *m;
	bool solved;
	int solutionNum;

public:
	//Operations
	SolutionSet(): m(new Matrix_ExactCover()), solved(false), solutionNum(0)  {}
	void insertNewRow(Node *n);
	Node *restorePrevRow();
	void solve();
	bool m_cover_inputs(const std::vector<int>& input);
	void m_restore_inputs();
	void printSolution();

	//Getters
	std::stack<Node *> getSolRows();
	Matrix_ExactCover *getECM();
	bool getSolved();
	int getSolnNum();

	void setStack(std::stack<Node *> s);
	void pushStack(Node *n);
	Node *popStack();
	void setSolved(bool b);
	void setSolnNum(int n);
	void setECM(Matrix_ExactCover *m);

};


#endif