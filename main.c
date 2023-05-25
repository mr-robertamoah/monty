#include "monty.h"

argument_t *argument = NULL;

FILE *fdopen(int fd, const char *mode);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

int is_number(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (i == 0 && str[i] == '-' && str[i + 1])
		{
			i++;
			continue;
		}
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}

	return (1);
}

void runInstruction()
{
	stack_t *stack = NULL;

	if (argument->n_tokens == 0)
		return;

	argument->instruction->f(&stack, argument->line_number);
}

void pint(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	if (argument->stackHead == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		free_all_args();
		exit(EXIT_FAILURE);
	}

	printf("%d\n", argument->stackHead->n);
}

void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}

void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp1, *tmp2;

	(void) stack;
	if (argument->stack_length < 2)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		free_all_args();
		exit(EXIT_FAILURE);
	}

	tmp1 = argument->stackHead;
	tmp2 = tmp1->next;
	tmp1->next = tmp2->next;
	if (tmp1->next)
		tmp1->next->prev = tmp1;
	tmp2->next = tmp1;
	tmp1->prev = tmp2;
	tmp2->prev = NULL;
	argument->stackHead = tmp2;
}

void _div(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp1, *tmp2;

	(void) stack;
	if (argument->stack_length < 2)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
		free_all_args();
		exit(EXIT_FAILURE);
	}

	tmp1 = argument->stackHead;
	tmp2 = tmp1->next;

	if (tmp2->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		free_all_args();
		exit(EXIT_FAILURE);
	}

	tmp2->n = tmp2->n / tmp1->n;
	delete_stack_node();

	argument->stack_length -= 1;
}

void free_all_args()
{
	closeStream();
	free_toks();
	free_arg();
}

void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp1, *tmp2;

	(void) stack;
	if (argument->stack_length < 2)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		free_all_args();
		exit(EXIT_FAILURE);
	}

	tmp1 = argument->stackHead;
	tmp2 = tmp1->next;

	tmp2->n = tmp2->n * tmp1->n;
	delete_stack_node();

	argument->stack_length -= 1;
}

void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp1, *tmp2;

	(void) stack;
	if (argument->stack_length < 2)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		free_all_args();
		exit(EXIT_FAILURE);
	}

	tmp1 = argument->stackHead;
	tmp2 = tmp1->next;

	tmp2->n = tmp2->n - tmp1->n;
	delete_stack_node();

	argument->stack_length -= 1;
}

void add(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp1, *tmp2;

	(void) stack;
	if (argument->stack_length < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		closeStream();
		free_toks();
		free_arg();
		exit(EXIT_FAILURE);
	}

	tmp1 = argument->stackHead;
	tmp2 = tmp1->next;

	tmp2->n = tmp1->n + tmp2->n;
	delete_stack_node();

	argument->stack_length -= 1;
}

void pop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	if (argument->stackHead == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		closeStream();
		free_toks();
		free_arg();
		exit(EXIT_FAILURE);
	}

	delete_stack_node();
	argument->stack_length -= 1;
}

void push(stack_t **stack, unsigned int line_number)
{
	if (argument->n_tokens <= 1 || !(is_number(argument->line_strs[1])))
	{
		free_arg();
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	*stack = malloc(sizeof(stack_t));
	if (*stack == NULL)
		malloc_failed();
	(*stack)->next = (*stack)->prev = NULL;

	(*stack)->n = (int) atoi(argument->line_strs[1]);

	if (argument->stackHead != NULL)
	{
		(*stack)->next = argument->stackHead;
		argument->stackHead->prev = *stack;
	}
	argument->stackHead = *stack;
	argument->stack_length += 1;
}

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (argument->stackHead == NULL)
		return;

	(void) line_number;
	(void) stack;

	tmp = argument->stackHead;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

void check_num_of_arguments(int argc)
{
	if (argc == 2)
		return;

	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}

void free_toks()
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

void free_stackHead()
{
	if (argument->stackHead)
		free_stack(argument->stackHead);

	argument->stackHead = NULL;
}

void closeStream()
{
	if (argument->stream)
	{
		fclose(argument->stream);
		argument->stream = NULL;
	}
}

void free_arg()
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

void invalid_instruction()
{
	fprintf(stderr, "L%d: unknown instruction %s\n",
		argument->line_number, argument->line_strs[0]);
	closeStream();
	free_toks();
	free_arg();
	exit(EXIT_FAILURE);
}

void read_failed(char *fileName)
{
	fprintf(stderr, "Error: Can't open file %s\n", fileName);
	free_arg();
	exit(EXIT_FAILURE);
}

void malloc_failed()
{
	fprintf(stderr, "Error: malloc failed\n");
	free_arg();
	exit(EXIT_FAILURE);
}

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

void tokenize()
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

	argument->line_strs = malloc(sizeof(char *) * (argument->n_tokens + 1));
	strcpy(linecpy, argument->line);
	token = strtok(linecpy, delims);
	while (token)
	{
		argument->line_strs[i] = malloc(sizeof(char) * (strlen(token) + 1));
		if (argument->line_strs[i] == NULL)
			malloc_failed();
		strcpy(argument->line_strs[i], token);
		token = strtok(NULL, delims);
		i++;
	}
	argument->line_strs[i] = NULL;
	free(linecpy);
}

void setInstruction()
{
	int i = 0;
	instruction_t instructions[] = {
		{"push", &push}, {"pop", &pop},
		{"pint", &pint}, {"swap", &swap},
		{"nop", &nop}, {"add", &add},
		{"pall", &pall}, {"sub", &sub},
		{"div", &_div}, {"mul", &mul},
		{NULL, NULL}
	};

	if (argument->n_tokens == 0) /* no instructions */
		return;

	for (; instructions[i].opcode != NULL; i++)
	{
		/* compare opcode of instruction to first token (instruction) */
		if (strcmp(instructions[i].opcode, argument->line_strs[0]) == 0)
		{
			argument->instruction->opcode = instructions[i].opcode;
			argument->instruction->f = instructions[i].f;
			return;
		}
	}

	invalid_instruction();
}

void init_arg()
{
	argument->instruction = malloc(sizeof(instruction_t));
	if (argument->instruction == NULL)
		malloc_failed();

	argument->stackHead = NULL;
	argument->line = NULL;

	argument->n_tokens = 0;
	argument->line_number = 0;
	argument->stack_length = 0;
	argument->stream = NULL;
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
