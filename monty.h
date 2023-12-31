#ifndef MONTY_H
#define MONTY_H
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define BUFF_SIZE 1024

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
 * @ds: keeps track of the specific data structure to use with the linked lists
 * (either stacks or queues)
 * @size: keeps track of the number of nodes int the queue or stack
 * @line_number: the line number where the instruction appears
 * @filename: the name of the file received on the command line (argv[1])
 * @buffer: the buffer to store the data from the file
 * @opcode: the opcode to work with
 * @value: used when the @opcode is "push"
 * @fileptr: used to handle file pointers (buffered I/O)
 * @cleanup: a cleanup function for each element in the list
 */
typedef struct list_s
{
	stack_t *head;
	stack_t *tail;
	size_t size;
	int ds;
	unsigned int line_number;
	char *filename;
	char *buffer;
	char *opcode;
	char *value;
	FILE *fileptr;
	void (*cleanup)(void **);
} list_t;

/* monty command context */
extern list_t monty_list;

/* flags to choose which data structure to use */

#define USE_QUEUE 1
#define USE_STACK 2
#define USE_DEFAULT 0 /* default is stack */

/* useful simple macro functions for quick info */

#define top(list) ((list).head->n)
#define size(list) ((list).size)
#define is_empty(list) ((list).size == 0)
#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_in_ascii_range(c) ((c) >= 0 && (c) <= 127)
#define is_queue(opcode) (strcmp((opcode), "queue") == 0)
#define is_stack(opcode) (strcmp((opcode), "stack") == 0)
#define set_ds(opcode)                                                        \
	((is_queue(opcode)) ? USE_QUEUE                                           \
						: ((is_stack(opcode)) ? USE_STACK : USE_DEFAULT))

/* stack operations */

void push(stack_t **stack, int data);
void pop(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, __attribute__((unused)) unsigned int line_number);

/* utility functions */

void parse(void);
void handle_exit(void);
int is_integer(const char *str);
void execute_command(char *command);
void handle_push(stack_t **stack, unsigned int line_number);

/* monty math operations */

void sub(stack_t **stack, unsigned int line_number);
void mul(stack_t **stack, unsigned int line_number);
void mod(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void division(stack_t **stack, unsigned int line_number);

/* monty string operations */

void pstr(stack_t **stack, __attribute__((unused)) unsigned int line_number);
void pchar(__attribute__((unused)) stack_t **stack, unsigned int line_number);

/* custom memory functions */

void _free(void **ptr);
void safe_free_stack(stack_t **stack);
void *_calloc(unsigned int nmemb, unsigned int size);
void *_memcpy(void *dest, const void *src, size_t n);
void *_memset(void *mem_area, int c, unsigned int size);
void *_realloc(void *old_mem_blk, size_t old_size, size_t new_size);

/* rotation operations */

void rotl(stack_t **stack, __attribute__((unused)) unsigned int line_number);
void rotr(stack_t **stack, __attribute__((unused)) unsigned int line_number);

#endif /* MONTY_H */
