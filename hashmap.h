#include <iostream>
using namespace std;

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

class HashMap {
private:
	HashEntry **table; // Pointer to head of array of pointers to entries (key-value pairs)
	long size, max_size; // # of table entries, max possible table entries currently available
	float loadfactor; // ratio of size/max_size at which to double table

	// Simple iterator implement for getting all table entries
	int iteri;

public:
	HashMap();
	~HashMap();

	long get(string key);
	void put(string key, long value);
	void increment(string key); // Increment value by 1 or init to 1
	long getLength() {return size;};
	long stringHash(string key); // hashes input key string
	long getTableHash(string key); // Get's actual table index for key or next open spot
	void resize(); // doubles table when loadfacter exceeds

	typedef HashEntry ** iterator;
	iterator begin() {return &table[0];};
	iterator end() {return &table[max_size-1];};
};