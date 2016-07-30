#ifndef NODE_H
#define NODE_H

class Node {
	friend class Matrix_ExactCover;
private:
	//Data
	Node *left;
	Node *right;
	Node *up;
	Node *down;
	int rowVal;
	int colVal;

	Node(): Node(0, 0) {}
	Node(int i, int j) : left(this), right(this), up(this), down(this), rowVal(i), colVal(j) {}

public:
	~Node() {
		left = nullptr;
		right = nullptr;
		up = nullptr;
		down = nullptr;
	}
	//Operations:
	
	void linkWithRow(Node *newNode);
	//"Restore" this node back, via Knuth's Dancing Links idea.
	void restoreLeftRight();
	void restoreUpDown();
	void removeLeftRight();
	void removeUpDown();

	//Getters
	Node *getLeft();
	Node *getRight();
	Node *getUp();
	Node *getDown();
	int getRow();
	int getCol();

	//Setters
	void setLeft(Node *n);
	void setRight(Node *n);
	void setUp(Node *n);
	void setDown(Node *n);
	
};

class Node_Constraint {
	friend class Matrix_ExactCover;
private:
	Node_Constraint *left;
	Node_Constraint *right;
	Node *head;
	int colVal;
	int size;

	Node_Constraint(): Node_Constraint(0) {}
	Node_Constraint(int i): left(this), right(this), head(nullptr), colVal(i), size(0) {}

public:
	~Node_Constraint() {
		Node *curr = head;
		if (curr == nullptr) return;
		curr->getUp()->setDown(nullptr);
		Node *next = curr->getDown();
		while (curr != nullptr) {
			delete curr;
			curr = next;
			if (next != nullptr) next = next->getDown();
		}

	}
	//Operations
	
	void restoreLeftRight();
	void removeLeftRight();
	void insertNewNode(Node *newNode);

	//Getters
	Node_Constraint *getLeft();
	Node_Constraint *getRight();
	Node *getHead();
	int getCol();
	int getSize();

	//Setters
	void setLeft(Node_Constraint *n);
	void setRight(Node_Constraint *n);
	void setHead(Node *n);
	//Size += i;
	void updateSize(int i);

};

#endif


