#pragma once
#include<iostream>
class Node {
public:
	char ch;
	Node* child[26];
	const int size = 26;
	bool isWord;
	Node() {
		isWord = false;
		ch = ' ';
		for (int i = 0; i < size; i++) {
			child[i] = NULL;
		}
	}

	~Node() {
		for (int i = 0; i < 26; i++) {
			delete[] child[i];
		}
	}
};

