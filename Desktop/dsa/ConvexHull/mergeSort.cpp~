#include<iostream>
using namespace std;

void mergeSort(int* A, const int n){
	
	if(n <= 1) return;
	int k1 = n/2, k2 = n-n/2;
	int* B = new int[k1];
	int* C = new int[k2];
	
	for(int k = 0; k < k2; k++){
		
		if(k < k1) B[k] = A[k];
		C[k] = A[k+k1];	
	}

	mergeSort(B, k1);
	mergeSort(C, k2);
	
	int i = 0, j = 0;
	for(int k = 0; k < n; k++){
		if(i != k1 && j != k2){

			int min = B[i];
			if(B[i] > C[j]){
				min = C[j];
				j++;
			}
			else i++;
			A[k] = min;		
		}
		else if(i == k1){
			A[k] = C[j];
			j++;		
		}
		else{
			A[k] = B[i];
			i++;			
		}
	}
	return;
}

int main(){
	
	int A[] = {4, 3, 2, 5, 6, 3, 5};
	mergeSort(A, 7);
	for(int i = 0; i < 7; i++){

		cout<<A[i]<<" ";
	}
	cout<<endl;

	return 0;
}
