#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <utility>
#include <vector>

class Node{
public:
	std::pair<int,int> conf[7];
	int last_play;
	int best_play;
	int depth;
	int val;
	
	Node();
	Node(Node *a);
	
	int play(int column,int player);
	int pos(int i,int j);
	std::vector<Node> child_list(int player);
	int final_board();
	int eval(int i, int j);
	int eval_board();

	void print_board();
};

#endif // NODE_H
