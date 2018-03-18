#include "node.h"
#include <unistd.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

//unit vector for view segments
std::pair<int,int> unit_vector[] = {std::make_pair( 1,-1),
									std::make_pair( 0,-1),
									std::make_pair(-1,-1),
									std::make_pair(-1, 0)};
									

//initial constructor
Node::Node(){
	//initialize conf
	for(int i=0;i<6;i++){
		for(int j=0;j<7;j++)
			this->conf[i][j]=3;
		this->np[i]=0;
		this->nx[i]=0;
	}
	this->np[6]=0;
	this->nx[6]=0;
	//intialize last play
	this->depth = 0;
	this->last_play = 0;
}

//constructor with node
Node::Node(Node *a){
	//copy conf from a
	for(int i=0;i<6;i++){
		for(int j=0;j<7;j++)
			this->conf[i][j]=a->conf[i][j];
		this->np[i]=a->np[i];
	}
	this->np[6]=a->np[6];
	//copy last_play from a
	
	this->depth = a->depth + 1;
	this->last_play = a->last_play;
}

//play piece of player in column
int Node::play(int column,int player){
	//test if piece can be played (game not over, column index valid, column not full)
	if(column<0 || column>6 || this->np[column]>5 || this->final_board()!=-1)
		return 1;
	
	this->conf[5-this->np[column]][column]=player;
	this->np[column]++;
	if(player==2){
		this->nx[column]+=1;
		if(column>0)this->nx[column-1]+=10;
		if(column<6)this->nx[column+1]+=10;
	}
	
	//this is the last play
	this->last_play = column;
	return 0;
}

int Node::rmplay(int lp){
	int c = this->last_play;
	if(this->np[c]==0)return 1;
	int p = this->conf[5-(this->np[c]-1)][c];
	this->conf[5-(this->np[c]-1)][c]=3;
	this->np[c]--;
	
	if(p==2){
		this->nx[c]-=1;
		if(c>0)this->nx[c-1]-=10;
		if(c<6)this->nx[c+1]-=10;
	}
	
	//this is the last play
	this->last_play = lp;
	return 0;
}

//pos i,j, i starting at 0 from bottom, j start from 0, from left
int Node::pos(int i,int j){
	//test if valid indexes
	if(j<0 || j>6 || i<0 || i>5){
		printf("Error: pos out of board! %d %d\n",i,j);
		exit(1);
	}
	return this->conf[5-i][j];
}

//make a child vector
std::vector<Node*> Node::child_list(int player){
	std::vector<Node*> l;
	for(int i=0;i<7;i++){
		Node *x = new Node(this);
		//x->depth--;
		//try play, if successful add to vector
		if(!x->play(i,player))
			l.push_back(x);
	}
	//printf("%d",l[0].depth)
	return l;
}

//test if game end
//-1 game not over
//0 draw
//1/2 player win
int Node::final_board(){
	//if column empty, game not over
	if(this->np[this->last_play]==0) return -1;
	
	
	int flag=0;//test if board full
	for(int i=0;i<7;i++)
		if(np[i]!=6){
			flag=1;
			break;
		}
	
	//last piece played
	int x = this->pos(this->np[this->last_play]-1,this->last_play);
	int s,i=this->np[this->last_play]-1,j=this->last_play,ix,jx;
	//test if segment of at leat 4
	for(int k=0;k<4;k++){
		s=0;
		ix = i;jx=j;
		ix-=unit_vector[k].first;
		jx-=unit_vector[k].second;
		while(ix>=0 && ix<6 && jx>=0 && jx<7){
			if(pos(ix,jx)!=x)break;
			s++;
			ix-=unit_vector[k].first;
			jx-=unit_vector[k].second;
		}
		ix = i;jx=j;
		ix+=unit_vector[k].first;
		jx+=unit_vector[k].second;
		while(ix>=0 && ix<6 && jx>=0 && jx<7){
			if(pos(ix,jx)!=x)break;
			s++;
			ix+=unit_vector[k].first;
			jx+=unit_vector[k].second;
		}
		s++;
		if(s>=4)return x;//player x wins
	}
	
	if(!flag) return 0;//board full and none player not win
	return -1;
}

