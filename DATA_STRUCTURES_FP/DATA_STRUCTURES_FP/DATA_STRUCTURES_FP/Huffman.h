#pragma once

#include<iostream>
#include"charNode.h"
#include <string>
#include <fstream>

using namespace std;

class Huffman {
	charNode* head, * root;
	string code;
	bool found, print;
public:
	Huffman() {
		this->head = NULL;
		this->root = NULL;
		code = "";
		found = false;
		print = false;
	}

	charNode* deleteFront() {
		if (head == NULL)
			return NULL;

		charNode* temp = head;
		head = head->next;

		return temp;
	}

	charNode* merge() {
		charNode* temp = new charNode;

		temp->left = deleteFront();
		temp->left->parent = temp;
		temp->right = deleteFront();
		temp->right->parent = temp;

		temp->frequency = temp->left->frequency + temp->right->frequency;

		return temp;
	}

	void insertAt(charNode* node) {
		charNode* temp = head;
		charNode* tailTemp = NULL;

		if (head) {

			while (temp) {
				if (temp->frequency >= node->frequency)
					break;
				tailTemp = temp;
				temp = temp->next;
			}
		}
		if (!head) {
			root = node;
			return;
		}

		if (!tailTemp) {
			node->next = temp;
			head = node;
			return;
		}
		else {
			node->next = temp;
			tailTemp->next = node;
		}
	}

	charNode* sort() {
		charNode* temp1 = head;
		charNode* temp = head->next;

		while (temp1) {
			while (temp) {
				if (temp1->frequency > temp->frequency) {
					swap(temp1->ch, temp->ch);
					swap(temp1->frequency, temp->frequency);
				}
				temp = temp->next;
			}
			temp1 = temp1->next;
			if (temp1 != NULL)
				temp = temp1->next;
			else
				temp = NULL;
		}

		return head;
	}

	charNode* insert(string str) {
		charNode* end = NULL;
		int arr[27] = { 0 };
		int count = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != ' ') {
				arr[str[i] - 'a'] += 1;
			}
			else
				arr[26] += 1;
			count++;
		}
		for (int i = 0; i < 27; i++) {
			if (arr[i] != 0) {
				if (end == NULL && i != 26) {
					end = new charNode;
					end->ch = i + 'a';
					end->frequency = arr[i];
					head = end;
				}
				else if (end == NULL && i == 26 && arr[i] != 0) {
					end = new charNode;
					end->ch = ' ';
					end->frequency = arr[i];
					head = end;
				}
				else if (i == 26 && arr[i] != 0) {
					end->next = new charNode;
					end = end->next;
					end->ch = ' ';
					end->frequency = arr[i];
				}
				else {
					end->next = new charNode;
					end = end->next;
					end->ch = i + 'a';
					end->frequency = arr[i];
				}
			}
		}

		return head;
	}

	void treeControl(string str) {
		insert(str);
		sort();
		while (head) {
			insertAt(merge());
		}

		preOrder(root);

		string reversed = "";
		for (int i = 0; i < str.length(); i++) {
			bin_code(root, str[i]);
			string temp = code;

			for (int i = code.length() - 1; i >= 0; i--)
			{
				temp[code.length() - i - 1] = code[i];
			}
			reversed += temp;

			found = print = false;
			code = "";
		}
		code = reversed;

		ofstream file;
		file.open("Huffman.txt");
		file << code;
	}

	void preOrder(charNode* head) {
		if (head == NULL)
			return;

		preOrder(head->left);
		preOrder(head->right);
	}

	void bin_code(charNode* head, char& ch) {
		if (head == NULL)
			return;
		if (head->ch == ch) {
			found = true;
		}
		if (!found) {
			bin_code(head->left, ch);
			bin_code(head->right, ch);
		}
		else if (!print) {
			while (head != root) {
				if (head->parent->left == head) {
					code += '0';
				}
				else {
					code += '1';
				}
				head = head->parent;
			}
			print = true;
		}
	}
	string decode() {
		charNode* temp = root;
		string st = "";
		for (int i = 0; i < code.length(); i++)
		{
			if (code[i] == '1') {
				temp = temp->right;
				if (temp->ch != '@')
				{
					st += temp->ch;
					temp = root;
				}
			}
			else
			{
				temp = temp->left;
				if (temp->ch != '@')
				{
					st += temp->ch;
					temp = root;
				}
			}
		}

		return st;
	}
};

