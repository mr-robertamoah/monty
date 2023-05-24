#include "monty.h"

FILE *fdopen(int fd, const char *mode);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

void free_argument_t(argument *arg)
{
	if (arg->instruction != NULL)
		free(arg->instruction);

	free(arg);
}

void invalid_instruction(argument_t *arg)
{
	fprintf(stderr, "L%ld: unknown instruction %s\n",
		arg->line_number, arg->line_strs[0]);
	free_argument_t(arg);
	exit(EXIT_FAILURE);
}

void read_failed(char *fileName)
{
	fprintf(stderr, "Error: Can't open file %s\n", fileName);
	exit(EXIT_FAILURE);
}

void malloc_failed()
{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}

FILE *getStream(char *fileName)
{
	int fd;
	FILE *stream = NULL;

	fd = open(fileName, O_RDONLY);
	if (fd == -1)
		read_failed(fileName);

	stream = fdopen(fd, "r");
	if (stream == NULL)
		read_failed(fileName);

	return (stream);
}

void tokenize(char *line, argument_t *arg)
{
	int n_tokens = 0, i = 0;
	char *delims = " \n", *token = NULL, *linecpy = NULL;

	linecpy = malloc(sizeof(char) * (strlen(line) + 1));
	strcpy(linecpy, line);
	token = strtok(linecpy, delims);
	while (token)
	{
		n_tokens++;
		token = strtok(NULL, delims);
	}

	argument->n_tokens = n_tokens;

	arg->line_strs = malloc(sizeof(char *) * (n_tokens + 1));
	strcpy(linecpy, line);
	token = strtok(linecpy, delims);
	while (token)
	{
		arg->line_strs[i] = malloc(sizeof(char) * (strlen(token) + 1));
		if (arg->line_strs[i] == NULL)
			malloc_failed();
		strcpy(arg->line_strs[i], token);
		token = strtok(NULL, delims);
		i++;
	}
	arg->line_strs[i] = NULL;
	free(linecpy);
}

void run_instruction(argument_t *arg)
{
	// TODO complete this function
}

void get_instruction(argument_t *arg)
{
	int i = 0;

	if (arg->n_tokens == 0) /* no instructions */
		return;

	for (; arg->instructions[i]; i++)
	{
		/* compare opcode of instruction to first token (instruction) */
		if (strcmp(arg->instructions[i].opcode, arg->line_strs[0]) == 0)
		{
			arg->instruction = arg->instructions[i];
			return;
		}
	}

	invalid_instruction(arg);
}

void init_arg(argument_t *arg)
{
	instruction_t instructions[] = {
		{"push", push}, {"pop", pop}, {"pint", pint},
		{"swap", swap},	{"nop", nop}, {"add", add}, NULL
	};

	argument->instructions = instructions;
	arg->instruction = malloc(sizeof(instruction_t));
	if (arg->instruction == NULL)
		malloc_failed();
}

/**
 * main - Entry point
 *
 * Description: print alphabets in lowercase using the putchar
 *
 * Return: returns 0 (Success)
 */
int main(int argc, char **argv)
{
	ssize_t lines_read = 0;
	size_t n = 0, line_num = 0;
	char *line = NULL;
	FILE *stream = NULL;
	argument_t *argument = NULL;

	(void)argv;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	argument = malloc(sizeof(argument_t));
	if (argument == NULL)
		malloc_failed();
	init_arg(argument);
	stream = getStream(argv[1]);

	while ((lines_read = getline(&line, &n, stream)) != -1)
	{
		line_num++;
		tokenize(line, argument);
		argument->line_number = line_num;
		get_instruction(argument);
		run_instruction(argument);
		n = 0;
		while (argument->line_strs[n]) {
			n++;
		}
	}

	free(line);
	free(argument);
	return (0);
}
