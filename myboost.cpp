#include "myboost.h"
#include "common.h" 

std::unordered_map<int,int> Global::m4;
std::unordered_map<int,int> Global::m5;
std::unordered_map<int,int> Global::m6;
std::unordered_map<int,int> Global::m7;
std::unordered_map<int,int> Global::m6c;

std::vector<int> p4;
std::vector<int> p5;
std::vector<int> p6;

void MyBoost::load_boost(){
	std::list<int> temp;
	
	temp.push_back(0);
	int x;
	while(temp.size()>0){
		x = temp.front();
		temp.pop_front();
		if(x<100){
			temp.push_back(x*10+1);
			temp.push_back(x*10+2);
			temp.push_back(x*10+3);
		}
		else{
			p4.push_back(x*10+1);
			p4.push_back(x*10+2);
			p4.push_back(x*10+3);
		}
	}
	
	for(int i=0;i<(int)p4.size();i++){
		p5.push_back(p4[i]*10+1);
		p5.push_back(p4[i]*10+2);
		p5.push_back(p4[i]*10+3);
		//printf("4: %d %d\n",p4[i],eval(p4[i]));
		Global::m4.insert(std::make_pair(p4[i],eval(p4[i])));
	}
	
	//printf("\n");
	for(int i=0;i<(int)p5.size();i++){
		p6.push_back(p5[i]*10+1);
		p6.push_back(p5[i]*10+2);
		p6.push_back(p5[i]*10+3);
		
		//printf("5: %d %d\n",p5[i],eval(p5[i]));
		Global::m5.insert(std::make_pair(p5[i],eval(p5[i])));
	}
	//printf("\n");
	for(int i=0;i<(int)p6.size();i++){	
		//printf("6: %d %d\n",p6[i],eval(p6[i]));
		Global::m6.insert(std::make_pair(p6[i],eval(p6[i])));
		
		//printf("7: %d %d\n",p6[i]*10+1,eval(p6[i]*10+1));
		//printf("7: %d %d\n",p6[i]*10+2,eval(p6[i]*10+2));
		//printf("7: %d %d\n",p6[i]*10+3,eval(p6[i]*10+3));
		Global::m7.insert(std::make_pair(p6[i]*10+1,eval(p6[i]*10+1)));
		Global::m7.insert(std::make_pair(p6[i]*10+2,eval(p6[i]*10+2)));
		Global::m7.insert(std::make_pair(p6[i]*10+3,eval(p6[i]*10+3)));
	}
	//printf("a\n");
	temp.push_back(0);
	int k;
	while(temp.size()>0){
		x = temp.front();
		temp.pop_front();
		
		k=x*10+1;
		while(k<100000)k=k*10+3;
		//printf("%d %d\n",k,eval(k));
		Global::m6c.insert(std::make_pair(k,eval(k)));
		k=x*10+2;
		while(k<100000)k=k*10+3;
		//printf("%d %d\n",k,eval(k));
		Global::m6c.insert(std::make_pair(k,eval(k)));
		
		if(x<10000){
			temp.push_back(x*10+1);
			temp.push_back(x*10+2);
		}
	}
	
}

int MyBoost::eval(int x){
	int n[4],val;
	n[0]=x%10;x/=10;
	n[1]=x%10;x/=10;
	n[2]=x%10;x/=10;
	n[3]=x%10;x/=10;
	val = eval_aux(n);
	while(x>0){
		n[0]=n[1];
		n[1]=n[2];
		n[2]=n[3];
		n[3]=x%10;x/=10;
		val += eval_aux(n);
	}
	return val;
}

int MyBoost::eval_aux(int n[]){
	int s=0,x=-1,i;
	for(i=0;i<4;i++){
		if(x==-1 && n[i]!=3){
			x = n[i];
			s++;
		}
		else if(n[i] == x && n[i]!=3){
			s++;
		}
		else if(n[i] != x && n[i]!=3){
			break;
		}
	}
	int sign;
	if(i==4 && x!=-1){
		if(x==1)sign=-1;//sign
		else sign=1;
		
		switch(s){
			case 1: return sign*1;
			case 2: return sign*10;
			case 3: return sign*50;
			case 4: return sign*512;
		}
	}
	return 0;
}
