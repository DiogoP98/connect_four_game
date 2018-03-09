#include "node.h"

Node::Node(){
	for(int i=0;i<7;i++){
		this->conf[i].first=0;
		this->conf[i].second=0;
	}
}

Node::Node(Node *a){
	for(int i=0;i<7;i++){
		this->conf[i].first=a->conf[i].first;
		this->conf[i].second=a->conf[i].second;
	}
}

int Node::play(int row,int player){
	if(row<0 || row>6 || conf[row].second==6)
		return 1;
	this->conf[row].first*=10;
	this->conf[row].first+=player;
	this->conf[row].second++;
	return 0;
}

int Node::pos(int i,int j){
	if(j<0 || j>6 || i<0 || i>5){
		printf("Error: pos out of board!\n");
		exit(1);
	}
	if(this->conf[j].second<=i)
		return 0;
	int a = this->conf[j].first / (long)pow(10,this->conf[j].second-i-1);
	return a%10;
}

vector<Node> Node::child_list(int player){
	vector<Node> l;
	Node *x;
	for(int i=0;i<7;i++){
		x = new Node(this);
		if(!x->play(i,player))
			l.push_back(x);
	}
	return l;
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
