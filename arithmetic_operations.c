#include "monty.h"

/**
 * add-adds the top two elements of the stack
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
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
 * sub - subtracts the top two elements of the stack
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
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
 * mul - multiplies the top two elements of the stack
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
 */
void mul(stack_t **stack, unsigned int line_number)
{
	int top_element;

	if (size(monty_list) < 2)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		handle_exit();
	}

	top_element = top(monty_list);
	pop(stack, line_number);
	(*stack)->n *= top_element;
}

/**
 * division - divides the top two elements of the stack
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
 */
void division(stack_t **stack, unsigned int line_number)
{
	int top_element;

	if (size(monty_list) < 2)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		handle_exit();
	}

	top_element = top(monty_list);
	if (top_element == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		handle_exit();
	}

	pop(stack, line_number);
	(*stack)->n /= top_element;
}

/**
 * mod - performs modulo arithmetic on the top two elements of the stack
 * top element of the stack
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
 */
void mod(stack_t **stack, unsigned int line_number)
{
	int top_element;

	if (size(monty_list) < 2)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		handle_exit();
	}

	top_element = top(monty_list);
	if (top_element == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		handle_exit();
	}

	pop(stack, line_number);
	(*stack)->n %= top_element;
}
