#include "monty.h"
#include <fcntl.h>

/**
 * runInstruction - Runs the instruction specified by the argument.
 */

void runInstruction(void)
{
	stack_t *stack = NULL;

	if (argument->n_tokens == 0 || argument->isComment)
		return;

	argument->instruction->f(&stack, argument->line_number);
}

/**
 * invalid_instruction - Handles an unknown instruction error.
 */

void invalid_instruction(void)
{
	fprintf(stderr, "L%d: unknown instruction %s\n",
			argument->line_number, argument->line_strs[0]);
	closeStream();
	free_toks();
	free_arg();
	exit(EXIT_FAILURE);
}

/**
 * setStream - Sets the stream for reading from the specified file.
 * @fileName: Name of the file to open and set as the stream.
 */

void setStream(char *fileName)
{
	int fd;

	fd = open(fileName, O_RDONLY);
	if (fd == -1)
		read_failed(fileName);

	argument->stream = fdopen(fd, "r");
	if (argument->stream == NULL)
	{
		close(fd);
		read_failed(fileName);
	}
}

/**
 * setInstruction - Sets the instruction based on the first token
 * in the input line.
 */

void setInstruction(void)
{
	int i = 0;
	instruction_t instructions[] = {
		{"push", &push}, {"pop", &pop},
		{"pint", &pint}, {"swap", &swap},
		{"nop", &nop}, {"add", &add},
		{"pall", &pall}, {"sub", &sub},
		{"div", &_div}, {"mul", &mul},
		{"rotl", &rotl}, {"rotr", &rotr},
		{"stack", &stack}, {"queue", &queue},
		{"pstr", &pstr}, {"pchar", &pchar},
		{"mod", &mod},
		{NULL, NULL}
	};

	if (argument->n_tokens == 0) /* no instructions */
		return;

	argument->isComment = 0;
	if (is_comment())
	{
		argument->isComment = 1;
		return;
	}

	for (; instructions[i].opcode != NULL; i++)
	{
		/* compare opcode of instruction to first token (instruct..) */
		if (strcmp(instructions[i].opcode, argument->line_strs[0])
				== 0)
		{
			argument->instruction->opcode = instructions[i].opcode;
			argument->instruction->f = instructions[i].f;
			return;
		}
	}

	invalid_instruction();
}
