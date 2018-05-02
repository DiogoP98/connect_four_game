#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

//dependecies
#include "node.h"
#include "minimax.h"
#include "alphabeta.h"
#include "myboost.h"

//functions
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

//variables
Node *a;
double totaltime;
int botvbot;
int mysymbol;
int method;
int difficulty;
int difficulty2;
bool flip;

int main(){
	printf("\033c");
	printf("***************\n");
	printf("*Conect 4 Game*\n");
	printf("***************\n");
	
	//generate all valid combinations of 4, 5, 6 and 7 and evaluate them
	printf("\nLoading..\n");
	MyBoost::load_boost();
	
	//for many games in a row
	bool gg=true;
	
	while(gg){
		totaltime=0; //time consumed by bot(s)
		a = new Node(); //create empty node
		
		char *l;
		
		l= readline("\nDo you want bot against bot?\n1-Yes\n2-No\n\nOption: ");
		add_history(l);
		while(!(botvbot=is0(l))){
			l= readline("Invalid! Option: ");
			add_history(l);
		}
		
		l= readline ("\nWhich method do you want to use?\n1-MiniMax\n2-AlphaBeta\n\nOption: ");
		add_history(l);
		while(!(method = is0(l))){
			l= readline("Invalid! Option: ");
			add_history(l);
		}
		
		//if bot vs bot
		if(botvbot==1){
			l = readline("\nFirst bot difficult(X):\n1(Easy)\n2\n3\n4(Medium)\n5\n6\n7\n8(Hard)\n\nOption: ");
			add_history(l);
			while(!(difficulty = isn(l))){
				l= readline("Invalid! Option: ");
				add_history(l);
			}
			
			l = readline("\nSecond bot difficult (O):\n1(Easy)\n2\n3\n4(Medium)\n5\n6\n7\n8(Hard)\n\nOption: ");
			add_history(l);
			while(!(difficulty2 = isn(l))){
				l= readline("Invalid! Option: ");
				add_history(l);
			}
			
			flip=false;
		}
		
		//if bot vs human
		if(botvbot==2){
			l = readline("\nBot difficult:\n1(Easy)\n2\n3\n4(Medium)\n5\n6\n7\n8(Hard)\n\nOption: ");
			add_history(l);
			while(!(difficulty = isn(l))){
				l= readline("Invalid! Option: ");
				add_history(l);
			}
			
			l= readline("\nWhich symbol do you want to use?\n1-X\n2-O\n\nOption: ");
			add_history(l);
			while(!(mysymbol=is0(l))){
				l= readline("Invalid! Option: ");
				add_history(l);
			}
			
			int stf;
			l= readline("\nDo you want to start first?\n1-Yes\n2-No\n\nOption: ");
			add_history(l);
			while(!(stf=is0(l))){
				l= readline("Invalid! Option: ");
				add_history(l);
			}
			
			if(stf==1)
				flip=true; //human first
			else
				flip=false; //bot first
		}			
		//start game	
		game();
		//game end, print time consumed by bot(s)
		printf("\nTotal elapsed time:%lf\n",totaltime);
		
		//delete board and prepare for new game if requested
		delete a;
		
		int k;
		l= readline("\n\nAnother game?\n1-Yes\n2-No\n\nOption: ");
		add_history(l);
		while(!(k=is0(l))){
			l= readline("Invalid! Option: ");
			add_history(l);
		}
		
		gg =false;
		if(k==1) gg = true;
	}
	
	return 0;
}

//to switch bots or players
void game (){
	if(botvbot==1){
		if(flip)
			gameo();
		else
			gamex();
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

//play bot x with algorithm selected before
void gamex(){
	if(method==1)
		game_bot_mm_x();
	else
		game_bot_ab_x();
}

//play bot o with algorithm selected before
void gameo(){
	if(method==1)
		game_bot_mm_o();
	else
		game_bot_ab_o();
}

//human player x
void game_player_x(){
	//check if there is a winner or a draw
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	
	//print board and ask for a play
	a->print_board();
	
	int c,x=1;char *l;
	l=readline("Player X - Choose a column: ");
	add_history(l);
	while(x){
		while((c=isn2(l))==-1){
			l=readline("Invalid! Choose other: ");
			add_history(l);
		}
		x = a->play(c,2);
		if(x){
			l=readline("Invalid! Choose other: ");
			add_history(l);
		}
	}
	printf("\n");
	flip = (!flip);
	game();
	return;
}

//human player o
void game_player_o(){
	//check if there is a winner or a draw
	int k = a->final_board();
	if(k>-1){
		a->print_board();
		end(k);
		return;
	}
	
	//print board and ask for a play
	a->print_board();
	
	int c,x=1;char *l;
	l=readline("Player O - Choose a column: ");
	add_history(l);
	while(x){
		while((c=isn2(l))==-1){
			l=readline("Invalid! Choose other: ");
			add_history(l);
		}
		x = a->play(c,1);
		if(x){
			l=readline("Invalid! Choose other: ");
			add_history(l);
		}
	}
	printf("\n");
	flip = (!flip);
	game();
	return;
}

//bot x with minimax
void game_bot_mm_x(){
	//check if there is a winner or a draw
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

//bot o with minimax
void game_bot_mm_o(){
	//check if there is a winner or a draw
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

//bot x with alphabeta
void game_bot_ab_x(){
	//check if there is a winner or a draw
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

//bot o with alphabeta
void game_bot_ab_o(){
	//check if there is a winner or a draw
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

//ptint winner or draw
void end(int x){
	
	switch(x){
		case 0:
			printf("DRAW!\n");
			break;
		case 1:
			printf("O Player Wins!\n");
			break;
		case 2:
			printf("X Player Wins!\n");
			break;
	}
	if(botvbot==1)
		printf("X depth: %d\nO depth: %d\n",difficulty,difficulty2);
	else
		printf("Bot difficulty: %d\n",difficulty);
}

//check if valid string and valid number, return 1 or 2
//0 false
int is0(char *l){
	if(l==NULL)return 0;
	if(!isdigit(l[0]))return 0;
	int k = atoi(l);
	if(k<1 || k>2) return 0;
	return k;
}

//check if valid string and valid number, return 1 to 20
//0 false
int isn(char *l){
	if(l==NULL)return 0;
	if(!isdigit(l[0]))return 0;
	int k = atoi(l);
	if(k<0 || k>20) return 0;
	return k;
}

//check if valid string and valid number, return 0 or 6
//-1 false
int isn2(char *l){
	if(l==NULL)return -1;
	if(!isdigit(l[0]))return -1;
	int k = atoi(l);
	if(k<0 || k>6) return -1;
	return k;
}
