#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "compiler.h"

Token* tokens[MAX_TOKEN_COUNT] = {NULL};

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
		if (strcmp(temp, "set") == 0) {
			tokens[token_count++] = token_new(temp, TOKEN_SET);
			temp = strtok(NULL, " ");
			continue;
		} else if (strcmp(temp, "get") == 0) {
			tokens[token_count++] = token_new(temp, TOKEN_GET);
			temp = strtok(NULL, " ");
			continue;
		} else if (strcmp(temp, "update") == 0) {
			tokens[token_count++] = token_new(temp, TOKEN_UPDATE);
			temp = strtok(NULL, " ");
			continue;
		} else if (strcmp(temp, "delete") == 0) {
			tokens[token_count++] = token_new(temp, TOKEN_DELETE);
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
			tokens[token_count++] = token_new(temp, TOKEN_VARIABLE);
		}
		temp = strtok(NULL, " ");
		regfree(&reg);
	}
	return token_count;
}

// Return -1 if there are syntax errors and return 0 if not.
int parser(Client* client) {
	/*
		Currently, there are four types of commands
		The bnf of the grammar is as follows:

		command: setCommand
		| getCommand
		| updateCommand
		| deleteCommand
		;

		setCommand: "set" key value;

		getCommand: "get" key;

		updateCommand: "update" key value;

		deleteCommand: "delete" key

		key: VARIABLE;

		value: VARIABLE;
	*/
	if (tokens[0] == NULL) {
		printf("Syntax error!\n");
		return -1;
	}

	if (tokens[0] -> type == TOKEN_SET || tokens[0] -> type == TOKEN_UPDATE) {
		if (tokens[1] == NULL || tokens[2] == NULL) {
			printf("Syntax error!\n");
			return -1;
		} else {
			if (tokens[1] -> type != TOKEN_VARIABLE || tokens[2] -> type != TOKEN_VARIABLE) {
				printf("Syntax error!\n");
				return -1;
			}
			/*
				When there are no syntax errors, store the command in the argv of the client.
				The number of the tokens in the set and update command is 3.
			*/ 
			client -> argc = 3;
			client -> argv = malloc(sizeof(char*) * client -> argc);
			for (int i = 0; i < client -> argc; i++) {
				(client -> argv)[i] = tokens[i] -> value;
			}
			return 0;
		}
	} else if (tokens[0] -> type == TOKEN_GET || tokens[0] -> type == TOKEN_DELETE) {
		if (tokens[1] == NULL || tokens[2] != NULL) {
			printf("Syntax error!\n");
			return -1;
		} else {
			if (tokens[1] -> type != TOKEN_VARIABLE) {
				printf("Syntax error!\n");
				return -1;
			}
			/* 
				When there are no syntax errors, store the command in the argv of the client.
				The number of the tokens in the get and delete is 2.
			*/
			client -> argc = 2;
			client -> argv = malloc(sizeof(char*) * client -> argc);
			for (int i = 0; i < client -> argc; i++) {
				(client -> argv)[i] = tokens[i] -> value;
			}
			return 0;
		}
	} else {
		printf("Syntax error!\n");
		return -1;
	}

}

void freeTokens() {
	for (int i = 0; i < MAX_TOKEN_COUNT; i++) {
		free(tokens[i]);
		tokens[i] = NULL;
	}
}

Token* token_new(char* value, Token_type type) {
	Token* token = malloc(sizeof(Token));
	token -> value = value;
	token -> type = type;
	return token;
}