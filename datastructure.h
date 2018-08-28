#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#define DS_STRING 0

typedef struct Ds_string Ds_string;
struct Ds_string {
	int length;
	char* buf;
};

typedef struct Ds_object Ds_object;
struct Ds_object {
	int ds_type;
	void* data;
};

Ds_string* Ds_string_new(char* string);
Ds_object* Ds_object_new(int ds_type, void* data);

#endif