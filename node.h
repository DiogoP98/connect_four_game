#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;

class Node{
public:
	pair<long,int> conf[7];
	long val;
	
	Node();
	Node(Node *a);
	
	int play(int row,int player);
	int pos(int i,int j);
	vector<Node> child_list(int player);

	void print_board();
};

#endif // NODE_H
