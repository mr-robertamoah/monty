#include "monty.h"

/**
* delete_stack_node - delete node at the head/top
* Return: void
*/
void delete_stack_node()
{
	stack_t *tmp;

	if (argument->stackHead)
		return;

	tmp = argument->stackHead;
	argument->stackHead = tmp->next;
	free(tmp);
}
