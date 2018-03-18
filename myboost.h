#ifndef MYBOOST_H
#define MYBOOST_H

#include <stdio.h>
#include <limits.h>
#include <list>
#include <vector>

class MyBoost{
public:

	static void load_boost();
	static int  eval(int x);
	static int  eval_aux(int n[]);
};

#endif // MYBOOST_H
