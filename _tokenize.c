#include "monty.h"

/**
 * tokenize - Tokenizes the input line.
 */

void tokenize(void)
{
	int i = 0;
	char *delims = " \n", *token = NULL, *linecpy = NULL;

	linecpy = malloc(sizeof(char) * (strlen(argument->line) + 1));
	strcpy(linecpy, argument->line);
	argument->n_tokens = 0;
	token = strtok(linecpy, delims);
	while (token)
	{
		argument->n_tokens += 1;
		token = strtok(NULL, delims);
	}

	argument->line_strs = malloc(sizeof(char *) *
			(argument->n_tokens + 1));
	strcpy(linecpy, argument->line);
	token = strtok(linecpy, delims);
	while (token)
	{
		argument->line_strs[i] = malloc(sizeof(char) *
				(strlen(token) + 1));
		if (argument->line_strs[i] == NULL)
			malloc_failed();
		strcpy(argument->line_strs[i], token);
		token = strtok(NULL, delims);
		i++;
	}
	argument->line_strs[i] = NULL;
	free(linecpy);
}
