#include "hashmap.h"
using namespace std;

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
	if(!table) {
		cerr << "ERROR: Failed to allocate new table of size " << max_size << endl;
		max_size = 0;
		return;
	}
	for (int i = 0; i < TABLE_START_SIZE; ++i)
		table[i] = NULL;
	max_size = TABLE_START_SIZE; // Initial availabe space in table
	size = 0; // Number of entries (empty table start)
	loadfactor = LOAD_FACTOR; // ratio at which to resize table
}

HashMap::~HashMap() { 
	for (int i = 0; i < max_size; ++i)
		if (table[i])
			delete table[i];
	delete[] table; 
}

// Returns -1 if didn't find key
long HashMap::get(string key) {
	long hval = getTableHash(key);
	// cerr << "Get key " << key << "(" << hval << ")" << endl;
	if (!table[hval])
		return -1;

	return table[hval]->getValue();
}

void HashMap::put(string key, long value) {
	if (float(size)/max_size >= loadfactor)
		resize(); // If hash table is getting full, resize it
	insert(getTableHash(key),key,value);
}

 /* Private helper, puts new HashEntry(key,value) into table[index]
    Assumes caller checked table[index] is empty */
void HashMap::insert(long index, string key, long value) {
	// cerr << "Inserting entry ("<<key<<","<<value<<") in bucket (" << index << ")... " << endl;
	table[index] = new HashEntry(key,value);
	if(!table[index]) {
		cerr << "ERROR: Failed to allocate space for new HashEntry." << endl;
		return;
	}
	size++; // keep track of # entries in table
}

void HashMap::increment(string key) {
	if (float(size)/max_size >= loadfactor)
		resize();
	long hval = getTableHash(key);
	// cerr << "Inc: " << key << "(" << hval << ")... " << endl;
	if (not table[hval])
		insert(hval,key,1);
	else 
		table[hval]->increment();
}

/* uses hval = stringHash(key), and then iterates through hval till table[hval]'s 
   key matches key given or next open spot.
   Assumes table is not full due to resize() calls on inserts, else inf loop could happen */
long HashMap::getTableHash(string key) {
	long hval = stringHash(key);
	while (table[hval] && table[hval]->getKey() != key) {
		hval = (hval + 1) % max_size;
	}
	return hval; // can b
}

// Helper function for getTableHash, contains the hash function for a string only, no bucketskipping
long HashMap::stringHash(string key) {
	// Uses Fowler–Noll–Vo hash function from wikipedia
	unsigned long hash = 2166136261u;
	for (unsigned int i = 0; i < key.size(); ++i)
		hash = (hash ^ key[i]) * FNV_PRIME;

	return hash % max_size;
}


void HashMap::resize() {
	// cerr << "Load: " << size << "/" << max_size << "=" << float(size)/max_size << " > " << loadfactor << ". ";
	// cerr << "Resizing table from " << max_size << " to " << max_size*TABLE_RESIZE_FACTOR << "...";
	HashEntry **oldtable = table;
	long old_max_size = max_size;
	
	max_size *= TABLE_RESIZE_FACTOR;
	table = new HashEntry*[max_size];
	if(!table) {
		cerr << "ERROR: Failed to allocate new table of size " << max_size << endl;
		table = oldtable;
		return;
	}

	for (int i = 0; i < max_size; ++i) table[i] = NULL;

	// Copy pointers to entries into new table with new hashed position
	for (int i = 0; i < old_max_size; ++i)
		if (oldtable[i])
			table[getTableHash(oldtable[i]->getKey())] = oldtable[i];

	delete[] oldtable; // Don't need to delete individual entries since pointers passed to new table
	
	// cerr << "Successful." << endl;
}