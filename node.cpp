#include "node.h"

//unit vector for view segments
std::pair<int,int> unit_vector[] = {std::make_pair( 1,-1),
									std::make_pair( 0,-1),
									std::make_pair(-1,-1),
									std::make_pair(-1, 0),
									std::make_pair(-1, 1),
									std::make_pair( 0, 1),
									std::make_pair( 1, 1)};

//initial constructor
Node::Node(){
	//initialize conf
	for(int i=0;i<7;i++){
		this->conf[i].first=0;
		this->conf[i].second=0;
	}
	//intialize last play
	this->depth = 0;
	this->last_play = 0;
}

//constructor with node
Node::Node(Node *a){
	//copy conf from a
	for(int i=0;i<7;i++){
		this->conf[i].first=a->conf[i].first;
		this->conf[i].second=a->conf[i].second;
	}
	//copy last_play from a
	this->depth = a->depth + 1;
	this->last_play = a->last_play;
}

//play piece of player in column
int Node::play(int column,int player){
	//test if piece can be played (game not over, column index valid, column not full)
	if(column<0 || column>6 || this->conf[column].second==6 || this->final_board()!=-1)
		return 1;
	this->conf[column].first*=10;
	this->conf[column].first+=player;
	this->conf[column].second++;
	//this is the last play
	this->last_play = column;
	return 0;
}

//pos i,j, i starting at 0 from bottom, j start from 0, from left
int Node::pos(int i,int j){
	//test if valid indexes
	if(j<0 || j>6 || i<0 || i>5){
		printf("Error: pos out of board!\n");
		exit(1);
	}
	//if blank space return 0
	if(this->conf[j].second<=i)
		return 0;
	
	//return piece
	int a = this->conf[j].first / pow(10,this->conf[j].second-i-1);
	return a%10;
}

//make a child vector
std::vector<Node> Node::child_list(int player){
	std::vector<Node> l;
	Node *x;
	for(int i=0;i<7;i++){
		x = new Node(this);
		//try play, if successful add to vector
		if(!x->play(i,player))
			l.push_back(x);
	}
	return l;
}

//test if game end
//-1 game not over
//0 draw
//1/2 player win
int Node::final_board(){
	//if column empty, game not over
	if(this->conf[this->last_play].second==0) return -1;
	
	
	int flag=0;//test if board full
	for(int i=0;i<7;i++)
		if(conf[i].second!=6){
			flag=1;
			break;
		}
	
	//last piece played
	int x = this->pos(this->conf[this->last_play].second-1,this->last_play);
	int s,i=this->conf[this->last_play].second-1,j=this->last_play,ix,jx;
	
	//test if segment of at leat 4
	for(int k=0;k<7;k++){
		s=0;ix=i;jx=j;
		ix+=unit_vector[k].first;
		jx+=unit_vector[k].second;
		while(ix>=0 && ix<6 && jx>=0 && jx<7){
			if(pos(ix,jx)!=x)break;
			s++;
			ix+=unit_vector[k].first;
			jx+=unit_vector[k].second;
		}
		//3 because not counting last piece played
		if(s>=3)return x;//player x wins
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
		if(x!=0)s=1;
		else s=0;//if empty
		
		ix=i+unit_vector[k].first;
		jx=j+unit_vector[k].second;
		//while inside board and lengh less than 4
		while(ix>=0 && ix<6 && jx>=0 && jx<7 && l<3){
			xx = pos(ix,jx);
			if(x==0 && xx!=0)x=xx;//if first piece not empty in segment
			
			if(x!=0 && xx==x)s++;//count pieces not empty equals
			else if(xx!=0) break;//if piece diff break
			
			l++;
			ix+=unit_vector[k].first;
			jx+=unit_vector[k].second;
		}
		//if segment of 4 and not segment empty
		if(l==3 && x!=0){
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
	int val=0;
	for(int i=5;i>=0;i--){
		for(int j=0;j<7;j++){
			//to avoid unnecessary work
			if(!(i<3 && j<3)){
				val+=eval(i,j);
			}
		}
	}
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
				case 0:
					printf("- ");
					break;
				case 1:
					printf("o ");
					break;
				case 2:
					printf("x ");
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
