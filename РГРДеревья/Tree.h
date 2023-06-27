#pragma once
#include <iostream>

class Node {
private:
	Node* parent;
	Node* sons[4];
	int keys[2];
	int length;
	int max_son;

	Node() {};

	Node(int _data) {
		keys[0] = _data;
		keys[1] = _data;
		length = 0;
		max_son = _data;
	};

	
	friend class Tree;
	friend Tree* disengage(Tree* S, int a);
	friend Tree concatenate(Tree t1, Tree t2);
	friend void ins_sort(Node* p);

};

class Tree {

private:
	Tree() {};
	Tree(Node* r) { root = r; };
	Tree(Node* r1, Node* r2);
	Node* root;
	Node* search(int a, Node* r);
	void add_son(Node* t);
	void update_keys(Node* t);
	void print_node(Node* t);

public:
	
	Tree(int data) { root = new Node(data); };
	
	void insert(int a);
	void print_tree();
	int h();

	friend Tree* disengage(Tree* S, int a);
	friend Tree concatenate(Tree t1, Tree t2);
};

void ins_sort(Node* p);

Tree concatenate(Tree t1, Tree t2);

Tree* disengage(Tree* S, int a);