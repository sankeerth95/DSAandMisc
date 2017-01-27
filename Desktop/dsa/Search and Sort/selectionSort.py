
#fHandle = open("input.txt", 'r')
#A = [int(num) for num in (fHandle.read()).split()]

def selectionSort(A):
	for startPoint in range(len(A)-1):
		
		searchMin = startPoint
		min = A[searchMin]
		indexMin = searchMin
		
		for index in range(serachmin+1, len(A)):
			if A[index] < min:
				min = A[index]
				indexMin = index
		
		
		A[indexMin] = A[startPoint]
		A[startPoint] = min
	
	return A
	
A = [3, 2, 6, 2, 6, 5, 3, 8]
B = selectionSort(A)
print B