//eval segment of 4 starting from i,j, and with the 4 first unit vectors
//not using all to avoid repetitions
int Node::eval(int i, int j){
	int val=0;
	int x;
	int ix,jx,l,s,xx;
		
	int sign;
	//go through first 4 vectors
	for(int k=0;k<4;k++){
		l=0;//will have length of segment
		x = pos(i,j); //piece in i,j
		
		//s will have number of pieces of player x
		if(x!=3)s=1;
		else s=0;//if empty
		
		ix=i+unit_vector[k].first;
		jx=j+unit_vector[k].second;
		//while inside board and lengh less than 4
		while(ix>=0 && ix<6 && jx>=0 && jx<7 && l<3){
			xx = pos(ix,jx);
			if(x==3 && xx!=3)x=xx;//if first piece not empty in segment
			
			if(x!=3 && xx==x)s++;//count pieces not empty equals
			else if(xx!=3) break;//if piece diff break
			
			l++;
			ix+=unit_vector[k].first;
			jx+=unit_vector[k].second;
		}
		//if segment of 4 and not segment empty
		if(l==3 && x!=3){
			if(x==1)sign=-1;//sign
			else sign=1;
			
			switch(s){
				case 1:
					val+=sign*1;
					break;
				case 2:
					val+=sign*10;
					break;
				case 3:
					val+=sign*50;
					break;
				case 4:
					val+=sign*512;
					break;
			}
		}
	}
	return val;
}

//evaluate board
int Node::eval_board(){
	/*
	int val=0;
	for(int i=5;i>=0;i--){
		for(int j=0;j<7;j++){
			//to avoid unnecessary work
			if(!(i<3 && j<3)){
				val+=eval(i,j);
			}
		}
	}
	if(val == 0) return val;
	int x = this->pos(this->np[this->last_play]-1,this->last_play);
	//if(x==1) val-=16;
	//else     val+=16;
	*/
	int val = 0,temp;
	int col[7],dgp[6],dgn[6];
	for(int i=0;i<6;i++){
		dgp[i]=0;
		dgn[i]=0;
		col[i]=0;
	}
	col[6]=0;
	//printf("\n");
	for(int i=5;i>=0;i--){
		temp = 0;
		for(int j=0;j<7;j++){
			temp=temp*10+this->conf[i][j];
			col[j] = col[j]*10+this->conf[i][j];
			//printf("%d %d %d %d\n",i,j,this->conf[i][j],col[j]);
			
			//printf("%d %d\n",i,j);
			
			if((i+j-3)>=0 && (i+j-3)<6){
				//printf("dgp %d %d %d\n",i,j,i-j+2);
				dgp[i+j-3] = dgp[i+j-3]*10+this->conf[i][j];
			}
				
			//printf("%d %d\n",i,j);
			
			if((j-i+2)>=0 && (j-i+2)<6){
				//printf("dgn %d %d %d\n",i,j,i+j-3);
				dgn[j-i+2] = dgn[j-i+2]*10+this->conf[i][j];
			}
				
			//printf("%d %d\n",i,j);
		}
		//printf("lin %d %d\n",temp,Global::m7[temp]);
		val+=Global::m7[temp];
	}
	
	for(int i=0;i<6;i++){
		if(dgp[i]<10000){
			//printf("dgp4 %d %d\n",dgp[i],Global::m4[dgp[i]]);
			val+=Global::m4[dgp[i]];
		}
		else if(dgp[i]<100000){
			//printf("dgp5 %d %d\n",dgp[i],Global::m5[dgp[i]]);
			val+=Global::m5[dgp[i]];
		}
		else if(dgp[i]<1000000){
			//printf("dgp6 %d %d\n",dgp[i],Global::m6[dgp[i]]);
			val+=Global::m6[dgp[i]];
		}
		
		if(dgn[i]<10000){
			//printf("dgn4 %d %d\n",dgn[i],Global::m4[dgn[i]]);
			val+=Global::m4[dgn[i]];
		}
		else if(dgn[i]<100000){
			//printf("dgn5 %d %d\n",dgn[i],Global::m5[dgn[i]]);
			val+=Global::m5[dgn[i]];
		}
		else if(dgn[i]<1000000){
			//printf("dgn6 %d %d\n",dgn[i],Global::m6[dgn[i]]);
			val+=Global::m6[dgn[i]];
		}
		//printf("col %d %d\n",col[i],Global::m6c[dgn[i]]);
		val+=Global::m6c[col[i]];
	}
	//printf("col %d %d\n",col[6],Global::m6c[6]);
	val+=Global::m6c[col[6]];
	int x = this->pos(this->np[this->last_play]-1,this->last_play);
	if(x==1) val+=16;
	else     val-=16;
	return val;
}

//print board pretty
void Node::print_board(){
	int x;
	for(int i=0;i<17;i++) printf("*");
	printf("\n");
	for(int i=5;i>=0;i--){
		printf("* ");
		for(int j=0;j<7;j++){
			x = pos(i,j);
			switch(x){
				case 3:
					printf("- ");
					break;
				case 1:
					printf(ANSI_COLOR_RED "O " ANSI_COLOR_RESET);
					break;
				case 2:
					printf(ANSI_COLOR_YELOW "X " ANSI_COLOR_RESET);
					break;
			}
		}
		printf("*");
		printf("\n");
	}
	for(int i=0;i<17;i++) printf("*");
	printf("\n  ");
	for(int i=0;i<7;i++) printf("%d ",i);
	printf("\n\n");
}
