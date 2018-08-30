#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

char* tokens[MAX_TOKEN_COUNT] = {0};

void tokenizer(Ds_string* ds_string) {
	printf("%s\n", ds_string -> buf);
	char* buf = ds_string -> buf;
	int token_count = 0;
	char* temp = strtok(buf, " ");
	tokens[token_count++] = temp;
	while (temp != NULL) {
		printf("%s\n", temp);
		temp = strtok(NULL, " ");
		tokens[token_count++] = temp;
	}
}

void parser() {

}