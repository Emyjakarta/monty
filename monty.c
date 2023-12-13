#include "monty.h"

/**
 * main - entry point for monty
 * @argc: arguments counter
 * @argv: arguments vector
 *
 * Return: 0 on success, else exits with -1 on error
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	monty_list.filename = argv[1];
	parse();

	/* clean up the stack and exit */
	safe_free_stack(&monty_list.head);

	return (EXIT_SUCCESS);
}
