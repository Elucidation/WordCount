#include <iostream>
#include <map>
#include "parser.h"
using namespace std;

/*
Draft 1, basic working example without safety-checks
STD usage: Uses std::cin, std::str, and std::map

To build on linux systems: make
To run with a test input file TEST_INPUT: wordcount.exe < TEST_INPUT

*/

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		cout << "Usage: wordcount.exe INPUT_FILE" << endl;
		return 0;
	}

	string word; // string buffer to hold a single word (set of chars delimited by space) (auto-allocates past 2**30 chars at least)
	
	// Red-black tree storing words & # of times encountered
	//   Entries are inserted into tree via compare by string (which is alphabetical)
	map<const string, int> wordCounts;  // Has O(log n) I/O
	
	const char* filename = argv[1]; // Filename

	// READING WORDS
	/////// FILE I/O
	Parser parse(filename);
	cout << "Parsing input file '"<< filename <<"' to map..." << endl;
	while (!parse.eof()) {
		word = parse.next();
		if (not word.empty())
			wordCounts[word]++;
	}
	cout << "Finished reading input in." << endl;
	parse.close();
	///////

	// PRINTING REVERSE-ALPHABETICAL LIST OF WORD COUNTS
	/////// Reverse iterating over the already sorted tree is O(n)
	map<const string, int>::reverse_iterator it; // Iterator over map
	for (it=wordCounts.rbegin(); it != wordCounts.rend(); ++it) 
		cout << it->first << " : " << it->second << endl;
	///////
	cout << "Number of entries in list: " << wordCounts.size() << endl;

	return 0;
}