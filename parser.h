#ifndef _PARSER_H
#define _PARSER_H

#include <fstream>
using namespace std;

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
#endif