#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"

Ds_string* Ds_string_new(char* string) {
	Ds_string* ds_string = malloc(sizeof(Ds_string));
	ds_string -> length = strlen(string);
	ds_string -> buf = string;
	return ds_string;
}

Ds_object* Ds_object_new(int ds_type, void* data) {
	Ds_object* ds_object = malloc(sizeof(Ds_object));
	ds_object -> ds_type = ds_type;
	ds_object -> data = data;
	return ds_object;
}

Dictionary* Dictionary_new(int table_size) {
	Dictionary* dictionary = malloc(sizeof(Dictionary));
	Dict_hashtable* hashtable = malloc(sizeof(Dict_hashtable));

	// Initialize the table of pointer of Dict_entry
	Dict_entry** table = malloc(sizeof(Dict_entry*) * table_size);
	for (int i = 0; i < table_size; i++) {
		table[i] = NULL;
	}

	// Initialize the hashtable
	hashtable -> table_size = table_size;
	hashtable -> table = table;

	// Initialize the dictionary
	dictionary -> hashtable = hashtable;

	return dictionary;
}

int Dictionary_add(Dictionary* dictionary, Ds_object* key, Ds_object* value) {
	return 0;
}

Ds_object* Dictionary_get(Dictionary* dictionary, Ds_object* key) {

	if (dictionary == NULL) {
		printf("The dictionary is not existed!\n");
		return NULL;
	}
	int table_size = dictionary -> hashtable -> table_size;

	// Calculate the hash value according to the key.
	int hashval = 0;
	int type = key -> ds_type;
	if (type == DS_STRING) {
		Ds_string* ds_string = (Ds_string*) key -> data;
		hashval = simpleHash(ds_string -> buf, ds_string -> length, table_size);
		// TODO: find the value in the hash table
	}
	return NULL;

}

int simpleHash(char* string, int slength, int table_size) {

	int result = 0;
	for (int i = 0; i < slength; i++) {
		result = result + string[i];
	}
	return result % table_size;

}