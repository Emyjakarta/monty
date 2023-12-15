#include "monty.h"

/**
 * pchar - prints the char at the top of the stack
 * @stack: the stack
 * @line_number: the index of the current command
 */
void pchar(__attribute__((unused)) stack_t **stack, unsigned int line_number)
{
	if (is_empty(monty_list))
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		handle_exit();
	}

	if (is_in_ascii_range(top(monty_list)))
		printf("%c\n", top(monty_list));
	else
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		handle_exit();
	}
}

/**
 * pstr - prints the string starting at the top of the stack
 * @stack: the stack
 * @line_number: the index of the current command
 */
void pstr(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	stack_t *tmp;

	if (is_empty(monty_list))
	{
		putchar('\n');
		fflush(stdout);
		return;
	}

	tmp = *stack;
	while (tmp != NULL && tmp->n != 0)
	{
		if (is_in_ascii_range(tmp->n))
			putchar(tmp->n);
		else
			break;
		tmp = tmp->next;
	}
	putchar('\n');
	fflush(stdout);
}
