#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "node.h"
#include "minimax.h"
#include "alphabeta.h"
#include "myboost.h"

double totaltime;

void game();
void gamex();
void gameo();
void game_player_x ();
void game_player_o ();
void game_bot_mm_x ();
void game_bot_mm_o ();
void game_bot_ab_x ();
void game_bot_ab_o ();
void end(int x);
int is0(char *l);
int isn(char *l);
int isn2(char *l);

Node *a;
int botvbot;
int mysymbol;
int method;
int difficulty;
int difficulty2;
bool flip;

int main(){
	//printf("\033c");
	printf("***************\n");
	printf("*Conect 4 Game*\n");
	printf("***************\n");
	
	printf("\nLoading..\n");
	MyBoost::load_boost();
	
	//std::map<int,int>::iterator it;
	//for(it=Global m4;i<)
	
	a = new Node();
	
	/*
	for(int i=0;i<6;i++)
		for(int j=0;j<7;j++)
			scanf("%d",&a->conf[i][j]);
	*/
	/*
	a->play(0,1);
	a->play(0,1);
	a->play(0,2);
	a->play(0,1);
	a->play(0,2);
	a->play(0,1);
	
	a->play(1,1);
	a->play(1,2);
	a->play(1,2);
	a->play(1,1);
	a->play(1,1);
	a->play(1,2);
	
	a->play(2,1);
	a->play(2,2);
	a->play(2,1);
	a->play(2,2);
	a->play(2,1);
	a->play(2,1);
	
	a->play(3,2);
	a->play(3,1);
	a->play(3,2);
	a->play(3,1);
	a->play(3,2);
	a->play(3,2);
	
	a->play(4,2);
	
	a->play(5,2);
	a->play(5,2);
	a->play(5,2);
	a->play(5,1);
	a->play(5,1);
	a->play(5,2);
	
	a->play(6,1);
	a->play(6,1);
	a->play(6,2);
	
	a->print_board();
	printf("%d\n",a->eval_board());	
*/	


	bool gg=true;
	
	while(gg){
		totaltime=0;
		a = new Node(); //create empty node
		
		char *l;
		
		l= readline("\nDo you want bot against bot?\n1-Yes\n2-No\n\nOption: ");
		while(!(botvbot=is0(l))){
			l= readline("Invalid! Option: ");
			add_history(l);
		}
		
		l= readline ("\nWhich method do you want to use?\n1-MiniMax\n2-AlphaBeta\n\nOption: ");
		while(!(method = is0(l))){
			l= readline("Invalid! Option: ");
			add_history(l);
		}

		l = readline("\nBot difficult:\n1(Easy)\n2\n3\n4(Medium)\n5\n6\n7\n8(Hard)\n\nOption: ");
		while(!(difficulty = isn(l))){
			l= readline("Invalid! Option: ");
			add_history(l);
		}
		
		if(botvbot==1){
			l = readline("\nSecond bot difficult (X):\n1(Easy)\n2\n3\n4(Medium)\n5\n6\n7\n8(Hard)\n\nOption: ");
			while(!(difficulty2 = isn(l))){
				l= readline("Invalid! Option: ");
				add_history(l);
			}
		}
		
		if(botvbot==2){
			
			l= readline("\nWhich symbol do you want to use?\n1-X\n2-O\n\nOption: ");
			while(!(mysymbol=is0(l))){
				l= readline("Invalid! Option: ");
				add_history(l);
			}
			
			int stf;
			l= readline("\nDo you want to start first?\n1-Yes\n2-No\n\nOption: ");
			while(!(stf=is0(l))){
				l= readline("Invalid! Option: ");
				add_history(l);
			}
			
			if(stf==1)
				flip=true;
			else
				flip=false;
		}
		else
			flip=true;
			
		game();
		printf("\nTotal elapsed time:%lf\n",totaltime);
		
		delete a;
		
		int k;
		l= readline("\n\nAnother game?\n1-Yes\n2-No\n\nOption: ");
		while(!(k=is0(l))){
			l= readline("Invalid! Option: ");
			add_history(l);
		}
		gg =false;
		if(k==1) gg = true;
	}
	
	return 0;
}

