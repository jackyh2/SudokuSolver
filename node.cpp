#include "node.h"

void Node::restoreLeftRight() {
	left->right = this;
	right->left = this;
}

void Node::restoreUpDown() {
	up->down = this;
	down->up = this;
}

void Node_Constraint::restoreLeftRight() {
	left->right = this;
	right->left = this;
}

void Node::removeLeftRight() {
	left->right = right;
	right->left = left;
}

void Node::removeUpDown() {
	up->down = down;
	down->up = up;
}

void Node_Constraint::removeLeftRight() {
	left->right = right;
	right->left = left;
}

//Getters

Node* Node::getLeft() { return left; }
Node* Node::getRight() { return right; }
Node* Node::getUp() { return up; }
Node* Node::getDown() { return down; }
int Node::getRow() { return rowVal; }
int Node::getCol() { return colVal; }

Node_Constraint* Node_Constraint::getLeft() { return left; }
Node_Constraint* Node_Constraint::getRight() { return right; }
Node* Node_Constraint::getHead() { return head; }
int Node_Constraint::getCol() { return colVal; }
int Node_Constraint::getSize() { return size; }


//Setters

void Node::setLeft(Node *n) { left = n; }
void Node::setRight(Node *n) { right = n; }
void Node::setUp(Node *n) { up = n; }
void Node::setDown(Node *n) { down = n; }

	
void Node_Constraint::setLeft(Node_Constraint *n) { left = n; }
void Node_Constraint::setRight(Node_Constraint *n) { right = n; }
void Node_Constraint::setHead(Node *n) { head = n; }
void Node_Constraint::updateSize(int i) { size += i; }

//Insert new node to the column
void Node_Constraint::insertNewNode(Node *newNode) {
	Node *curr = head;
	head = newNode;
	if (curr != nullptr) {
		newNode->setUp(curr);
		newNode->setDown(curr->getDown());
		curr->setDown(newNode);
		newNode->getDown()->setUp(newNode);

		/*newNode->up = curr;
		newNode->down = curr->down;
		curr->down = newNode;
		newNode->down->up = newNode;*/
	} else { //first node
		newNode->setUp(newNode);
		newNode->setDown(newNode);

		/*newNode->up = newNode;
		newNode->down = newNode;*/
	}
	size++;
}

//Create links to join a new node to an existing row of node(s) horizontally
void Node::linkWithRow(Node *newNode) {
	Node *curr = right;
	newNode->setLeft(this);
	newNode->setRight(curr);
	curr->setLeft(newNode);
	right = newNode;

	/*Node *curr = right;
	newNode->left = this;
	newNode->right = curr;
	curr->left = newNode;
	right = newNode;*/
}
