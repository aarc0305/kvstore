#ifndef COMPILER_H
#define COMPILER_H
#include "datastructure.h"
#include "server.h"

#define MAX_TOKEN_COUNT 100

typedef enum Token_type {
	TOKEN_SET,
	TOKEN_GET,
	TOKEN_UPDATE,
	TOKEN_DELETE,
	TOKEN_VARIABLE
} Token_type;

typedef struct Token Token;
struct Token {
	Token_type type;
	char* value;
};

int tokenizer(Ds_string* ds_string);
int parser(Client* client);
Token* token_new(char* value, Token_type type);

#endif