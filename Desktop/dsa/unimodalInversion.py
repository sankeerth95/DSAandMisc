def unimodPeak(A):
	n = len(A)
	if n <= 1: return (1, A[1]) 

	i = n/2
	while True:
		if A[i] >= A[i-1] and A[i] >= A[i+1]: return (i, A[i])
		if A[i] > A[i+1]: i = i/2
		else i = i + (n-i)/2
		
