#include<iostream>
using namespace std;

void selectionSort(int A, const int n){


	for(int i = 0; i < n; i++){
	int index = i, min = A[i], temp;

		for(int j = i; j<n; j++){
			if(A[j] < min){
				index = j;
				min = A[j];
			}			
		}

	temp = A[index];
	A[index] = A[i];
	A[i] = temp;
	}

}

int main(){

	int A[] = {2, 4, 1, 65, 7, 4, 3, 23};

	selectionSort(A, 8);
	
	for(int i = 0; i < 8; i++){

		cout<<A[i]<<" ";
	}
	cout<<endl;
	return 0;
}
