#include <stdio.h>

#include "node.h"
#include "minimax.h"

void game_player(Node *a);
void game_bot   (Node *a);
void end(int x);

int main(){
	printf("***************\n");
	printf("*Conect 4 Game*\n");
	printf("***************\n\n");
	
	Node *a = new Node(); //create empty node
	game_player(a);
	
	return 0;
}

void game_player(Node *a){
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	a->print_board();
	
	int c;
	printf("Choose a column: ");
	scanf("%d",&c);
	a->play(c,1);
	game_bot(a);
	return;
}

void game_bot(Node *a){
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	a->print_board();
	
	printf("Bot thinking..\n");
	int c = minimax(a);
	printf("Bot chooses column %d\n",c);
	a->play(c,2);
	game_player(a);
	return;
}

void end(int x){
	switch(x){
		case 0:
			printf("DRAW!\n");
			return;
		case 1:
			printf("Human Player Wins!\n");
			return;
		case 2:
			printf("Bot Player Wins!\n");
			return;
	}
}
/*for Debug/tests*/


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
