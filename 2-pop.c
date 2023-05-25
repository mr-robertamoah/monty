#include "monty.h"

/**
 * pop - Removes the top element from the stack.
 * @stack: Pointer to the stack.
 * @line_number: Line number where the pop function is called.
 */

void pop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	if (argument->stackHead == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		closeStream();
		free_toks();
		free_arg();
		exit(EXIT_FAILURE);
	}

	delete_stack_node();
	argument->stack_length -= 1;
}
