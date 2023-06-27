#include "Tree.h"

void Tree::insert(int a) {
	Node* v = new Node(a);
	if (root->sons[0] == nullptr) {
		Node* r = new Node();
		if (root->keys[0] > v->keys[0]) {
			r->sons[0] = v;
			r->sons[1] = root;
			root->parent = r;
			v->parent = r;
			r->length = 2;
			root = r;
		}
		else {
			r->sons[0] = root;
			r->sons[1] = v;
			root->parent = r;
			v->parent = r;
			r->length = 2;
			root = r;
		}

	}
	else {
		Node* f = search(a, root);		
		v->parent = f;
		f->sons[f->length] = v;
		f->length++;
		ins_sort(f);
		if (f->length == 4) {
			add_son(f);
		}
	}
	update_keys(v);
}

Node* Tree::search(int a, Node* r) {
	if (r->sons[0]->sons[0] == nullptr) {
		return r;
	 }

	else {
		if (a < r->keys[0]) {
			return search(a, r->sons[0]);
		}

		else if ((r->length == 2) || (a <= r->keys[1])) {
			return search(a, r->sons[1]);
		}
		else {
			return search(a, r->sons[2]);
		}
	}
}

void Tree::add_son(Node* v) {
	Node* v_ = new Node();
	v_->sons[0] = v->sons[2];
	v_->sons[1] = v->sons[3];
	v->sons[2]->parent = v_;
	v->sons[3]->parent = v_;
	v->sons[2] = nullptr;
	v->sons[3] = nullptr;
	v->max_son = v->sons[1]->max_son;
	v->length = 2;
	v_->length = 2;
	v_->keys[0] = v_->sons[0]->max_son;
	v_->keys[1] = v_->sons[1]->max_son;
	v_->max_son = v_->sons[1]->max_son;
	
	
	if (v == root) {
		Node* r = new Node();
		r->sons[0] = v;
		r->sons[1] = v_;
		v->parent = r;
		v_->parent = r;
		r->length = 2;
		root = r;
	}
	else {
 		auto f = v->parent;
		
		if (f->sons[1] == v) {
			if (f->sons[2] == nullptr) {
				f->sons[2] = v_;
			}
			else {
				f->sons[3] = f->sons[2];
				f->sons[2] = v_;
			}
		}
		else if (f->sons[2] == v) {
			f->sons[3] = v_;
		}
		
		else {
			if (f->sons[2] == nullptr) {
				f->sons[2] = f->sons[1];
				f->sons[1] = v_;
			}
			else {
				f->sons[3] = f->sons[2];
				f->sons[2] = f->sons[1];
				f->sons[1] = v_;
			}
		}

		
		v_->parent = f;
		f->length = f->length + 1;
		if (f->length == 4) {
			add_son(f);
		}
	}
}

void Tree::update_keys(Node* t) {

	if (t->sons[0] != nullptr) {
		t->keys[0] = t->sons[0]->max_son;
		t->keys[1] = t->sons[1]->max_son;
		if (t->length == 2) {
			t->max_son = t->sons[1]->max_son;
		}
		else {
			t->max_son = t->sons[2]->max_son;
		}
	}

	if (t->parent != nullptr) {
		update_keys(t->parent);
	}
}



void ins_sort(Node* f) {
	for (int i = 0; i < f->length - 1; i++) {
		for (int j = 0; j < f->length - 1; j++) {
			if (f->sons[j]->keys[0] > f->sons[j + 1]->keys[1]) {
				auto temp = f->sons[j];
				f->sons[j] = f->sons[j + 1];
				f->sons[j + 1] = temp;
			}
		}
	}
}



void Tree::print_tree() {
	auto a = root;
	std::cout << a->keys[0] << ':' << a->keys[1] << '\n';
	for (int i = 0; i < 4; i++) {
		if (a->sons[i] != nullptr) {
			print_node(a->sons[i]);
		}
	}
	std::cout << '\n';
}

void Tree::print_node(Node* t) {
	if (t->sons[0] != nullptr) {
		std::cout << t->keys[0] << ':' << t->keys[1] << ' ' << t->parent->keys[0] << ':' << t->parent->keys[1] << '\n';
	}
	else {
		std::cout << t->keys[0] << ' ' << t->parent->keys[0] << ':' << t->parent->keys[1] << '\n';
	}
	for (int i = 0; i < 4; i++) {
		if (t->sons[i] != nullptr) {
			print_node(t->sons[i]);
		}
	}
}


