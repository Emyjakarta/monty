#include "monty.h"

/**
 * push - inserts a node at the beginning of the list
 * @stack: a pointer to the stack
 * @data: the integer value to insert
 */
void push(stack_t **stack, int data)
{
	stack_t *new_frame = malloc(sizeof(stack_t));

	if (new_frame == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		handle_exit();
	}

	new_frame->n = data;

	new_frame->prev = NULL;
	if (is_empty(monty_list))
	{
		*stack = new_frame;
		(*stack)->next = NULL;
		monty_list.tail = *stack;
	}
	else
	{
		new_frame->next = *stack;
		(*stack)->prev = new_frame;
		if ((*stack)->next == NULL)
			(*stack)->prev = new_frame;

		*stack = new_frame;
	}

	monty_list.size++;
}

/**
 * pop - removes a node at the beginning of the linked list
 * @stack: a pointer to the stack
 * @line_number: the index of the current command
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (is_empty(monty_list))
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		handle_exit();
	}

	tmp = *stack;
	(*stack) = (*stack)->next;

	/* cleanup memory for the deleted frame and decrement the size */
	monty_list.cleanup((void **)&tmp);
	monty_list.size--;

	/* check if the operation caused the stack to become empty */
	if (is_empty(monty_list))
	{
		monty_list.tail = NULL;
	}
}

/**
 * pint - prints the value at the top of stack (TOS)
 * @stack: the stack
 * @line_number: the index of the current command
 */
void pint(__attribute__((unused)) stack_t **stack, unsigned int line_number)
{
	if (is_empty(monty_list))
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		handle_exit();
	}

	printf("%d\n", top(monty_list));
	fflush(stdout);
}

/**
 * pall - prints all the elements in the stack
 * @stack: the stack
 * @line_number: the index of the current command
 */
void pall(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	stack_t *tmp;

	/* handle cases when the stack is empty */
	if (is_empty(monty_list))
	{
		return;
	}

	tmp = *stack;
	/* the stack is not empty, let's print it */
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}

	fflush(stdout);
}
