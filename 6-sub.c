#include "monty.h"

/**
 * sub - Subtracts the top element of the stack from the second top element.
 * @stack: Pointer to the stack.
 * @line_number: Line number where the sub function is called.
 */

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
