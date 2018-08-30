#ifndef COMPILER_H
#define COMPILER_H
#include "datastructure.h"
#include "server.h"

#define MAX_TOKEN_COUNT 100

void tokenizer(Ds_string* ds_string);
void parser();

#endif