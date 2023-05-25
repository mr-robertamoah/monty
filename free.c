#include "monty.h"

/**
 * free_all_args - Frees all allocated memory for arguments.
 */

void free_all_args(void)
{
	closeStream();
	free_toks();
	free_arg();
}

/**
 * free_toks - Frees the allocated memory for tokens.
 */

void free_toks(void)
{
	int i = 0;

	if (argument->line_strs)
	{
		while (argument->line_strs[i])
		{
			free(argument->line_strs[i]);
			i++;
		}
		free(argument->line_strs);
	}
}

/**
 * free_stackHead - Frees the memory allocated for the stackHead and
 * sets it to NULL.
 */

void free_stackHead(void)
{
	if (argument->stackHead)
		free_stack(argument->stackHead);

	argument->stackHead = NULL;
}

/**
 * closeStream - Closes the file stream and sets it to NULL.
 */

void closeStream(void)
{
	if (argument->stream)
	{
		fclose(argument->stream);
		argument->stream = NULL;
	}
}

/**
 * free_arg - Frees the memory allocated for the argument
 * structure and its members.
 */

void free_arg(void)
{
	if (argument == NULL)
		return;

	if (argument->instruction)
	{
		free(argument->instruction);
		argument->instruction = NULL;
	}

	free_stackHead();

	if (argument->line)
	{
		free(argument->line);
		argument->line = NULL;
	}

	free(argument);
}
