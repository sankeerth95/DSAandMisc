def searchFor(A, ser):
	i = binarySearch(A, ser)
	if A[i] == ser: return i
	else: return -1

def binarySearch(A, ser):
	n = len(A)
	if n <= 1: return n-1
 
	i = n/2
	if A[i] == ser: return i
	if A[i] < ser: return i+binarySearch(A[i:n], ser)
	else: return binarySearch(A[0:n-n/2], ser)

A = [2, 4, 6, 23, 45, 334, 567]
print searchFor(A, 567)

