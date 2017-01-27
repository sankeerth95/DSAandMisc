def countingSort(A, k):

	freq = [0 for i in range(k)]
	for i in range(len(A)):
		freq[A[i]] += 1

	for i in range(k-1):
		freq[i+1] += freq[i]
	
	sortedArr = [0 for i in range(len(A))]
	for i in range(len(A)):
		sortedArr[freq[A[i]]-1] = A[i]
		freq[A[i]] -= 1

	return sortedArr


A = [4, 2, 5, 2, 1, 0, 7, 4]
sortedArr = countingSort(A, 8)
print sortedArr

