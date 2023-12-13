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
/**
 * sub-subtracts the top element of the stack
 * from the second top element of the stack
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
 * Return: void
 */
void sub(stack_t **stack, unsigned int line_number)
{
	int top_element;

	if (size(monty_list) < 2)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		handle_exit();
	}
	top_element = top(monty_list);
	pop(stack, line_number);
	(*stack)->n -= top_element;

}
/**
 *  * div-adds the top two elements of the stack
 *   * @stack: pointer to a pointer to the stack
 *    * @line_number: line number
 *     * Return: void
 *      */
void div(stack_t **stack, unsigned int line_number)
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
 *  * mul-adds the top two elements of the stack
 *   * @stack: pointer to a pointer to the stack
 *    * @line_number: line number
 *     * Return: void
 *      */
void mul(stack_t **stack, unsigned int line_number)
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
 *  * mod-adds the top two elements of the stack
 *   * @stack: pointer to a pointer to the stack
 *    * @line_number: line number
 *     * Return: void
 *      */
void mod(stack_t **stack, unsigned int line_number)
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
