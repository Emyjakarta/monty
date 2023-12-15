#include "monty.h"

/**
 * safe_free_stack - frees memory for the stack
 * @stack: struct for stack
 */
void safe_free_stack(stack_t **stack)
{
	while (stack != NULL && *stack != NULL)
	{
		pop(stack, monty_list.line_number);
	}
}

/**
 * handle_exit - handles exit on multiple error cases where memory needs to be
 * deallocated exiting to avoid potential memory leaks
 */
void handle_exit(void)
{
	/* cleanup the buffer */
	monty_list.cleanup((void **)&monty_list.buffer);

	/* clear the stack */
	safe_free_stack(&monty_list.head);

	/* close the file pointer */
	fclose(monty_list.fileptr);

	/* now exit with the failure */
	exit(EXIT_FAILURE);
}
