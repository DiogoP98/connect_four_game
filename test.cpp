#include <stdio.h>

#include "node.h"

using namespace std;

int main(){
	Node *a = new Node();
	a->play(0,1);
	a->play(0,2);
	a->play(0,2);
	a->print_board();
	return 0;
}
