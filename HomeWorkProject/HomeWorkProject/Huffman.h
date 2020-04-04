#pragma once
#include <queue>
#include <vector>
#include<iostream>
using namespace std;
struct Tree {
public:
	Tree* left;
	Tree* right;
	string val;
	string xChar;
	int count;
	Tree(const string& val = "", int count = 0, Tree* left = 0, Tree* right = 0) {
		this->val = val; // множество символом узла
		this->xChar = ""; // строковое представление битового кода узла
		this->count = count; // сколько раз втретилось
		this->left = left; // левый ребенок
		this->right = right; // правый ребенок
	}
	bool operator()(Tree a, Tree b) {
		return a.count > b.count;
	}

};

char* HuffCoding( char* bytes, int n) {
	unsigned int arrCount[256];
	priority_queue<Tree, vector<Tree>, Tree> graph;
	for (int i = 0; i < 256; i++) arrCount[i] = 0;
	for (int i = 0; i < n; i++) {
		arrCount[bytes[i]]++;
	}
	for (int i = 0; i < 256; i++) {
		if (arrCount != 0)
			graph.emplace(string(1,char(i)), arrCount[i]);
	}
	for (int i = 0; i < graph.size(); i++) {
		cout << graph << " ";
	}
	return bytes;

}
unsigned char* HuffDecoding(unsigned char* bytes, int n) {
	return bytes;
}