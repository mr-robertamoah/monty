#include "monty.h"

/**
 * rotr - rotates the stack to the bottom
 * @stack: Pointer to the stack.
 * @line_number: Line number where the mul function is called.
 */

void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp1, *tmp2;

	(void) stack;
	(void) line_number;
	if (argument->stack_length < 2)
		return;

	tmp1 = tmp2 = argument->stackHead;
	while (tmp2->next != NULL)
		tmp2 = tmp2->next;

	if (tmp2->prev)
		tmp2->prev->next = NULL;
	tmp2->prev = NULL;
	tmp2->next = tmp1;
	tmp1->prev = tmp2;

	argument->stackHead = tmp2;
}
