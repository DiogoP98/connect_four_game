#ifndef NODE_H
#define NODE_H

#include <stdio.h>

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
	
	int play(int column,int player);
	int rmplay(int lp);
	int pos(int i,int j);
	int final_board();
	int eval_board();

	void print_board();
};

#endif // NODE_H

