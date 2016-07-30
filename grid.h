#ifndef GRID_H
#define GRID_H

#include <vector>

#include "node.h"

//Standard 9x9 sudoku
const int NUMCOLS = 324; //columns indexed [0,323]
const int NUMROWS = 729; //rows indexed [1,729]
const int NUMBOXES = 81;
const int MULT_R_ROW = 81; //multipler constant
const int MULT_R_COL = 9; //multiplier constant

//COND0: only one of value in each of 81 cells
//COND1: only one of 1-9 in each of 9 rows
//COND2: only one of 1-9 in each of 9 columns
//COND3: only one of 1-9 in each of 9 blocks
const int COND0 = 0; //the starting column/offset for each of the four conditions
const int COND1 = 80;
const int COND2 = 161;
const int COND3 = 242;
const int NUM_CONDS = 4;
const int MULT_9 = 9; //multipler constant


//Representation of the Exact Cover matrix.
class Matrix_ExactCover {
	friend class SolutionSet;
private:
	Node_Constraint *head;
	std::vector<Node_Constraint *> header_constraint; //length NUMCOLS
	Matrix_ExactCover();//contructor default
	void m_create_cells();
public:
	//Operations
	~Matrix_ExactCover() {
		for (int i = 0; i < header_constraint.size(); ++i) {
			delete header_constraint[i];
		}
	}
	void printRowByRow();

	//Getters
	Node_Constraint *getHead();
	Node_Constraint *get_Column_Constraint(int col);
	Node *get_Node(int row, int col);

	//Setters
	void set_Column_Constraint(int col, Node_Constraint *n);
	void setHead(Node_Constraint *n);


};


Matrix_ExactCover *m_create_grid();


#endif 