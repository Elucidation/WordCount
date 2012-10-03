#include <iostream>
#include <unordered_map>
#include "parser.h"
#include "sorter.h"
using namespace std;

/*
Draft 2, basic working example without safety-checks
STD usage: Uses std::cin, std::str, and std::unordered_map

To build on linux systems: make
To run with a test input file TEST_INPUT: wordcount.exe < TEST_INPUT

*/

typedef std::unordered_map<string, int> hashmap;

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		cout << "Usage: wordcount.exe INPUT_FILE" << endl;
		return 0;
	}

	string word; // string buffer to hold a single word (set of chars delimited by space) (auto-allocates past 2**30 chars at least)
	
	// Red-black tree storing words & # of times encountered
	//   Entries are inserted into tree via compare by string (which is alphabetical)
	hashmap wordCounts;  // Has O(log n) I/O
	
	const char* filename = argv[1]; // Filename

	// READING WORDS
	/////// FILE I/O
	Parser txtParser(filename);
	cout << "Parsing input file '"<< filename <<"' to map..." << endl;
	while (!txtParser.eof()) {
		word = txtParser.next(); // all letters converted to lower-case
		if (not word.empty())
			wordCounts[word]++;
	}
	cout << "Finished reading input in." << endl << endl;;
	txtParser.close();
	///////

	// PRINTING REVERSE-ALPHABETICAL LIST OF WORD COUNTS
	/////// O(n) routine to create list of words to be sorted
	string words[wordCounts.size()]; // Key list to be sorted
	int i=0;
	for (hashmap::iterator it=wordCounts.begin(); it != wordCounts.end(); ++it) {
		words[i] = it->first;
		i++;
	}

	/////// unordered_map needs to be sorted by key alphabetically
	// Sort words in alphabetical order
	quicksort(words, wordCounts.size()); // Quicksort average case is O(nlogn), worst O(n^2) when list is in reverse order (highly unlikely in these hashing cases)

	// Reverse iterate over words and get hash value as well, an O(1) operation n times yielding O(n)
	for (int i = wordCounts.size()-1; i >= 0; --i) {
		cout << words[i] << " -> " << wordCounts[ words[i] ] << endl;
	}

	///////
	cout << "Number of entries in list: " << wordCounts.size() << endl;

	// In total, biggest O is due to sort, an average/best case performance due to quicksort of O(nlogn),
	//   worst case O(n^2) with reverse ordered list by hash value (unlikely), memory used is of order O(n) for quicksort

	return 0;
}