def mergeSort(A):
	
	n = len(A)
	if n <= 1:
		return A
	alpha = []
	beta = []
	if n/2 > 0:
		alpha = mergeSort(A[:n/2])
	if n/2 < n:
		beta = mergeSort(A[n/2:])
	
	lalp = len(alpha)
	lbet = len(beta)
	
	iterAlpha = 0
	iterBeta = 0
	
	for i in range(n):
		
		if iterAlpha == lalp:
			A[i:n] = beta[iterBeta:lbet]
			break
		if iterBeta == lbet:
			A[i:n] = alpha[iterAlpha:lalp]
			break
		
		if alpha[iterAlpha] < beta[iterBeta]:
			A[i] = alpha[iterAlpha]
			iterAlpha+=1
		else:
			A[i] = beta[iterBeta]
			iterBeta+=1
			
	
	return A
	
A = [3, 2, 6, 2, 6, 5, 3, 8]
B = mergeSort(A)
print B