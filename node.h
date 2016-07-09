#ifndef NODE_H
#define NODE_H

struct Node {
	Node(): Node(0, 0) {}
	Node(int i, int j) : left(this), right(this), up(this), down(this), rowVal(i), colVal(j) {}
	//Data
	Node *left;
	Node *right;
	Node *up;
	Node *down;
	int rowVal;
	int colVal;

	//Operations:

	void linkWithRow(Node *newNode);
	//"Restore" this node back, via Knuth's Dancing Links idea.
	void restoreLeftRight();
	void restoreUpDown();
	void removeLeftRight();
	void removeUpDown();
	
};

struct Node_Constraint {
	Node_Constraint(): Node_Constraint(0) {}
	Node_Constraint(int i): left(this), right(this), head(nullptr), colVal(i), size(0) {}
	Node_Constraint *left;
	Node_Constraint *right;
	Node *head;
	int colVal;
	int size;

	//Operations

	void restoreLeftRight();
	void removeLeftRight();
	void insertNewNode(Node *newNode);

};

#endif


