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


#endif


