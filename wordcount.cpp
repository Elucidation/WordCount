#include <iostream>
#include <map>
#include <fstream>
using namespace std;
#define BUFFER_SIZE 1024 // Size of char buffer for a token


/*
Draft 1, basic working example without safety-checks
STD usage: Uses std::cin, std::str, and std::map

To build on linux systems: make
To run with a test input file TEST_INPUT: wordcount.exe < TEST_INPUT

*/
class Parser
{
public:
	Parser(const char *filename);
	~Parser();

	void close();
	bool eof(); // bool at end of file or not
	string next(); // next string token

private:
	bool isValidChar(char c); // Is Letter or Number, whatever we deem valid
	ifstream f; // file input stream

};

Parser::Parser(const char* filename) {
	cout << "Loading " << filename << "...";
	f.open(filename);
	if (not f.is_open()) {
		cout << "ERROR: Could not open file '" << filename << "'." << endl;
	}
	else
		cout << "Successful." << endl;
}

Parser::~Parser() {
	close();
}
void Parser::close() {
	if (f && f.is_open())
		f.close();
}
bool Parser::eof() {
	return f.eof();
}
string Parser::next() {
	string token = "";
	char k;
	while (f.good()){
		f.get(k);
		if (k == '\n' or k == ' ')
			break;
		else if (isValidChar(k))
			token += k;
	}
	return token;
}

bool Parser::isValidChar(char c) {
	return (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57); // UPPER or LOWER or DIGIT
}

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