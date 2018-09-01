#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "compiler.h"

char* tokens[MAX_TOKEN_COUNT] = {0};

// Return -1 if there are lexical errors and return the number of tokens if not.
int tokenizer(Ds_string* ds_string) {

	if (ds_string -> length == 0) {
		printf("The length of ds_string is 0!\n");
		return -1;
	}

	int token_count = 0;
	printf("%s\n", ds_string -> buf);
	char* buf = ds_string -> buf;
	char* temp = strtok(buf, " ");
	while (temp != NULL) {

		/*
			First, see if the token is a keyword.
			Currently, the keyword "set", "get", 
			"update" and "delete" are supported.
		*/ 
		if (strcmp(temp, "set") == 0 || 
			strcmp(temp, "get") == 0 ||
			strcmp(temp, "update") == 0 ||
			strcmp(temp, "delete") == 0) 
		{
			tokens[token_count++] = temp;
			temp = strtok(NULL, " ");
			continue;
		}

		/* 
			Second, if this token is not a keyword, 
			check if the current token is made 
			up with only alphabets, that is a-zA-Z
			Here, we use the regular expression to do this.
		*/
		regex_t reg;
		regmatch_t pmatch;
		char* pattern = "^[a-zA-Z]+[a-zA-Z]*$";
		if(regcomp(&reg, pattern, REG_EXTENDED) < 0) {
			printf("regcomp error!\n");
		}
		int status = regexec(&reg, temp, 1, &pmatch, 0);
		if (status == REG_NOMATCH) {
			printf("No match!\n");
			token_count = -1;
			break;
		} else {
			printf("match!\n");
			tokens[token_count++] = temp;
		}
		temp = strtok(NULL, " ");
		regfree(&reg);
	}
	return token_count;
}

void parser(int num_tokens) {
	/*
		Currently, there are four types of commands
		The bnf of the grammar are as follows:
	*/
	if (strcmp(tokens[0], "set") == 0) {
	}
}

void reset_tokens() {
	for (int i = 0; i < MAX_TOKEN_COUNT; i++) {
		tokens[i] = 0;
	}
}