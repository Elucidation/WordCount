#include <iostream>
using namespace std;

// Constants used by HashMap
#define TABLE_START_SIZE 1024 // Has been tested and should work with any integer size >0 
#define LOAD_FACTOR 0.5 // ratio of entries to table max_size at which to resize
#define TABLE_RESIZE_FACTOR 10 // factor to multiple original table size when resizing
#define FNV_PRIME 16777619u // used by Fowler–Noll–Vo string hash function


class HashEntry {
private:
	string key;
	long value;

public:
	HashEntry() {};
	HashEntry(string key, long value);
	
	string getKey();
	long getValue();
	void increment(); // increments value by 1

};

/* Hash Table implementation with collisions solved by open addressing (linear probing) 
   O(1) I/O
*/
class HashMap {
private:
	HashEntry **table; // Pointer to head of array of pointers to entries (key-value pairs)
	long size, max_size; // # of table entries, max possible table entries currently available
	float loadfactor; // ratio of size/max_size at which to double table

	void insert(long index, string key, long value); // table insert routine updates size
	long stringHash(string key); // hashes input key string
	void resize(); // doubles table when loadfacter exceeds
	long getTableHash(string key); // Get's actual table index for key or next open spot

public:
	HashMap();
	~HashMap();

	long get(string key);
	void put(string key, long value);
	void increment(string key); // Increment value by 1 or init to 1 if non-existent
	long getLength() {return size;};

	// Table iterator
	typedef HashEntry ** iterator;
	iterator begin() {return &table[0];};
	iterator end() {return &table[max_size];};
};