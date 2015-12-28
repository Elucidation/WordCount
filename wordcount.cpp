#include <iostream>
#include "parser.h"
#include "sorter.h"
#include "hashmap.h"
using namespace std;

#define MAX_PRINT_CHARS 512 // Maximum number of chars in a word to print to screen (for testing)

/*
Basic working word counter without direct string safety-checks
STD usage: Uses std::cin, std::str, and std::unordered_map

To build on linux systems: make
To run with a test input file TEST_INPUT: wordcount(.exe) TEST_INPUT
*/

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		cout << "Usage: wordcount.exe INPUT_FILE" << endl;
		return 0;
	}
	const char* filename = argv[1]; // Filename

	string word; // string buffer to hold a single word (set of chars delimited by space) (auto-allocates past 2**30 chars at least)
	
	// Hash table with collisions handled by iterating to next slot
	HashMap wordCounts; // O(1) I/O in general when with a good resizing routine
	

	// Parse words in from File
	/////// ifstream I/O occurs in Parser
	Parser txtParser(filename);
	cerr << "Parsing input file '"<< filename <<"' to map...";
	while (!txtParser.eof()) {
		word = txtParser.next(); // all letters converted to lower-case
		if (not word.empty()) {
			wordCounts.increment(word);
		}
	}
	cerr << "Successful." << endl;
	txtParser.close();
	///////

	/////// O(n) routine to create list of words to be sorted
	cerr << "Generating word list for sorting...";
	string* words = new string[wordCounts.getLength()]; // Key list to be sorted, (de)allocated with new/delete
	if (!words) {
		cerr << "Could not allocate string array of length " << wordCounts.getLength() << endl;
		return 0;
	}
	
	int i=0;
	for (HashMap::iterator entryp = wordCounts.begin(); entryp < wordCounts.end(); entryp++) {
		// cerr << "Bucket(" << entryp << ")" << endl;
		if (*entryp) // only look at slots with (*entryp) in them
		{
			words[i++] = (*entryp)->getKey();
			// cerr << "words loaded with '" << (*entryp)->getKey() << "'..." << endl;
		}
	}
	if (i != wordCounts.getLength()) {
		cerr << "Error, only " << i << "/" << wordCounts.getLength() << " words loaded from hashmap." << endl;
		return -1;
	}
	cerr << "Successful." << endl;;

	// Sort words alphabetically
	/////// unordered_map needs to be sorted by key alphabetically
	cerr << "Sorting word list reverse alphabetically...";
	quicksort(words, wordCounts.getLength()); // Quicksort average case is O(nlogn), worst O(n^2) when list is in reverse order (highly unlikely in these hashing cases)
	cerr << "Successful." << endl;;

	// Pretty-print words & counts reverse-alphabetically
	/////// Reverse iterate over words and get hash value as well, an O(1) operation n times yielding O(n)
	for (int i = wordCounts.getLength()-1; i >= 0; --i) {
		// Pretty-prints key word to MAX_PRINT_CHARS chars rather than all of them
		if (words[i].size() < MAX_PRINT_CHARS)
			cout << words[i];
		else
			cout << words[i].substr(0,MAX_PRINT_CHARS) << "...("<< words[i].size()-MAX_PRINT_CHARS<< " more)";

		cout << " -> " << wordCounts.get(words[i]) << endl;
	}

	///////
	cerr << "Number of entries in list: " << wordCounts.getLength() << endl;


	// In total, biggest O is due to sort, an average/best case performance due to quicksort of O(nlogn),
	//   worst case O(n^2) with reverse ordered list by hash value (unlikely), memory used is of order O(n) for quicksort

	delete[] words; // always delete a new

	return 0;
}