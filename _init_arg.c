#include "monty.h"

/**
 * init_arg - Initializes the argument structure.
 */

void init_arg(void)
{
	argument->instruction = malloc(sizeof(instruction_t));
	if (argument->instruction == NULL)
		malloc_failed();

	argument->stackHead = NULL;
	argument->line = NULL;

	argument->n_tokens = 0;
	argument->isComment = 0;
	argument->line_number = 0;
	argument->stack = 1;
	argument->stack_length = 0;
	argument->stream = NULL;
}

/**
 * check_num_of_arguments - Checks the number of command-line arguments.
 * @argc: The number of command-line arguments.
 */

void check_num_of_arguments(int argc)
{
	if (argc == 2)
		return;

	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}

/**
 * read_failed - Handles the error when reading a file fails.
 * @fileName: The name of the file that failed to open.
 */

void read_failed(char *fileName)
{
	fprintf(stderr, "Error: Can't open file %s\n", fileName);
	free_arg();
	exit(EXIT_FAILURE);
}


/**
 * malloc_failed - Handles the error when malloc fails to allocate memory.
 */

void malloc_failed(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	free_arg();
	exit(EXIT_FAILURE);
}
