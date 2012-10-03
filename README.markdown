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
* Passing in nonsensical files (example an binary exe file)
* Small test file < 1MB (Lorem ipsum)
* Real-world example < 1MB (Entire 'The Adventures of Sherlock Holmes' book as text file)
* Stress test > 10 MB file size (file containing increasing integers from 0 up)
   1 char = 1 byte, 5 MB = 5e6 chars, so lets choose 2e6 integers with a space after each for >> 10MB file
   All on one line, file size is ~14.5 MB
   There are n=2e6 = 2 million words in file on one line, so map will need to have 2 million unique nodes

All cases passed, for nonsensical file, binary data was converted to ascii chars on the fly by cin to string, which resulted in non-visual characters like the bell character (computer beep), however code completes.


Assumptions made
---
* Assumes input is well-formed text file containing ascii characters and a file end character (say \0).
* Assumes a single word will fit within limits of string.max_size() 
