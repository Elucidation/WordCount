Unique Word Count in Reverse Alphabetical order
===
Sameer Ansari

Parses a text file, reads out the words (characters separated by whitespace) and prints a word -> count list in reverse alphabetical order. Uses std::str and std::unordered_map.

* Parsing done using character-based file input stream		O(n)
* Word count stored using hash map via std::unordered_map	O(n)*(1)
* Reverse-alphabetical order is done using quicksort		O(nlogn), worst O(n^2)

Other O(n) for iteration over words & hash map, size etc.
Total big O : O(nlogn) due to quicksort.

Building
---
To build:

	make

Usage
---
To run with a test input file `TEST_INPUT`: 

Linux `wordcount TEST_INPUT` , Windows `wordcount.exe TEST_INPUT`

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


To run all tests in `Tests` folder:

Linux `./runTests` , Windows `bash runTests`

Big-O runtime
---
Hash table is unordered_map which has constant time O(1) I/O. Then, to fill the map with a file of n words is O(n).
It uses a linked list in each bucket where keys are sorted by hash value.

The only disadvantage is the hash table is not in order (ordered by hash buckets). 

To sort the hash table, quick sort is chosen because it tends to be faster than mergesort and it's worst case possibility of O(n^2) with a reverse ordered list is highly unlikely. Memory used is O(n).

Quicksort's worst case (reverse order) is highly unlikely with hashing average words of a text file.


Testing strategy
---
The limiting factors are the cin stream to string buffer limits, the map resizing max limits, and through it all, the memory allocation limits. Stress test A deals with map size, Stress test B deals with string, as well as a basic test case and real world example.

* Passing in nonsensical files (example an binary exe file)

* Small test file :    < 1MB    (Lorem ipsum)

* Test files with known output:
	* t0_empty       =  empty file via saving empty txt file
	* t1_reallyempty =  empty file via touch cmd
	* t2_small       =  basic test of known words resulting in expected output
	* t3_delimit     =  tests the delimitters in the parser

* Real-world example (t5_sherlock) :  < 1MB    (Entire 'The Adventures of Sherlock Holmes' book as text file)

* Stress test A (t6_stessA) :      > 14.5 MB  (file containing increasing integers from 0 up)
	* 1 char = 1 byte, 5 MB = 5e6 chars, so lets choose 2e6 integers with a space after each for >> 10MB file, One line.
	* There are n=2e6 = 2 million words in file on one line, so map will need to have 2 million unique nodes
	* limit is allocation of words string array, which has a check on whether allocation succeeded

* Stress test B (t7_stressB) :      > 285 MB (2**30 > 1 billion character word input was max_size() )
	* Test with 285 MB file containing roughly 298,844,160 characters (all letter 'a')
	* Since it's 285MB I didn't attach it in zip, a large ascii file can replace this test


All cases passed, for nonsensical file, binary data was converted to ascii chars on the fly by cin to string, which resulted in non-visual characters like the bell character (computer beep), however code completes, if binary null-byte encountered will end on that. 

For Stress test B, string allocation continues to work, a try/except may need to still be added for an exception raised when string.max_size() is broken, though I need to learn more about what sort of input this program expects, as that's pretty unusual in normal text files, and for a 285MB file of one word, string continues to work.


Assumptions made
---
* Assumes input is well-formed text file containing ascii characters and a terminating null-byte at file end.
* Assumes only letters and digits (a-z A-Z 0-9) are part of words, if non letter-digit comes after letter-digit that acts as delimitter also, otherwise those are skipped till first valid character.

* Assumes case of a word is not important (stores all words as lower-case for simpler alphabetical comparison)
* Assumes digits come before letters alphabetically
* Assumes a single word will fit within limits of string.max_size() (string auto-alloc limited)
* Assumes memory available via allocation can contain all unique words in input text file.
* When printing out each word to screen, only prints first N characters (#define for pretty printing), though it can hold/print as many as the allocated string is capable of.