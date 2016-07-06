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

void Node_Constraint::insertNewNode(Node *newNode) {
	Node *curr = head;
	head = newNode;
	if (curr != nullptr) {
		newNode->up = curr;
		newNode->down = curr->down;
		curr->down = newNode;
		newNode->down->up = newNode;
	} else { //first node
		newNode->up = newNode;
		newNode->down = newNode;
	}
	size++;
}

void Node::insertNewRowNode(Node *newNode) {
	Node *curr = right;
	newNode->left = this;
	newNode->right = curr;
	curr->left = newNode;
	right = newNode;
	/*if (curr == nullptr) {
		newNode->right = this;
		left = newNode;
	} else {
		curr-left = newNode;
	}*/
}