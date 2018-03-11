#ifndef ALFABETA_H
#define ALFABETA_H

#include <stdio.h>

#include "node.h"

int AlfaBeta(Node *a);
int min_value(Node  *a, int alfa, int beta, int depth_in, int depth_max);
int max_value(Node *a, int alfa, int beta, int depth_in, int depth_max)


#endif // MINIMAX_H
