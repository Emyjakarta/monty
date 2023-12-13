#include "monty.h"
/**
 * rotl-rotates the stack to the top
 * the top element of the stack becomes
 * the last one and the second top element
 * of the stack beomes the first one
 * rotl never fails
 * @stack: pointer to a pointer to the stack
 * @line_number: line number
 * Return: void
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *top_element = *stack;

	stack_t *second = NULL;

	if (size(monty_list) < 2 || top_element == NULL || top_element->next == NULL)
	{
		fprintf(stderr, "L%u: can't rotl, stack too short\n", line_number);
		return;
	}
	second = top_element->next;
	while (top_element->next != NULL)
	{
		top_element = top_element->next;
	}

	top_element->next = *stack;
	*stack = second;
	second->prev = NULL;
	top_element->next->prev = top_element;
	top_element->next = NULL;
	monty_list.tail = top_element;

	/*top_element->next = monty_list.head;
	monty_list.head->prev = top_element;
	monty_list.head = monty_list.head->next;
	top_element->next = NULL;
	monty_list.head->prev = NULL;
	(*stack)->prev = NULL;
	monty_list.tail = top_element;*/ 
}
/**
 *  * mod-computes the rest of the division of the
 *   * second top element of the stack by the
 *    * top element of the stack
 *     * @stack: pointer to a pointer to the stack
 *      * @line_number: line number
 *       * Return: void
 *        */
void rotr(stack_t **stack, unsigned int line_number)
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
