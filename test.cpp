#include <stdio.h>

#include "node.h"

using namespace std;

int main(){
	Node *a = new Node();
	a->play(0,1);
	a->play(0,2);
	a->play(0,2);
	a->print_board();
	printf("------------------\n\n");
	vector<Node> l = a->child_list(1);
	for(int i=0;i<(int)l.size();i++)
		l[i].print_board();
	l = l[0].child_list(2);
	printf("------------------\n\n");
	for(int i=0;i<(int)l.size();i++)
		l[i].print_board();
	return 0;
}
