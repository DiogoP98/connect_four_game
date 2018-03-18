#include "minimax.h"

long long expandidos;

int Minimax::minimax(Node *a,int k, int depthx){
	expandidos = 0;
	if(k==1)min_value(a,depthx); //o 
	else max_value(a,depthx);    //x 
	printf ("Nos expandidos: %lld\n", expandidos);
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
				//printf("%d\n",a->depth);
				//a->print_board();
				return a->eval_board();
		}
	}
	int val = INT_MIN,x,lp,kk;
	lp=a->last_play;
	//std::vector<Node*> l = a->child_list(2);
	for(int i=0;i<7;i++){
		
		//a->print_board();
		kk=a->play(i,2);
		//printf("a %d\n",kk);
		
		if(!kk){
			expandidos++;
			a->depth++;
			x = min_value(a,depth_max);
			//printf("%d\n",x);
			//if(x>600)a->print_board();
			//exit(1);
			if(opt==1){
				printf("\t%d = %d (0)\n",a->last_play,x);
				//s[i]->print_board();
			}
			if(opt==2){
				printf("\t\t%d = %d (1)\n",a->last_play,x);
				//s[i]->print_board();
			}
			if(val<x){
				//printf("%d\n",a->depth-depth_in);
				if(a->depth==1)
					a->best_play=a->last_play;
				val = x; 
			}
			a->depth--;
			a->rmplay(lp);
			//delete l[i];
		}
	}
	//printf("%d\n",val);
	//a->print_board();
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
				//printf("%d\n",a->depth);
				//a->print_board();
				return a->eval_board();
		}
	}
	int val = INT_MAX,x,lp,kk;
	lp=a->last_play;
	//std::vector<Node*> l = a->child_list(1);
	for(int i=0;i<7;i++){
		
		//a->print_board();
		kk=a->play(i,1);
		//printf("b %d\n",kk);
		
		if(!kk){
			expandidos++;
			a->depth++;
			x = max_value(a,depth_max);
			//printf("%d\n",x);
			//if(x>600)a->print_board();
			//exit(1);
			if(opt==1){
				printf("\t%d = %d (0)\n",a->last_play,x);
				//s[i]->print_board();
			}
			if(opt==2){
				printf("\t\t%d = %d (1)\n",a->last_play,x);
				//s[i]->print_board();
			}
			if(val>x){
				//printf("%d\n",a->depth-depth_in);
				if(a->depth==1)
					a->best_play=a->last_play;
				val = x; 
			}
			a->depth--;
			a->rmplay(lp);
			//delete l[i];
		}
	}
	//printf("%d\n",val);
	//a->print_board();
	return val;
}
