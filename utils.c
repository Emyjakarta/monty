#include "monty.h"

/* monty list command context */
list_t monty_list = {NULL, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, _free};

/**
 * is_integer - returns 1 if the string is an integer else 0
 * @str: the string containing the value to check
 *
 * Return: 1 if it is an integer, else it returns 0
 */
int is_integer(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);

	while (*str != '\0')
	{
		if (is_digit(*str) || str[0] == '-')
			str++; /* we found a number, keep searching */
		else
			return (0); /* non-integer found */
	}

	return (1); /* if we got this far, it's definitely an integer */
}

/**
 * handle_push - handles the push operation
 * @stack: a pointer to the stack
 * @line_number: the index of the current command
 */
void handle_push(stack_t **stack, unsigned int line_number)
{
	/* handle non-integer values */
	if (monty_list.value == NULL || is_integer(monty_list.value) == 0)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		handle_exit();
	}

	/* push the element to the stack */
	push(stack, atoi(monty_list.value));
}

/**
 * parse - performs a simple parsing on the file
 */
void parse(void)
{
	FILE *file;
	size_t n_read, total_read = 0;

	file = fopen(monty_list.filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", monty_list.filename);
		handle_exit();
	}

	monty_list.buffer = _calloc(BUFF_SIZE, sizeof(char));
	if (monty_list.buffer == NULL)
	{
		fprintf(stderr, "malloc failed\n");
		handle_exit();
	}

	while ((n_read = (fread(monty_list.buffer, BUFF_SIZE, 1, file)) != 0))
	{
		if (n_read >= total_read)
		{
			monty_list.buffer =
				_realloc(monty_list.buffer, total_read, total_read * 2);
			if (monty_list.buffer == NULL)
			{
				fprintf(stderr, "malloc failed\n");
				handle_exit();
			}
		}
		total_read += n_read;
	}
	fclose(file);

	if (*monty_list.buffer == '\0')
		return;

	parse_helper();
}

/**
 * parse_helper - a helper function to complete the parsing before execution
 */
void parse_helper(void)
{
	size_t i;

	monty_list.commands = tokenize(monty_list.buffer, "\n");
	monty_list.cleanup((void **)&monty_list.buffer);

	if (monty_list.commands == NULL)
		return; /* probably we received a bunch of whitespaces or nothing */

	i = 0;
	while (monty_list.commands[i] != NULL)
	{
		++monty_list.line_number;

		/* handle the command execution and clean up */
		execute_command(monty_list.commands[i]);
		monty_list.cleanup((void **)&monty_list.commands[i]);

		i++; /* get the next command */
	}
	/* clean up and leave here */
	monty_list.cleanup((void **)&monty_list.commands);
}

/**
 * execute_command - handles the execution of monty commands
 * @command: the command to execute
 */
void execute_command(char *command)
{
	size_t i = 0;

	instruction_t instructs[] = {
		{"push", handle_push}, {"pop", pop},	  {"pint", pint},
		{"pall", pall},		   {"add", add},	  {"swap", swap},
		{"sub", sub},		   {"div", division}, {"mul", mul},
		{"mod", mod},		   {"pchar", pchar},  {"pstr", pstr},
		{NULL, NULL}};

	/* handle comments and nop opcode */
	if (*command == '#')
		return;

	while (instructs[i].opcode != NULL)
	{
		monty_list.opcode = strtok(command, " ");

		/* handle the nop opcode and failed missing opcodes */
		if (monty_list.opcode == NULL || strcmp(monty_list.opcode, "nop") == 0)
			return;

		if (strcmp(instructs[i].opcode, monty_list.opcode) == 0)
		{
			if (strcmp(monty_list.opcode, "push") == 0)
				monty_list.value = strtok(NULL, " ");
			instructs[i].f(&monty_list.head, monty_list.line_number);
			return; /* we just executed a command, is there more? */
		}
		i++; /* keep searching for the right function to handle this */
	}

	if (instructs[i].opcode == NULL)
	{
		/* if we made it this far, the opcode does not exit */
		fprintf(stderr, "L%u: unknown instruction %s\n",
				monty_list.line_number, monty_list.opcode);
		handle_exit();
	}
}
