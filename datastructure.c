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
	ds_object -> ds_type;
	ds_object -> data;
	return ds_object;
}