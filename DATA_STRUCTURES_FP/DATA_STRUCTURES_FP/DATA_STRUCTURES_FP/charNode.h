#pragma once

#include<iostream>

class charNode {
public:
	int frequency;
	char ch;
	charNode* next;
	charNode* left, * right;
	charNode* parent;
	bool lWeight, rWeight;

	charNode() {
		this->next = this->left = this->right = NULL;
		this->frequency = 0;
		this->ch = '@';
		this->lWeight = false;
		this->rWeight = true;
		this->parent = NULL;
	}

	charNode(const charNode& node) {
		this->ch = node.ch;
		this->frequency = node.frequency;
		this->left = new charNode;
		this->left = node.left;
		this->right = new charNode;
		this->right = node.right;
		this->lWeight = node.lWeight;
		this->rWeight = node.rWeight;
		this->next = new charNode;
		this->next = node.next;
	}
};

