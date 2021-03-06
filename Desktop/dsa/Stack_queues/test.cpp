#include<iostream>
#include "Stack.hpp"
#include "Queue.hpp"
#include "LinkedList.hpp"
using namespace std;

int main(){

	Stack<int>* s = new Stack<int>(30);
	s->push(4);
	s->push(3);
	int x;
	cout<<&x<<endl;
	int* p = s->pop(x);
	p = s->pop(x);
	cout << &x <<endl;
	cout << s->isEmpty()<<endl;

	Queue<int>* q = new Queue<int>(10);
	q->enqueue(4);
	q->enqueue(5);
	q->dequeue(x);
	cout<<x<<endl;

	LinkedList<int>* l = new LinkedList<int>();
	l->addElement(4);
	l->addElement(3);
	
	
	return 0;
}
