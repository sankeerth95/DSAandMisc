#include "Heap.hpp"
#include <iostream>
using namespace std;

void func(Heap<int> h){
	cout<<h.last<<endl;
	for(int i = 0; i < 20; i++) cout<<h.returnData(i)<<" ";
	cout<<endl;
}

int main(){

	Heap<int> h(20);
	int x;

func(h);
	h.insert(1, 10);
func(h);
	h.insert(2, 80);
func(h);
	h.removeMin(x);
func(h);
	h.insert(2, 16);
func(h);
	h.insert(4, 30);
func(h);
	h.removeMin(x);
func(h);
	h.insert(3, 86);
func(h);
	h.removeMin(x);
func(h);
	h.insert(5, 80);
func(h);
	h.insert(6, 40);
	//h.removeMin(x);

	func(h);

	cout << h.findMin()<<endl;
}
