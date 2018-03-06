#include <bits/stdc++.h>

using namespace std;

void copy (pair<long,int> x[], pair<long,int> k[]);

class Node {

public:
  pair<long,int> config[7];
  Node* pai;
  int utility;
  int profundidade;

  //descontructor
  ~Node(){

  }

  //constructor
  Node (pair<long,int> config[], Node* x, int k, int d) {
    copy(config,this->config);
    this->pai= x;
    this->utility=k;
    this->profundidade=d;
  }

};

void copy (pair<long,int> x[], pair<long,int> k[]) {
  for (int i=0;i<7;i++) {
    long q = x[i].first;
    int r = x[i].second;
    k[i]= make_pair(q,r);
  }
}

int main () {
  

  return 0;
}
