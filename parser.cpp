#include "parser.h"
#include <iostream>
using namespace std;

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