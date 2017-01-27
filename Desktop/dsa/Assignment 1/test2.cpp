#include <iostream>
#include <list>
using namespace std;

void foo(int s){

	
}

int main(){

	std::list<int> x;

	x.push_back(2);
	x.push_back(24);
	x.push_back(56);
	x.push_back(95);

	std::list<int>::iterator it;

	for(it = x.begin(); it != x.end(); it++)
	std::cout<<*it<<std::endl;

	std::cout<<std::endl;

	it--;it--;
	std::cout<<*(x.begin())<<std::endl;

	
	return 0;
}
