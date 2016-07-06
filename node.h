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
	void removeLeftRight();
	void removeUpDown();
	void insertNewRowNode(Node *newNode);
};

struct Node_Constraint {
	Node_Constraint *left;
	Node_Constraint *right;
	Node *head;
	int colVal;
	int size;

	void restoreLeftRight();
	void removeLeftRight();
	void insertNewNode(Node *newNode);

};

#endif


