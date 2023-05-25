#include "monty.h"

argument_t *argument = NULL;

/**
 * main - Entry point
 * @argc: The number of command-line arguments.
 * @argv: A pointer to an array of strings containing
 * the command-line arguments.
 * Description: print alphabets in lowercase using the putchar
 *
 * Return: returns 0 (Success)
 */
int main(int argc, char **argv)
{
	ssize_t lines_read = 0;
	size_t n = 0;

	check_num_of_arguments(argc);

	argument = malloc(sizeof(argument_t));
	if (argument == NULL)
		malloc_failed();

	init_arg();
	setStream(argv[1]);

	while ((lines_read = getline(&argument->line, &n, argument->stream)) != -1)
	{
		argument->line_number += 1;
		tokenize();
		setInstruction();
		runInstruction();
		free_toks();
	}

	closeStream();
	free_arg();

	return (0);
}
