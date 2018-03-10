#include "node.h"

std::pair<int,int> unit_vector[] = {std::make_pair( 1,-1),
									std::make_pair( 0,-1),
									std::make_pair(-1,-1),
									std::make_pair(-1, 0),
									std::make_pair(-1, 1),
									std::make_pair( 0, 1),
									std::make_pair( 1, 1)};

Node::Node(){
	for(int i=0;i<7;i++){
		this->conf[i].first=0;
		this->conf[i].second=0;
	}
	this->last_play = 0;
}

Node::Node(Node *a){
	for(int i=0;i<7;i++){
		this->conf[i].first=a->conf[i].first;
		this->conf[i].second=a->conf[i].second;
	}
	this->last_play = a->last_play;
}

int Node::play(int column,int player){
	if(column<0 || column>6 || this->conf[column].second==6 || this->final_board()!=-1)
		return 1;
	this->conf[column].first*=10;
	this->conf[column].first+=player;
	this->conf[column].second++;
	this->last_play = column;
	return 0;
}

int Node::pos(int i,int j){
	if(j<0 || j>6 || i<0 || i>5){
		printf("Error: pos out of board!\n");
		exit(1);
	}
	if(this->conf[j].second<=i)
		return 0;
	int a = this->conf[j].first / pow(10,this->conf[j].second-i-1);
	return a%10;
}

std::vector<Node> Node::child_list(int player){
	std::vector<Node> l;
	Node *x;
	for(int i=0;i<7;i++){
		x = new Node(this);
		if(!x->play(i,player))
			l.push_back(x);
	}
	return l;
}

int Node::final_board(){
	if(this->conf[this->last_play].second==0) return -1;
	
	int flag=0;
	for(int i=0;i<7;i++)
		if(conf[i].second!=6){
			flag=1;
			break;
		}
	
	
	int x = this->pos(this->conf[this->last_play].second-1,this->last_play);
	int s,i=this->conf[this->last_play].second-1,j=this->last_play,ix,jx;
		
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
		if(s>=3)return x;
	}
	
	if(!flag) return 0;
	return -1;
}

//<flag,val>
int Node::eval(int i, int j){
	int val=0;
	int x;
	int ix,jx,l,s,xx;
		
	int sign;
	//printf("%d %d\n",i,j);
	for(int k=0;k<4;k++){
		l=0;
		
		x = pos(i,j);
		if(x!=0)s=1;
		else s=0;
		
		ix=i+unit_vector[k].first;
		jx=j+unit_vector[k].second;
		while(ix>=0 && ix<6 && jx>=0 && jx<7 && l<3){
			xx = pos(ix,jx);
			if(x==0 && xx!=0)x=xx;
			
			if(x!=0 && xx==x)s++;
			else if(xx!=0) break;
			l++;
			ix+=unit_vector[k].first;
			jx+=unit_vector[k].second;
		}
		if(l==3 && x!=0){
			if(x==1)sign=-1;
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
		//printf("\t%2d | %d %d",val,unit_vector[k].first,unit_vector[k].second);
	}
	//printf("\n---------------------------------\n");
	return val;
}

int Node::eval_board(){
	int val=0;
	for(int i=5;i>=0;i--){
		for(int j=0;j<7;j++){
			if(!(i<3 && j<3)){
				val+=eval(i,j);
			}
		}
		//printf("---------------------------------\n");
	}
	return val;
}

void Node::print_board(){
	for(int i=5;i>=0;i--){
		for(int j=0;j<7;j++){
			printf("%d ",pos(i,j));
		}
		printf("\n");
	}
	printf("\n");
}
