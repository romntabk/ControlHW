#pragma once
#include <queue>
#include <vector>
#include<iostream>
using namespace std;


vector<pair<string, string>> vecPairs;
struct Tree {

	Tree* left;
	Tree* right;
	string val;
	string xChar;
	int count;

	Tree(const string& val = "", int count = 0, Tree* left = 0, Tree* right = 0) {
		this->val = val;  
		this->xChar = ""; 
		this->count = count;
		this->left = left; 
		this->right = right;
	}
	bool operator()(Tree a, Tree b) {
		return a.count > b.count;
	}
	Tree* join(Tree x) {
		return new Tree(x.val + val, x.count + count, new Tree(x), this);
	}
	void traversal_code(string code) {
		this->xChar = code;
		if (left == nullptr && right == nullptr) {
			vecPairs.push_back(pair<string, string>(val, xChar));
		}
		if (left != nullptr || right != nullptr) {
			left->traversal_code(code + "1");
			right->traversal_code(code + "0");
		}
		
	}
    Tree* build(priority_queue<Tree, vector<Tree>, Tree> graph) {
		while (graph.size() > 1) {
			Tree* n = new Tree(graph.top());
			graph.pop();
			graph.push(*n->join(*new Tree(graph.top())));
			graph.pop();
		}
		return new Tree(graph.top());
	}
};



vector<pair<string, string>> HuffCoding( char* bytes, int n) {
	unsigned int arrCount[256];
	priority_queue<Tree, vector<Tree>, Tree> graph;
	for (int i = 0; i < 256; i++) arrCount[i] = 0;
	for (int i = 0; i < n; i++) {
		arrCount[128+(int)bytes[i]]++;
		cout << (int)bytes[i]+128 << " ";
	}
	for (int i = 0; i < 256; i++) {
		if (arrCount[i]	 != 0) {
			Tree drevo = Tree(string(1, (char)i), arrCount[i]);
			graph.push(drevo);
		}
	}
    vecPairs = vector<pair<string, string>>();
	Tree* tree = Tree().build(graph);
	tree->traversal_code("");
	for (int i = 0; i < vecPairs.size(); i++) {
		cout << vecPairs[i].first << " and " << vecPairs[i].second<< endl;
	}
	return vecPairs;
}

unsigned char* HuffDecoding(unsigned char* bytes, int n, vector<pair<string,string>> vec) {
	
	return bytes;
}