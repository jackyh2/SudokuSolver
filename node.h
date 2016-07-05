#ifndef NODE_H
#define NODE_H

struct Matrix_ExactCover {
	Node *head;
}

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

struct Node_Contraint {
	Node *left;
	Node *right;
	Node *up;
	Node *down;
	int colVal;
	int size;

	void restoreLeftRight();
};

#endif


