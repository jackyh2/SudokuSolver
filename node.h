#ifndef NODE_H
#define NODE_H



struct Node {
	//Data
	Node *left;
	Node *right;
	Node *up;
	Node *down;
	int rowVal;
	int colVal;

	//Operations:

	//"Restore" this node back, via Knuth's Dancing Links idea.
	void restoreLeftRight();
	void restoreUpDown();
};

struct Node_Constraint {
	Node_Constraint *left;
	Node_Constraint *right;
	Node *up;
	Node *down;
	int colVal;
	int size;

	void restoreLeftRight();
};

struct Matrix_ExactCover {
	Node_Constraint *head;
};

#endif