int Tree::h() {
	auto f = root;
	int count = 0;
	while (f->sons[0] != nullptr) {
		count += 1;
		f = f->sons[0];
	}
	return count;
}

Tree::Tree(Node* r1, Node* r2) {
	Node* r = new Node();
	r->sons[0] = r1;
	r->sons[1] = r2;
	r1->parent = r;
	r2->parent = r;
	r->length = 2;
	r->keys[0] = r1->max_son;
	r->keys[1] = r2->max_son;	
	r->max_son = r2->max_son;
	root = r;
}

Tree concatenate(Tree t1, Tree t2) {
	if (t1.root->keys[0] > t2.root->keys[0]) {
		auto tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	
	int h1 = t1.h();
	int h2 = t2.h();
	Node* root1 = t1.root;
	Node* root2 = t2.root;
	if (t1.h() == t2.h()) {
		return Tree(root1, root2);
	}

	else if (h1 > h2) {
		int count = 0;
		Node* f = root1;
		while (count != h1 - h2 - 1) {
			count += 1;
			f = f->sons[f->length - 1];
		}



		f->sons[f->length] = root2;
		root2->parent = f;
		f->length++;
		f->max_son = root2->max_son;
		if (f->length == 4) {
			t1.add_son(f);
			t1.update_keys(root2);
		}

		return t1;

	}

	else {
		int count = 0;
		Node* f = root2;
		while (count != h2 - h1 - 1) {
			count += 1;
			f = f->sons[0];
		}


		f->sons[3] = f->sons[2];
		f->sons[2] = f->sons[1];
		f->sons[1] = f->sons[0];
		f->sons[0] = root1;
		root1->parent = f;
		f->keys[0] = f->sons[0]->max_son;
		f->keys[1] = f->sons[1]->max_son;
		f->length++;
		if (f->length == 4) {
			t2.add_son(f);
			t2.update_keys(root1);
		}

		return t2;
	}
}

Tree* disengage(Tree* S, int a) {
	Tree* mas = new Tree[2];
	const int height = S->h();
	
	Tree* left_les = new Tree[3 * height];
	Tree* right_les = new Tree[3 * height];
	int len_l = 0;
	int len_r = 0;

	Node* f = S->root;
	while (f->keys[0] != f->keys[1]) {
		if (a <= f->keys[0]) {
			if (f->sons[2] != nullptr) {
				right_les[len_r] = Tree(f->sons[2]);
				len_r++;
			}
			right_les[len_r] = Tree(f->sons[1]);
			len_r++;
			f = f->sons[0];
			

		}

		else if ((a <= f->keys[1]) || (f->sons[2] == nullptr)) {
			left_les[len_l] = Tree(f->sons[0]);
			len_l++;
			if (f->sons[2] != nullptr) {
				right_les[len_r] = Tree(f->sons[2]);
				len_r++;
			}
			f = f->sons[1];
		}
		else {
			left_les[len_l] = Tree(f->sons[0]);
			len_l++;
			left_les[len_l] = Tree(f->sons[1]);
			len_l++;
			f = f->sons[2];
		}

	}
	left_les[len_l] = Tree(f);
	len_l++;
	if (len_r == 0) {
		std::cout << "ERROR: You can\'t disengage by the largest number.";
		exit(0);
	}
	/*for (int i = 0; i < len_r - 1; i++) {
		for (int j = 0; j < len_r - 1; j++) {
			if (right_les[j].root->keys[0] > right_les[j + 1].root->keys[0]) {
				auto tmp = right_les[j];
				right_les[j] = right_les[j + 1];
				right_les[j + 1] = tmp;
			}
		}
	}

	for (int i = 0; i < len_l - 1; i++) {
		for (int j = 0; j < len_l - 1; j++) {
			if (left_les[j].root->keys[0] > left_les[j + 1].root->keys[0]) {
				auto tmp = left_les[j];
				left_les[j] = left_les[j + 1];
				left_les[j + 1] = tmp;
			}
		}
	}
	*/


	while (len_l != 1) {
		left_les[len_l - 2] = concatenate(left_les[len_l - 2], left_les[len_l - 1]);
		left_les[len_l - 1] = nullptr;
		len_l--;
	}
	
	while (len_r != 1) {
		right_les[len_r - 2] = concatenate(right_les[len_r - 2], right_les[len_r - 1]);
		right_les[len_r - 1] = nullptr;
		len_r--;
	}

	mas[0] = left_les[0];
	mas[1] = right_les[0];


	return mas;
}
