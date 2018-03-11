#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <stdio.h>

#include "node.h"
class Alphabeta{
public:
  int alphabeta(Node *a);
  int min_value(Node  *a, int alfa, int beta, int depth_in, int depth_max);
  int max_value(Node *a, int alfa, int beta, int depth_in, int depth_max);
};


#endif // ALPHABETA_H