void game (){
	if(botvbot==1){
		if(flip)
			gamex();
		else
			gameo();
	}
	else{
		if(flip){
			if(mysymbol==1)
				game_player_x();
			else
				game_player_o();
		}
		else{
			if(mysymbol==1)
				gameo();
			else
				gamex();
		}
	}
}

void gamex(){
	if(method==1)
		game_bot_mm_x();
	else
		game_bot_ab_x();
}

void gameo(){
	if(method==1)
		game_bot_mm_o();
	else
		game_bot_ab_o();
}

void game_player_x(){
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	a->print_board();
	
	int c,x=1;char *l;
	l=readline("Player X - Choose a column: ");
	while(x){
		while((c=isn2(l))==-1){
			//printf("!%d!\n",c);
			l=readline("Invalid! Choose other: ");
			add_history(l);
		}
		x = a->play(c,2);
		if(x)l=readline("Invalid! Choose other: ");
	}
	printf("\n");
	flip = (!flip);
	game();
	return;
}

void game_player_o(){
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	a->print_board();
	
	int c,x=1;char *l;
	l=readline("Player O - Choose a column: ");
	while(x){
		while((c=isn2(l))==-1){
			l=readline("Invalid! Choose other: ");
			add_history(l);
		}
		x = a->play(c,1);
		if(x)l=readline("Invalid! Choose other: ");
	}
	printf("\n");
	flip = (!flip);
	game();
	return;
}

void game_bot_mm_x(){
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	a->print_board();
	
	
	printf("Bot X thinking ..\n");
	
	long start_s=clock();
	int c;
	if(!flip)c = Minimax::minimax(a,2,difficulty);
	else     c = Minimax::minimax(a,2,difficulty2);
	long stop_s=clock();
	printf("Total time thinking: %lf\n",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
	totaltime+=((stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
	
	printf("Bot chooses column %d\n\n",c);
	a->play(c,2);
	flip = (!flip);
	game();
	return;
}

void game_bot_mm_o(){
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	a->print_board();
	
	printf("Bot O thinking ..\n");
	
	long start_s=clock();
	int c;
	if(!flip)c = Minimax::minimax(a,1,difficulty);
	else     c = Minimax::minimax(a,1,difficulty2);
	long stop_s=clock();
	printf("Total time thinking: %lf\n",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
	totaltime+=((stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
	
	printf("Bot chooses column %d\n\n",c);
	a->play(c,1);
	flip = (!flip);
	game();
	return;
}

void game_bot_ab_x(){
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	a->print_board();
	
	printf("Bot X thinking ..\n");
	
	long start_s=clock();
	int c;
	if(!flip)c = Alphabeta::alphabeta(a,2,difficulty);
	else     c = Alphabeta::alphabeta(a,2,difficulty2);
	long stop_s=clock();
	printf("Total time thinking: %lf\n",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
	totaltime+=((stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
	
	printf("Bot chooses column %d\n\n",c);
	a->play(c,2);
	flip = (!flip);
	game();
	return;
}

void game_bot_ab_o(){
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	a->print_board();
	
	printf("Bot O thinking ..\n");
	
	long start_s=clock();
	int c;
	if(!flip)c = Alphabeta::alphabeta(a,1,difficulty);
	else     c = Alphabeta::alphabeta(a,1,difficulty2);
	long stop_s=clock();
	printf("Total time thinking: %lf\n",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
	totaltime+=((stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
	
	printf("Bot chooses column %d\n\n",c);
	a->play(c,1);
	flip = (!flip);
	game();
	return;
}

void end(int x){
	
	switch(x){
		case 0:
			printf("DRAW!\n");
			return;
		case 1:
			printf("O Player Wins!\n");
			return;
		case 2:
			printf("X Player Wins!\n");
			return;
	}
	
}

int is0(char *l){
	if(l==NULL)return 0;
	if(!isdigit(l[0]))return 0;
	int k = atoi(l);
	if(k<1 || k>2) return 0;
	return k;
}

int isn(char *l){
	if(l==NULL)return 0;
	if(!isdigit(l[0]))return 0;
	int k = atoi(l);
	if(k<0 || k>20) return 0;
	return k;
}

int isn2(char *l){
	if(l==NULL)return -1;
	if(!isdigit(l[0]))return -1;
	int k = atoi(l);
	if(k<0 || k>6) return -1;
	return k;
}
