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