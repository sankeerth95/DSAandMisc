#include<iostream>
#include "Queue.hpp"
using namespace std;

int main(){

	Queue<int> q(5);

	q.enqueue(4);
	int x;
	q.dequeue(x);
	cout << x <<endl;
	return 0;
}
