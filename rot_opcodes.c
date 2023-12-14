#include "monty.h"

/**
 * rotl - rotates the stack to the top
 * @stack: a pointer to the stack or queue
 * @line_number: the index of the current command
 *
 * Note: The top element of the stack becomes the last one, and the second top
 * element of the stack becomes the first one. This function never fails
 */
void rotl(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	stack_t *tmp;

	if (size(monty_list) < 2 || size(monty_list) == 0)
		return; /* there's not enough nodes to rotate */

	/* keep the address of the now old head node and move to next node */
	tmp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	monty_list.head = *stack;

	/* adjust links to insert at the end of the list */
	tmp->next = NULL;
	monty_list.tail->next = tmp;
	tmp->prev = monty_list.tail;
	monty_list.tail = tmp;
}

/**
 * rotr - rotates the stack to the bottom.
 * @stack: a pointer to the stack or queue
 * @line_number: the index of the current command
 *
 * Note: The last element of the stack becomes the top element of the stack.
 * This function never fails
 */
void rotr(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	/* TODO: Solution here. All operation must be in constant time O(1) */
	(void)stack; /* please remove this line when done */
}
