#include<iostream>
using namespace std;

void quickSort(int* A, const int n){

	if(n <= 1) return;
	int pivot = A[0], less_than_p = 0;

	for(int scanner = 1; scanner < n; scanner++){
		if(A[scanner] < pivot){
			int temp = A[scanner];
			A[scanner] = A[less_than_p+1];
			A[less_than_p+1] = temp;

			less_than_p++;
		}
	}


	A[0] = A[less_than_p];
	A[less_than_p] = pivot;

	quickSort(A, less_than_p);
	quickSort(A+less_than_p+1, n-less_than_p-1);
	
}

int main(){
	int A[] = {0, 4, 3, 2, 5, 6, 3, 5};
	
	int n = sizeof(A)/4;
	
	quickSort(A,n);
	for(int i = 0; i < n; i++){
		cout<<A[i]<<" ";
	}
	cout<<endl;

	return 0;
}
