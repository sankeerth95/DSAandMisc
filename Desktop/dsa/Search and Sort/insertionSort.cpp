#include <iostream>
using namespace std;

void insertionSort(int* A, const int n){

	for(int i = 0; i < n; i++){

		for(int j = i; j>0; j--){
			if(A[j] > A[j-1]) break;
			int temp = A[j];
			A[j] = A[j-1];
			A[j-1] = temp;
		}
	}
}

int main(){
	
	int A[] = {4, 3, 2, 5, 6, 3, 5};

	insertionSort(A, 7);

	for(int i = 0; i < 7; i++){

		cout<<A[i]<<" ";
	}
	cout<<endl;
	
	return 0;
}

