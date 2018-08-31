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

// Return -1 if two objects are not equal and return 0 if two objects are the same.
int compareObject(Ds_object* this_object, Ds_object* that_object) {

	int this_type = this_object -> ds_type;
	int that_type = that_object -> ds_type;
	if (this_type != that_type) {
		return -1;
	}
	if (this_type == DS_STRING) {
		Ds_string* this_ds_string = (Ds_string*)(this_object -> data);
		Ds_string* that_ds_string = (Ds_string*)(that_object -> data);
		char* this_string = this_ds_string -> buf;
		char* that_string = that_ds_string -> buf;
		if (strcmp(this_string, that_string) == 0) {
			return 0;
		} else {
			return -1;
		}
	}
	return -1;

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


// Return 0 if successful and return -1 if not.
int Dictionary_add(Dictionary* dictionary, Ds_object* key, Ds_object* value) {

	if (dictionary == NULL) {
		printf("The dictionary is not existed!\n");
		return -1;
	}

	int table_size = dictionary -> hashtable -> table_size;
	int type = key -> ds_type;
	int hashval = 0;
	if (type == DS_STRING) {
		Ds_string* key_ds_string = (Ds_string*) (key -> data);
		hashval = simpleHash(key_ds_string -> buf, key_ds_string -> length, table_size);
		if ((dictionary -> hashtable -> table)[hashval] == NULL) {
			// If there are no entries in the index, just input it.
			(dictionary -> hashtable -> table)[hashval] = malloc(sizeof(Dict_entry));
			(dictionary -> hashtable -> table)[hashval] -> key = key;
			(dictionary -> hashtable -> table)[hashval] -> value = value;
			(dictionary -> hashtable -> table)[hashval] -> next = NULL;
		} else {
			Dict_entry* target = (dictionary -> hashtable -> table)[hashval];
			Dict_entry* last_target = NULL;
			while (target != NULL) {
				/*
					Compare with the input key. 
					If the target and the input key are the same, 
					replace the value with the new one and return 0.
					Otherwise, look for the next target.
				*/ 
				if (compareObject(target -> key, key) == 0) {
					target -> value = value;
					return 0;
				} else {
					last_target = target;
					target = target -> next;
				}
			}
			last_target -> next = malloc(sizeof(Dict_entry));
			last_target -> next -> key = key;
			last_target -> next -> value = value;
			last_target -> next -> next = NULL;
		}

	}
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
		/*
			If the key is a ds_string, use the hash function and the
			string stored in the ds_string to calculate the hash value.
			Then, use this value as an index to get value in the table.
			An index may include several keys, therefore, we must scan 
			all of the keys in this index.
		*/
		Ds_string* ds_string = (Ds_string*) key -> data;
		hashval = simpleHash(ds_string -> buf, ds_string -> length, table_size);
		Dict_entry* target = (dictionary -> hashtable -> table)[hashval];
		if (target == NULL) {
			printf("The key is not found in this table!");
			return NULL;
		}
		// Scan all the keys in this index.
		while (target != NULL) {
			if (compareObject(target -> key, key) == 0) {
				// Get the key, therefore, return the corresponding value.
				return target -> value;
			}
			target = target -> next;
		}
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
