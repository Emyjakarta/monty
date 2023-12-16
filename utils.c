#include "monty.h"

/* monty list command context */
list_t monty_list = {NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, _free};

/**
 * is_integer - returns 1 if the string is an integer else 0
 * @str: the string containing the value to check
 *
 * Return: 1 if it is an integer, else it returns 0
 */
int is_integer(const char *str)
{
	int numbers = 0;

	if (str == NULL || *str == '\0')
		return (0);

	if (*str == '-' || *str == '+')
		str++; /* moved past the sign */

	while (*str != '\0')
	{
		if (is_digit(*str))
		{
			str++; /* we found a number, keep searching */
			numbers++;
		}
		else
			return (0); /* non-integer found */
	}

	if (numbers == 0)
		return (0);

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
	size_t size = BUFF_SIZE;
	ssize_t n_read;

	monty_list.fileptr = fopen(monty_list.filename, "r");
	if (monty_list.fileptr == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", monty_list.filename);
		handle_exit();
	}

	monty_list.buffer = _calloc(size, sizeof(char));
	if (monty_list.buffer == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		fclose(monty_list.fileptr);
		handle_exit();
	}

	while ((n_read = getline(&monty_list.buffer, &size, monty_list.fileptr)) !=
		   -1)
	{
		++monty_list.line_number;
		execute_command(monty_list.buffer);
	}

	/* let's handle errors (insufficient memory) or EOF */
	if (n_read == -1)
	{
		/* let's check for memory allocation or reallocation failures */
		if (errno == ENOMEM)
		{
			fprintf(stderr, "Error: malloc failed\n");
			handle_exit();
		}
	}

	/* close the file pointer and cleanup memory for the buffer */
	fclose(monty_list.fileptr);
	monty_list.cleanup((void **)&monty_list.buffer);
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
		{"rotl", rotl},		   {"rotr", rotr},	  {NULL, NULL}};

	while (instructs[i].opcode != NULL)
	{
		monty_list.opcode = strtok(command, " \t\n");
		if ((monty_list.opcode != NULL) &&
			(is_stack(monty_list.opcode) || is_queue(monty_list.opcode)))
		{
			monty_list.ds = set_ds(monty_list.opcode);
			return;
		}
		/* handle comments, the nop opcode and failed missing opcodes */
		if (monty_list.opcode == NULL ||
			strcmp(monty_list.opcode, "nop") == 0 || *monty_list.opcode == '#')
			return;
		if (strcmp(instructs[i].opcode, monty_list.opcode) == 0)
		{
			if (strcmp(monty_list.opcode, "push") == 0)
				monty_list.value = strtok(NULL, " \t\n");
			instructs[i].f(&monty_list.head, monty_list.line_number);
			return; /* we just executed a command, is there more? */
		}
		i++; /* keep searching for the right function to handle this */
	}
	if (instructs[i].opcode == NULL)
	{
		/* if we made it this far, the opcode does not exist */
		fprintf(stderr, "L%u: unknown instruction %s\n",
				monty_list.line_number, monty_list.opcode);
		handle_exit();
	}
}
