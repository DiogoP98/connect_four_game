#include <stdio.h>

#include "node.h"

int main(){
	Node *a = new Node();
	
	printf("final? %d\n",a->final_board());
	a->print_board();
	
	a->play(0,1);
	a->play(0,2);
	a->play(0,2);
	
	printf("final? %d\n",a->final_board());
	a->print_board();
	
	a->play(0,2);
	a->play(0,2);
	
	printf("final? %d\n",a->final_board());
	a->print_board();
		
	return 0;
}

/*
   printf("------------------\n\n");
	std::vector<Node> l = a->child_list(1);
	for(int i=0;i<(int)l.size();i++)
		l[i].print_board();
	l = l[0].child_list(2);
	//l = l[3].child_list(1);
	printf("------------------\n\n");
	for(int i=0;i<(int)l.size();i++)
		l[i].print_board();
*/

/*DRAW
 a = new Node();
	a->conf[0]=std::make_pair(121212,6);
	a->conf[1]=std::make_pair(212122,6);
	a->conf[2]=std::make_pair(111221,6);
	a->conf[3]=std::make_pair(121212,6);
	a->conf[4]=std::make_pair(221212,6);
	a->conf[5]=std::make_pair(212121,6);
	a->conf[6]=std::make_pair(112121,6);
	printf("final? %d\n",a->final_board());
	a->print_board();
*/
