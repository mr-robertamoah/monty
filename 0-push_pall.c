#include "monty.h"

/**
 * push - Pushes an integer onto the stack.
 * @stack: Pointer to the stack.
 * @line_number: Line number where the push function is called.
 */

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

	if (argument->stackHead == NULL)
	{
		argument->stackHead = *stack;
	}
	else
	{
		if (argument->stack)
		{
			(*stack)->next = argument->stackHead;
			argument->stackHead->prev = *stack;
			argument->stackHead = *stack;
		}
		else
		{
			stack_t *tmp = argument->stackHead;

			while (tmp->next)
				tmp = tmp->next;
			tmp->next = *stack;
			(*stack)->prev = tmp;
		}
	}
	argument->stack_length += 1;
}

/**
 * pall - Prints all the elements in the stack.
 * @stack: Pointer to the stack.
 * @line_number: Line number where the pall function is called.
 */

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
