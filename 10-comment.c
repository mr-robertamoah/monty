#include "monty.h"

/**
* is_comment - checks the line_strs if it starts with #"
* Return: 0 or 1
*/
int is_comment(void)
{
	if (
		argument->line_strs &&
		argument->line_strs[0] &&
		argument->line_strs[0][0] == '#'
	)
		return (1);

	return (0);
}
