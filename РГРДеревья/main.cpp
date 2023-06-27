#include "Tree.h"

void main() {
	Tree t(1);
	t.insert(2);
	t.insert(4);
	t.insert(5);
	t.insert(0);
	//t.insert(6);
	//t.insert(7);
	//t.insert(8);
	//t.insert(9);

	Tree s(-1);
	//s.insert(-2);
	//s.insert(-3);
	//s.insert(-4);
	//s.insert(-5);
	//s.insert(-6);
	//s.insert(-7);
	//s.insert(-8);
	
	t.print_tree();
	s.print_tree();

	auto ts = concatenate(t, s);
	ts.print_tree();

	Tree* ts_ = &ts;
	auto arr = disengage(ts_, -1);

	arr[0].print_tree();
	arr[1].print_tree();



}