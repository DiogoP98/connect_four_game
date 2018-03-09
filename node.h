#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <utility>

using namespace std;

class Node{
public:
	pair<long,int> conf[7];
	
	Node();
	Node(pair<long,int> v[]);
	
	void play(int row,int player);
	int pos(int i,int j);

	void print_board();
};

#endif // NODE_H
