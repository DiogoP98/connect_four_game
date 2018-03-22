#include "minimax.h"

long long expandidos2;//number of nodes expanded

int Minimax::minimax(Node *a,int k, int depthx){
	expandidos2 = 0;
	if(k==1)min_value(a,depthx); //o 
	else max_value(a,depthx);    //x 
	printf ("Nos expandidos: %lld\n", expandidos2);
	return a->best_play;
}

int Minimax::max_value(Node *a,int depth_max){
	int opt=0;
	if(a->depth==0)opt=1;
	if(a->depth==1)opt=2;
	int k = a->final_board();
	if(k>-1 || a->depth>=depth_max){
		switch(k){
			case 1:
				return -512;
			case 2:
				return  512;
			case 0:
				return    0;
			default:
				return a->eval_board();
		}
	}
	int val = INT_MIN,x,lp,kk;
	lp=a->last_play;
	for(int i=0;i<7;i++){
		
		kk=a->play(i,2);
		
		if(!kk){
			expandidos2++;
			a->depth++;
			x = min_value(a,depth_max);

			//for printing value of childs of first 2 levels
			if(opt==1){
				printf("\t%d = %d (0)\n",a->last_play,x);
			}
			if(opt==2){
				printf("\t\t%d = %d (1)\n",a->last_play,x);
			}
			if(val<x){
				if(a->depth==1)
					a->best_play=a->last_play;
				val = x; 
			}
			a->depth--;
			a->rmplay(lp);
			//delete l[i];
		}
	}
	return val;
}

int Minimax::min_value(Node *a,int depth_max){
	int opt=0;
	if(a->depth==0)opt=1;
	if(a->depth==1)opt=2;
	int k = a->final_board();
	if(k>-1 || a->depth>=depth_max){
		switch(k){
			case 1:
				return -512;
			case 2:
				return  512;
			case 0:
				return    0;
			default:
				return a->eval_board();
		}
	}
	int val = INT_MAX,x,lp,kk;
	lp=a->last_play;
	for(int i=0;i<7;i++){
		
		kk=a->play(i,1);
		
		if(!kk){
			expandidos2++;
			a->depth++;
			x = max_value(a,depth_max);
			
			//for printing value of childs of first 2 levels
			if(opt==1){
				printf("\t%d = %d (0)\n",a->last_play,x);
			}
			if(opt==2){
				printf("\t\t%d = %d (1)\n",a->last_play,x);
			}
			
			if(val>x){
				if(a->depth==1)
					a->best_play=a->last_play;
				val = x; 
			}
			a->depth--;
			a->rmplay(lp);
		}
	}
	return val;
}
