#include "node.h"

Node::Node(){
	for(int i=0;i<7;i++){
		this->conf[i].first=0;
		this->conf[i].second=0;
	}
}

Node::Node(pair<long,int> v[]){
	for(int i=0;i<7;i++){
		this->conf[i].first=v[i].first;
		this->conf[i].second=v[i].second;
	}
}

void Node::play(int row,int player){
	this->conf[row].first*=10;
	this->conf[row].first+=player;
	this->conf[row].second++;
}

int Node::pos(int i,int j){
	if(j<0 || j>6 || i<0 || i>5){
		printf("Error: pos out of board!\n");
		exit(1);
	}
	if(this->conf[j].second<=i)return 0;
	int a = this->conf[j].first / (long)pow(10,this->conf[j].second-i-1);
	return a%10;
}

void Node::print_board(){
	for(int i=5;i>=0;i--){
		for(int j=0;j<7;j++){
			printf("%d ",pos(i,j));
		}
		printf("\n");
	}
}
