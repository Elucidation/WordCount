#include "sorter.h"

void quicksort(string arr[], const int arrLen) {
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

// /* Compares strings case-insensitive until reaches a terminating null byte in either string 
//    Returns -1 if a < b, 0 if a == b, and 1 if a > b 
//    if a & b are different lengths but same up to point, shorter is considered less than.
// */
// int caselessCompare(string a, string b) {
// 	int i=0,j=0; // array pointers in a,b respectively
// 	unsigned char ca,cb;
// 	//int diff; // char difference
// 	while ( (ca = toupper(a[i])) != '\0' && (cb = toupper(b[j])) != '\0')
// 		if (ca < cb)
// 			return -1;
// 		else if (ca > cb)
// 			return 1;
// 	if (i == j)
// 		return 0;
// 	else 
// 		return (i < j ? -1 : 1);

// }