#include "alphabeta.h"

//some constants for sorting the order of child expansion

#define x1  29//xpieces
#define x2  -7//opieces
#define x3  -3 //xp+op
#define x4  -11//vh

#define o1  -7//xpieces
#define o2  29//opieces
#define o3   3//xp+op
#define o4  -11//vh

//1 - sort childs
//0 - dont sort childs
#define wsort 1

//variables
long long int podas;//number of prunes
long long expandidos;//number of nodes expanded
int vh[] = {-1,1,3,5,3,1,-1};//some constants


int Alphabeta::alphabeta(Node *a,int k, int depthx){
	
	//Check if there is a winning play
	int lp = a->last_play; 
	for(int i=0;i<7;i++){
		int erro_play = a->play(i,k);
		if(!erro_play){
			int win = a->final_board();
			a->rmplay(lp);
			if(win == k) return i;
		}
	}
	
	podas = 0;
	expandidos = 0;
	int alfa = INT_MIN;
	int beta = INT_MAX;
	
	if (k==1)
		min_value(a,alfa,beta,depthx); //o
	else
		max_value(a,alfa,beta,depthx); //x
	printf("Numero de podas: %lld\n",podas);
	printf ("Nos expandidos: %lld\n", expandidos);	
	return a->best_play;
}

int Alphabeta::max_value(Node *a, int alfa, int beta, int depth_max) {
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
	int v = INT_MIN,kk,xx,kv,podar,lp;
	podar=0;
	lp=a->last_play;
	std::vector<std::pair<int,int> > vt;
	int xk;
	for(int i=0;i<7;i++){
		xk = x1*a->nx[i]+x2*(a->np[i]-a->nx[i]);
		vt.push_back(std::make_pair(x3*xk*a->depth*wsort + x4*vh[i]*wsort,i));
	}
	std::sort(vt.begin(),vt.end());
	for (int i=0; i<7 && !podar;i++) {
		kk=a->play(vt[i].second,2);
		if(!kk){
			expandidos++;
			a->depth++;
			xx = min_value ( a, alfa, beta, depth_max);
			
			//for printing value of childs of first 2 levels
			if(opt==1){
				printf("\t(0) %d = %d\n",a->last_play,xx);
			}
			if(opt==2){
				printf("\t\t(1) %d = %d\n",a->last_play,xx);
			}
			
			kv = std::max (v,xx);
			if (kv!=v) {
				if(a->depth==1)
					a->best_play = a->last_play;
				v=kv;
			}
			if (v>=beta){
				podas++;
				podar=1;
			}
			alfa = std::max (alfa,v);
			a->depth--;
			a->rmplay(lp);
		}
	}
	return v;
}


int Alphabeta::min_value(Node *a, int alfa, int beta, int depth_max) {
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
	int v = INT_MAX,kk,xx,kv,podar,lp;
	podar=0;
	lp=a->last_play;
	std::vector<std::pair<int,int> > vt;
	int ok;
	for(int i=0;i<7;i++){
		ok = o1*a->nx[i]+o2*(a->np[i]-a->nx[i]);
		vt.push_back(std::make_pair(o3*ok*a->depth*wsort + o4*vh[i]*wsort,i));
	}
	std::sort(vt.begin(),vt.end());
	for (int i=0; i<7 && !podar;i++) {
		kk=a->play(vt[i].second,1);
		expandidos++;
		if(!kk){
			a->depth++;
			xx = max_value (a, alfa, beta, depth_max);
			
			//for printing value of childs of first 2 levels
			if(opt==1){
				printf("\t(0) %d = %d\n",a->last_play,xx);
			}
			if(opt==2){
				printf("\t\t(1) %d = %d\n",a->last_play,xx);
			}

			kv = std::min (v,xx);
			if (kv!=v) {
				if(a->depth==1)
					a->best_play = a->last_play;
				v=kv;
			}
			if (v<=alfa){
				podas++;
				podar=1;
			}
			beta = std::min (beta,v);
			a->depth--;
			a->rmplay(lp);
		}
	}
	return v;
}
