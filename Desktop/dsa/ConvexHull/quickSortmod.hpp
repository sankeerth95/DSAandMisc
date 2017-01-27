
template<class T>

void quickSort(T* A, const int n){

	if(n <= 1) return;
	T pivot = A[0];
	int less_than_p = 0;

	for(int scanner = 1; scanner < n; scanner++){
		if(A[scanner] < pivot){
			T temp = A[scanner];
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


