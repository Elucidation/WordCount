#include <iostream>
#include <map>
using namespace std;

/*
Draft 1, basic working example without safety-checks
STD usage: Uses std::cin, std::str, and std::map

To build on linux systems: make
To run with a test input file TEST_INPUT: wordcount.exe < TEST_INPUT
*/
int main(int argc, char const *argv[])
{
	string word; // string buffer to hold a single word (set of chars delimited by space)
	map<const string, int> wordCounts; // Red-black tree storing words & # of times encountered
	// Has O(log n) I/O

	while (cin >> word) wordCounts[word]++; // So for n words has O(n) * O(log n) = O(nlogn) input

	// Iterating over the already sorted tree is O(n)
	map<const string, int>::reverse_iterator it; // Iterator over map
	for (it=wordCounts.rbegin(); it != wordCounts.rend(); ++it) 
		cout << it->first << " -> " << it->second << endl;

	return 0;
}