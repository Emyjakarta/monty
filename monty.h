#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: the integer data to store
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct list_s - a mini object-oriented approach list to keep stack/queues
 * @head: keeps the address of the head node
 * @tail: keeps the address of the tail node (helps to achieve O(1) when
 * inserting at the end)
 * @size: keeps track of the number of nodes int the queue or stack
 * @cmd_count: keeps track of the number of commands executed since the shell
 * started
 * @cleanup: a cleanup function for each element in the list
 */
typedef struct list_s
{
	stack_t *head;
	stack_t *tail;
	size_t size;
	size_t cmd_count;
	void (*cleanup)(void **);
} list_t;

extern list_t monty_list;

/* useful simple macro functions for quick info */

#define top(list) ((list).head->n)
#define size(list) ((list).size)
#define is_empty(list) ((list).size == 0)

/* stack operations */

void push(stack_t **stack, int data);
void pop(stack_t **stack, unsigned int line_number);
void pint(stack_t *stack, unsigned int line_number);
void pall(stack_t *stack, unsigned int line_number);

void _free(void **ptr);

#endif /* MONTY_H */
