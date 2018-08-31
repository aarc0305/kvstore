#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#define DS_STRING 0

typedef struct Ds_string Ds_string;
typedef struct Ds_object Ds_object;

/* Structure related to dictionary
	1. Dict_entry
	2. Dict_hashtable
	3. Dictionary
*/
typedef struct Dict_entry Dict_entry;
typedef struct Dict_hashtable Dict_hashtable;
typedef struct Dictionary Dictionary;

struct Ds_string {
	int length;
	char* buf;
};

struct Ds_object {
	int ds_type;
	void* data;
};

struct Dict_entry {
	Ds_object* key;
	Ds_object* value;
	Dict_entry* next;
};

struct Dict_hashtable {
	int table_size;
	Dict_entry** table;
};

struct Dictionary {
	Dict_hashtable* hashtable;
};

Ds_string* Ds_string_new(char* string);
Ds_object* Ds_object_new(int ds_type, void* data);
int compareObject(Ds_object* this_object, Ds_object* that_object);

Dictionary* Dictionary_new(int table_size);
int Dictionary_add(Dictionary* dictionary, Ds_object* key, Ds_object* value);
Ds_object* Dictionary_get(Dictionary* dictionary, Ds_object* key);


// Set of hash functions
int simpleHash(char* string, int slength, int table_size);

#endif