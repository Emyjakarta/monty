#include "monty.h"
/**
 * add-adds the top two elements of the stack
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
 * Return: void
 */
void add(stack_t **stack, unsigned int line_number)
{
	int top_element;

	if (size(monty_list) < 2)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		handle_exit();
	}
	top_element = top(monty_list);
	pop(stack, line_number);
	(*stack)->n += top_element;

}
/**
 * nop-does not do anything on the stack
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
 * Return: void
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;

	return;
}
