def quickSort(A):
	n = len(A)
	pivot = A[0]

	less_than_p = 0
	
	for i in range(n-1):
		
		scan_index = i+1
		if A[scan_index] < pivot:
			temp = A[less_than_p+1]
			A[less_than_p+1] = A[scan_index]
			A[scan_index] = temp
			less_than_p += 1
	
	A[0] = A[less_than_p]
	A[less_than_p] = pivot
	if less_than_p > 0:
		A[0:less_than_p] = quickSort(A[0:less_than_p])
	if less_than_p+1 < n:
		A[less_than_p+1:n] = quickSort(A[less_than_p+1:n])
	
	return A
	
	
A = [3, 2, 6, 2, 6, 5, 3, 8]
B = quickSort(A)
print B