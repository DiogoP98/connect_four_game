#include "alphabeta.h"
#include <unistd.h>
#include <vector>
#include <algorithm>

#define x1  29//xpieces
#define x2  -7//opieces
#define x3  -3 //xp+op
#define x4  -11//vh

#define o1  -7//xpieces
#define o2  29//opieces
#define o3   3//xp+op
#define o4  -11//vh

long long int podas;
long long int vpodas;
long long expandidos;
int vh[] = {-1,1,3,5,3,1,-1};

int Alphabeta::alphabeta(Node *a,int k, int depthx){
	podas = 0;
	expandidos = 0;
	vpodas=0;
	int alfa = INT_MIN;
	int beta = INT_MAX;
	if (k==1)
		min_value(a,alfa,beta,depthx); //o
	else
		max_value(a,alfa,beta,depthx); //x
	printf("Numero de podas: %lld\n",podas);
	printf("Value das podas:  %lld\n",vpodas);
	printf ("Nos expandidos: %lld\n", expandidos);	
	return a->best_play;
}

int Alphabeta::max_value(Node *a, int alfa, int beta, int depth_max) {
	int opt=0;
	if(a->depth==0)opt=1;
	if(a->depth==1)opt=2;
	if(a->depth==2)opt=4;
	int k = a->final_board();
	if(k>-1 || a->depth>=depth_max){
		if(opt==1){
			//printf("\t(0) %d = %d\n",a->last_play,k);
			//s[i]->print_board();
		}
		if(opt==2){
			//printf("\t\t(1) %d = %d\n",a->last_play,k);
			//s[i]->print_board();
		}
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
	int v = INT_MIN,kk,xx,kv,fl,lp;
	//std::vector<Node*> s = a->child_list(2); //filhos do bot
	fl=1;
	lp=a->last_play;
	std::vector<std::pair<int,int> > vt;
	int xk;
	for(int i=0;i<7;i++){
		xk = x1*a->nx[i]+x2*(a->np[i]-a->nx[i]);
		vt.push_back(std::make_pair(x3*xk*a->depth + x4*vh[i],i));
	}
	std::sort(vt.begin(),vt.end());
	for (int i=0; i<7 && fl;i++) {
		kk=a->play(vt[i].second,2);
		if(!kk){
			expandidos++;
			a->depth++;
			xx = min_value ( a, alfa, beta, depth_max);
			if(opt==1){
				printf("\t(0) %d = %d\n",a->last_play,xx);
				//s[i]->print_board();
			}
			if(opt==2){
				printf("\t\t(1) %d = %d\n",a->last_play,xx);
				//s[i]->print_board();
			}
			if(opt==3){
				//printf("\t\t\t(2) %d = %d\n",s[i]->last_play,xx);
				//s[i]->print_board();
			}
			kv = std::max (v,xx);
			if (kv!=v) {
				if(a->depth==1)
					a->best_play = a->last_play;
				v=kv;
			}
			if (v>=beta){
				podas++;
				vpodas+=(vt.size()-i-1)*7^(depth_max-a->depth);
				fl=0;
			}
			alfa = std::max (alfa,v);
			//delete s[i];
			a->depth--;
			a->rmplay(lp);
		}
	}
	//for(;i<(int)s.size();i++)delete s[i];
	return v;
}


int Alphabeta::min_value(Node *a, int alfa, int beta, int depth_max) {
	int opt=0;
	if(a->depth==0)opt=1;
	if(a->depth==1)opt=2;
	if(a->depth==2)opt=4;
	int k = a->final_board();
	if(k>-1 || a->depth>=depth_max){
		if(opt==1){
			//printf("\t(0) %d = %d\n",a->last_play,k);
			//s[i]->print_board();
		}
		if(opt==2){
			//printf("\t\t(1) %d = %d\n",a->last_play,k);
			//s[i]->print_board();
		}
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
	int v = INT_MAX,kk,xx,kv,fl,lp;
	//std::vector<Node*> s = a->child_list(1); //filhos do player
	fl=1;
	lp=a->last_play;
	std::vector<std::pair<int,int> > vt;
	int xk;
	for(int i=0;i<7;i++){
		xk = o1*a->nx[i]+o2*(a->np[i]-a->nx[i]);
		vt.push_back(std::make_pair(o3*xk*a->depth + o4*vh[i],i));
	}
	std::sort(vt.begin(),vt.end());
	for (int i=0; i<7 && fl;i++) {
		kk=a->play(vt[i].second,1);
		expandidos++;
		if(!kk){
			a->depth++;
			xx = max_value (a, alfa, beta, depth_max);
			if(opt==1){
				printf("\t(0) %d = %d\n",a->last_play,xx);
				//s[i]->print_board();
			}
			if(opt==2){
				printf("\t\t(1) %d = %d\n",a->last_play,xx);
				//s[i]->print_board();
			}
			if(opt==3){
				//printf("\t\t\t(2) %d = %d\n",s[i]->last_play,xx);
				//s[i]->print_board();
			}
			kv = std::min (v,xx);
			if (kv!=v) {
				if(a->depth==1)
					a->best_play = a->last_play;
				v=kv;
			}
			if (v<=alfa){
				podas++;
				vpodas+=(vt.size()-i-1)*7^(depth_max-a->depth);
				fl=0;
			}
			beta = std::min (beta,v);
			a->depth--;
			a->rmplay(lp);
			//delete s[i];
		}
	}
	//for(; i<(int)s.size();i++) delete s[i];
	return v;
}
