#include "alfabeta.h"
#include <climits>
#include <cmath>

int AlfaBeta(Node *a,int k){
  int alfa = INT_MIN;
  int beta = INT_MAX;
  if (k==1)
    min_value(a,alfa,beta,a->depth,10);
  else
    max_value(a,alfa,beta,a->depth,10);
  return a->best_play;
}

int max_value(Node *a, int alfa, int beta, int depth_in, int depth_max) {
  int k = a->final_board();
  if(k>-1 || a->depth-depth_in>depth_max){
    switch(k){
    case 1:
      return -512;
    case 2:
      return  512;
    case 0:
      return    0;
    default:
      return a->eval_board();
    }
  }
  int v = INT_MIN;
  std::vector<Node> s = a->child_list(2); //filhos do bot
  for (int i=0; i<(int)s.size();i++) {
    int k = std::max (v,min_value ( &s[i], alfa, beta, depth_in, depth_max));
    if (v>=beta)
      return v;
    alfa = std::max (alfa,v);
  }
  return v;
}


int max_value(Node *a, int alfa, int beta, int depth_in, int depth_max) {
  int k = a->final_board();
  if(k>-1 || a->depth-depth_in>depth_max){
    switch(k){
    case 1:
      return -512;
    case 2:
      return  512;
    case 0:
      return    0;
    default:
      return a->eval_board();
    }
  }
  int v = INT_MAX;
  std::vector<Node> s = a->child_list(1); //filhos do player
  for (int i=0; i<(int)s.size();i++) {
    int k = std::min (v,max_value ( &s[i], alfa, beta, depth_in, depth_max));
    if (v<=alfa)
      return v;
    beta = std::min (beta,v);
  }
  return v;
}