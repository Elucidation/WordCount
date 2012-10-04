#include "hashmap.h"
using namespace std;

#define TABLE_START_SIZE 4
#define LOAD_FACTOR 0.75 // ratio of entries to table max_size at which to resize

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


long HashMap::stringHash(string key) {
	// long hval = 0;
	// for (int i = 0; key[i] != '\0'; ++i)
	// {
	// 	hval += (i << 3*i) * key[i];
	// }
	// return hval;
	return key.length() % max_size;
}

long HashMap::get(string key) {
	long hval = getTableHash(key);
	// cout << "Get key " << key << "(" << hval << ")" << endl;
	if (!table[hval])
		return -1;
	while (table[hval]->getKey() != key) {
		hval = (hval + 1) % max_size ;
		if (!table[hval])
			return -1;
	}
		
	// HashEntry entry = *table[hval];

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
	int i=0;
	while (table[hval] && table[hval]->getKey() != key) {
		// cout << "Searching for " << key << " past table[" << hval << "] = " << table[hval]->getKey() << endl;
		hval = (hval + 1) % max_size;
		if (++i >= max_size)
			return -1; // Table was full, didn't find it in entire table
	}
	return hval; // can b
}

void HashMap::resize() {
	// cout << "Resizing table from " << max_size << endl;
	HashEntry **oldtable = table;
	long old_max_size = max_size;
	
	max_size *= 2;
	table = new HashEntry*[max_size];
	for (int i = 0; i < max_size; ++i)
		table[i] = NULL;

	// Copy pointers to entries into new table with new hashed position
	for (int i = 0; i < old_max_size; ++i)
	{
		if (oldtable[i])
			table[stringHash(oldtable[i]->getKey())] = oldtable[i];
	}
	delete[] oldtable; // Don't need to delete individual entries since pointers passed to new table
}