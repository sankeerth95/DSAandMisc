
#fHandle = open("input.txt", 'r')
#A = [int(num) for num in (fHandle.read()).split()]

def insertionSort(A):

	n = len(A)
	for i in range(n-1):
		
		pos = i+1
		while pos > 0:
			if A[pos] > A[pos-1]:
				break
			
			temp = A[pos]
			A[pos] = A[pos - 1]
			A[pos-1] = temp
			pos -= 1
		
	return A
	
A = [3, 2, 6, 2, 6, 5, 3, 8]
B = insertionSort(A)
print B