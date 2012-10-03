Unique Word Count in Reverse Alphabetical order
===
Sameer Ansari

Parses a text file, reads out the words (characters separated by whitespace) and prints a word -> count list in reverse alphabetical order. Uses std::cin, std::str, and std::map for a total big O of O(nlogn).

Building
---
To build:

	make


Usage
---
To run with a test input file `TEST_INPUT`: 
	
	wordcount.exe < TEST_INPUT

Example:
	
	wordcount.exe < test.txt

Big-O runtime
---
Standard map is a Red-black tree with keys as string and integer count for times word encountered.
Input/Output to the map will be O(log n), since it's a self-balancing binary tree, with memory of O(n)

To fill the map with a file of n words is O(nlogn).

The advantage of an RB tree is the nodes being pre-sorted on input by key, which is a string comparison which is alphabetical
So a reverse iterator over the tree in-order returns a reverse alphabetical list of words in O(n) time.

Since I'll probably be replacing the stl with custom functions, I'd prefer to use a hash map (such as stl unordered_map)
Since I/O will be O(1), then using a sort routine that is suited to task to order the keys, this will be the longest op.

If we have stack space & memory, mergesort for O(nlogn) with O(n) memory/stack space
If we don't want to use much memory, in place quicksort which at best can do O(nlogn) with O(log n) stack space needed (probably O(n) space though)
	This isn't a bad option since the worst case (reverse order) is highly unlikely with hashing average words of a text file


Testing strategy
---
The limiting factors are the cin stream to string buffer limits, the map resizing max limits, and through it all, the memory allocation limits. Stress test A deals with map size, Stress test B deals with string, as well as a basic test case and real world example.

* Passing in nonsensical files (example an binary exe file)

* Small test file :    < 1MB    (Lorem ipsum)

* Stress test A :      > 14.5 MB  (file containing increasing integers from 0 up)
	* 1 char = 1 byte, 5 MB = 5e6 chars, so lets choose 2e6 integers with a space after each for >> 10MB file, One line.
	* There are n=2e6 = 2 million words in file on one line, so map will need to have 2 million unique nodes

* Stress test B :      > 285 MB (2**30 > 1 billion character word input was max_size() )
	* Test with 285 MB file containing roughly 298,844,160 characters (all letter 'a')

* Real-world example:  < 1MB    (Entire 'The Adventures of Sherlock Holmes' book as text file)

All cases passed, for nonsensical file, binary data was converted to ascii chars on the fly by cin to string, which resulted in non-visual characters like the bell character (computer beep), however code completes. For Stress test B, string allocation continues to work, a try/except needs to still be added for a exception raised when string.max_size() is broken, though I need to learn more about what sort of input this program expects, as that's pretty unusual in normal text files, and for a 285MB file of one word, string continues to work.


Assumptions made
---
* Assumes input is well-formed text file containing ascii characters and a file end character (say \0).
* Assumes a single word will fit within limits of string.max_size() (string auto-alloc limited)
* Assumes all characters are important to a word, including quotations periods, commas etc., Only spaces delimit words, and no characters are ignored.
* Assumes memory available via allocation can contain all unique words in input text file.
