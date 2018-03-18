#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <utility>
#include <vector>

#include "common.h"

class Node{
public:
	int conf[6][7];
	int np[7];
	int last_play;
	int best_play;
	int depth;
	int nx[7];
	
	Node();
	Node(Node *a);
	
	int play(int column,int player);
	int rmplay(int lp);
	int pos(int i,int j);
	std::vector<Node*> child_list(int player);
	int final_board();
	int eval(int i, int j);
	int eval_board();

	void print_board();
};

#endif // NODE_H

