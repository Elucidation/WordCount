Unique Word Count in Reverse Alphabetical order [![Build Status](https://travis-ci.org/Elucidation/WordCount.svg?branch=master)](https://travis-ci.org/Elucidation/WordCount)
===
Sameer Ansari

Parses a text file, reads out the words (characters separated by whitespace) and prints a word -> count list in reverse alphabetical order. Uses std::str.

* Parsing done using character-based file input stream		, O(n)
* Word count stored in a custom hash map w/ linear probing	, O(n)*O(1) with good load factor
* Reverse-alphabetical order is done using quicksort		, O(nlogn), worst O(n^2)

Other O(n) for iteration over words & hash map, size etc.
Total big O : O(nlogn) due to quicksort.

Has been tested with all tests in Tests folder as well as two stress tests not included.

Files
---
* `wordcount.cpp`   = Main class wrapper to determine list of reverse alphabetically ordered word counts
* `makefile`        = Makefile for building
* `parser.cpp/h`    = Class to open & parse a file for words
* `hashmap.cpp/h`   = Class for hash map implementation
* `sorter.cpp/h`    = Class to apply quicksort to string array of words
* `tests/`          = Folder containing test input text files and correct expected outputs
* ~~`runTests`      = shell script to run all tests in `\Tests` directory~~ *(Not used anymore)*


Building & Testing
---
To build:

	make

To test:

	make test

Usage
---
To run with a test input file `TEST_INPUT`: 

Linux `wordcount TEST_INPUT`, Windows `wordcount.exe TEST_INPUT`

Example:
	
	wordcount.exe Tests/t0_small.txt

where `t0_small.txt` is:

	This is n0t the 1st test

Output:

	Loading Tests/t2_small.txt...Successful.
	Parsing input file 'Tests/t2_small.txt' to map...Successful.
	Generating word list for sorting...Successful.
	Sorting word list...Successful.
	this -> 1
	the -> 1
	test -> 1
	n0t -> 1
	is -> 1
	1st -> 1
	Number of entries in list: 6


Big O Rruntime
---
Parsing is done via ifstream one character at a time, it is O(n) to get every character in file up to null-byte.

The Hash table is implemented using open addressing for collision resolution (linear probing). The Load factor is set to 0.5 for resizing of the array, which in tests keeps the collisions reasonably low.

Input & Output to the Hash table is constant time O(1) I/O with worst case O(n) with a full table (which load factor avoids). Then, to fill the map with a file of n words is O(n).

One disadvantage is the hash table is not in order (hash function decides slot).

To sort the hash table, quick sort is chosen because it tends to be faster than mergesort and it's worst case possibility of O(n^2) with a reverse ordered list is highly unlikely. Memory used is O(n).

Quicksort's worst case (reverse order) is highly unlikely with hashing average words of a text file.

Combining all of these, the worst case is O(n^2) due to either the hash table getting too many collisions and filled up (load factor stops that), or quicksort on a reverse ordered list of words happens (improbable). On average and best case is O(nlogn) which is limited by quicksort.

Testing strategy
---
The limiting factors are the cin stream to string buffer limits, the map resizing max limits, and through it all, the memory allocation limits. Stress test A tests map size up to 2 million unique entries, Stress test B deals with string, as well as a basic test case and real world example.

* Passing in nonsensical files (example an binary exe file)

* Small test file :    < 1MB    (Lorem ipsum)

* Test files with known output:
	* t0_empty       =  empty file via saving empty txt file
	* t1_reallyempty =  empty file via touch cmd
	* t2_small       =  basic test of known words resulting in expected output
	* t3_delimit     =  tests the delimitters in the parser
	* t4_basic       =  lorem ipsum set of generated paragraphs

* Real-world example (t5_sherlock) :  < 1MB    (Entire 'The Adventures of Sherlock Holmes' book as text file)

Following files are not attached, but their truncated outputs are:

* Stress test A (t6_stessA) :      > 14.5 MB  (file containing increasing integers from 0 up)
	* 1 char = 1 byte, 5 MB = 5e6 chars, so lets choose 2e6 integers with a space after each for >> 10MB file, One line.
	* There are n=2e6 = 2 million words in file on one line, so hash table will need to have 2 million unique entries
	* limit is allocation of words string array, which has a check on whether allocation succeeded

* Stress test B (t7_stressB) :      > 285 MB (2**30 > 1 billion character word input was max_size() )
	* Test with 285 MB file containing roughly 298,844,160 characters (all letter 'a')


All cases passed, for nonsensical files, binary data is converted to ascii chars on the fly and only those that were considered valid chars were used.

For Stress test B, string allocation continues to work, a try/except may need to still be added for an exception raised when string.max_size() is broken, though I need to learn more about what sort of input this program expects, as that's pretty unusual in normal text files, and for a 285MB file of one word, string continues to work. Implementing that may be overkill.


Assumptions made
---
* Assumes input is well-formed text file containing ascii characters and a terminating null-byte at file end.
* Assumes only letters and digits (a-z A-Z 0-9) are part of words, if non letter-digit comes after letter-digit that acts as delimitter also, otherwise those are skipped till first valid character.

* Assumes case of a word is not important (stores all words as lower-case for simpler alphabetical comparison)
* Assumes digits come before letters alphabetically
* Assumes a single word will fit within limits of string.max_size() (string auto-alloc limited)
* Assumes memory available via allocation can contain all unique words in input text file.
* When printing out each word to screen, only prints first N characters (#define for pretty printing), though it can hold/print as many as the allocated string is capable of.