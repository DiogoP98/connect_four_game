#ifndef MINIMAX_H
#define MINIMAX_H

#include <stdio.h>
#include <limits.h>

#include "node.h"
class Minimax{
public:
	static int minimax(Node *a,int k,int d);
	static int max_value(Node *a,int depth_max);
	static int min_value(Node *a,int depth_max); 
};
#endif // MINIMAX_H
