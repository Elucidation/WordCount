#include "hashmap.h"
using namespace std;

#define TABLE_START_SIZE 4
#define LOAD_FACTOR 0.75 // ratio of entries to table max_size at which to resize
#define TABLE_RESIZE_FACTOR 10 // factor to multiple original table size when resizing
#define FNV_PRIME 16777619u

// Hash Entry
HashEntry::HashEntry(string keyIn, long valueIn){
	key = keyIn;
	value = valueIn;
};

string HashEntry::getKey() {return key;}

long HashEntry::getValue() {return value;}
void HashEntry::increment() {value++;}


// Hash Map
HashMap::HashMap() {
	table = new HashEntry*[TABLE_START_SIZE];
	for (int i = 0; i < TABLE_START_SIZE; ++i)
		table[i] = NULL;
	max_size = TABLE_START_SIZE;
	size = 0;
	loadfactor = LOAD_FACTOR;
}

HashMap::~HashMap() { delete[] table; }

// Returns -1 if didn't find key
long HashMap::get(string key) {
	long hval = getTableHash(key);
	// cout << "Get key " << key << "(" << hval << ")" << endl;
	if (!table[hval])
		return -1;

	return table[hval]->getValue();
}

void HashMap::put(string key, long value) {
	// If hash table is getting full, resize it
	// cout << "Put ("<<key<<","<<value<<"), Load: " << size << "/" << max_size << "=" << float(size)/max_size << " vs. " << loadfactor << endl;
	if (float(size)/max_size >= loadfactor)
		resize();

	long hval = getTableHash(key);
	// cout << key << "(" << hval << ") : " << endl;

	table[hval] = new HashEntry(key,value);
	size++;

	return;
}

void HashMap::increment(string key) {
	if (float(size)/max_size >= loadfactor)
		resize();
	long hval = getTableHash(key);
	// cout << "Inc: " << key << "(" << hval << ")... " << endl;
	if (not table[hval]) {
		// cout << "Inserting entry ("<<key<<") in bucket (" << hval << ")... " << endl;
		table[hval] = new HashEntry(key,1);
		size++;
	}
	else {
		table[stringHash(key)]->increment();
	}
	return;
}

/* uses hval = stringHash(key), and then iterates through hval till table[hval]'s 
  key matches key given or next open spot*/
long HashMap::getTableHash(string key) {
	long hval = stringHash(key);
	// int i=0;
	while (table[hval] && table[hval]->getKey() != key) {
		// cout << "Searching for " << key << " past table[" << hval << "] = " << table[hval]->getKey() << endl;
		hval = (hval + 1) % max_size;
		// if (++i >= max_size)
		// 	return -1; // Table was full, didn't find it in entire table
	}
	return hval; // can b
}

// Helper function for getTableHash, contains the hash function for a string only, no bucketskipping
long HashMap::stringHash(string key) {
	// Uses basic Fowler–Noll–Vo hash function from wikipedia
	unsigned long hash = 2166136261u;
	for (unsigned int i = 0; i < key.size(); ++i)
		hash = (hash ^ key[i]) * FNV_PRIME;

	return hash % max_size;
}


void HashMap::resize() {
	// cout << "Load: " << size << "/" << max_size << "=" << float(size)/max_size << " > " << loadfactor << ". ";
	// cout << "Resizing table from " << max_size << " to " << max_size*TABLE_RESIZE_FACTOR << "...";
	HashEntry **oldtable = table;
	long old_max_size = max_size;
	
	max_size *= TABLE_RESIZE_FACTOR;
	table = new HashEntry*[max_size];
	for (int i = 0; i < max_size; ++i)
		table[i] = NULL;

	// Copy pointers to entries into new table with new hashed position
	for (int i = 0; i < old_max_size; ++i)
	{
		if (oldtable[i])
			table[getTableHash(oldtable[i]->getKey())] = oldtable[i];
	}
	delete[] oldtable; // Don't need to delete individual entries since pointers passed to new table
	
	// cout << "Successful." << endl;
}