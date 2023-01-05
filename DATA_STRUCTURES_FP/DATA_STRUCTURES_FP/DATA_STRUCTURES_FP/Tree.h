#pragma once
#include "Node.h"
#include <string>

using namespace std;

class Tree {
public:
	Tree() {
		Root = new Node;
	}
	Node* getRoot() {
		return Root;
	}
	void setRoot(Node* temp) {
		for (int i = 0; i < 26; i++) {
			Root->child[i]->ch = temp->child[i]->ch;
			Root->child[i]->isWord = temp->child[i]->isWord;
		}
	}

	Tree(const Tree& obj) {
		this->Root = obj.Root;
		for (int i = 0; i < 26; i++) {
			this->Root->child[i]->isWord = obj.Root->child[i]->isWord;
			this->Root->child[i]->ch = obj.Root->child[i]->ch;
		}
	}

	Node* Root;
};

