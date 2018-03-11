#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <stdio.h>
#include <climits>
#include <cmath>

#include "node.h"
class Alphabeta{
public:
  static int alphabeta(Node *a);
  static int min_value(Node  *a, int alfa, int beta, int depth_in, int depth_max);
  static int max_value(Node *a, int alfa, int beta, int depth_in, int depth_max);
};


#endif // ALPHABETA_H
