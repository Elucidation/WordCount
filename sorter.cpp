#include "sorter.h"

/* Input is an array of strings, the array length is expected to be arrLen */
void quicksort(string arr[], const int arrLen) {
	if (arrLen <= 0) return; // If passed empty array do nothing
	quicksortR(arr, 0, arrLen-1);
}

/* Sorts a sub-array of strings by alphabetical order */
void quicksortR(string arr[], int left, int right) {
	// avg O(nlogn) sort, O(n) memory
	int a = left, b = right;
	string tmp, pivot = arr[ (left+right)/2 ]; // truncates down

	while (a <= b) {
		while (arr[a] < pivot)
			a++;
		while (arr[b] > pivot)
			b--;
		if (a <= b) {
			// Swap a & b
			tmp = arr[a];
			arr[a] = arr[b];
			arr[b] = tmp;
			a++;
			b--;
		}
	}

	// The 2 recursive calls here result in a log n depth tree, also best case O(log n)
	if (left < b)
		quicksortR( arr, left, b );	
	if (a < right)
		quicksortR( arr, a, right );
}