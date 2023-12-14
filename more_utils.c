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

	/* cleanup space for the commands array */
	free_cmds();

	/* clear the stack */
	safe_free_stack(&monty_list.head);

	/* now exit with the failure */
	exit(EXIT_FAILURE);
}

/**
 * free_cmds - handles memory deallocation for the commands array
*/
void free_cmds(void)
{
	size_t i;

	if (monty_list.commands == NULL)
		return;

	for (i = monty_list.line_number - 1; monty_list.commands[i] != NULL; i++)
	{
		monty_list.cleanup((void **)&monty_list.commands[i]);
	}
	monty_list.cleanup((void **)&monty_list.commands);
}

/**
 * tokenize - returns a string array of strings based on a delimiter
 * @str: the string to tokenize
 * @delim: the delimiter
 *
 * Return: a NULL-terminated string array of words
 */
char **tokenize(char *str, const char *delim)
{
	char *token = NULL, *dup_str = NULL, **commands = NULL;
	size_t num_of_tokens, i;

	if (str == NULL || *str == '\0' || delim == NULL)
		return (NULL);

	/* tokenize the input string */
	dup_str = strdup(str);
	if (dup_str == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		handle_exit();
	}
	token = strtok(dup_str, delim);
	num_of_tokens = 0;
	while (token != NULL)
	{
		++num_of_tokens; /* count all the tokens */
		token = strtok(NULL, delim);
	}
	free(dup_str);

	if (num_of_tokens > 0)
	{
		commands = _calloc(num_of_tokens + 1, sizeof(char *));
		if (commands == NULL)
		{
			fprintf(stderr, "Error: malloc failed\n");
			handle_exit();
		}
		token = strtok(str, delim);
		i = 0;
		while (token != NULL)
		{
			commands[i++] = strdup(token);
			token = strtok(NULL, delim);
		}
		commands[i] = NULL;
	}
	return (commands);
}
