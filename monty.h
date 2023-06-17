#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

#define NO_OF_INSTRUCTIONS 7

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
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
 * struct argument_s - struct to help pass arguments around
 *
 */
typedef struct argument_s
{
	char **line_strs; /* used to store tokens from line */
	char *line; /* used for getting line from file */
	unsigned int line_number; /* for tracking current line number */
	instruction_t *instruction; /* a valid instruction from a line */
	int n_tokens; /* number of tokens created from line */
	int isComment; /* tracks whether or not tokens start with # */
	FILE *stream; /* file stream */
	int stack_length; /* tracks the number of nodes in the stack */
	stack_t *stackHead; /* head/top of the stack (doubly linked lists of struct stack_s) */
	int stack; /* for switching between the use of stack and queue */
} argument_t;

FILE *fdopen(int fd, const char *mode);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

extern argument_t *argument;

void push(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void nop(stack_t **stack, unsigned int line_number);
void sub(stack_t **stack, unsigned int line_number);
void _div(stack_t **stack, unsigned int line_number);
void mul(stack_t **stack, unsigned int line_number);
void mod(stack_t **stack, unsigned int line_number);
void pchar(stack_t **stack, unsigned int line_number);
void pstr(stack_t **stack, unsigned int line_number);
void rotl(stack_t **stack, unsigned int line_number);
void rotr(stack_t **stack, unsigned int line_number);
void stack(stack_t **stack, unsigned int line_number);
void queue(stack_t **stack, unsigned int line_number);

void check_num_of_arguments(int argc);
void read_failed(char *fileName);
void malloc_failed(void);
void free_all_args(void);
void free_arg(void);
void free_toks(void);
void free_stack(stack_t *head);
void delete_stack_node(void);
void closeStream(void);
void setStream(char *fileName);
void setInstruction(void);
void invalid_instruction(void);
void runInstruction(void);
void free_stackHead(void);
void tokenize(void);
void init_arg(void);


int is_comment();
int is_number(char *str);


#endif /* MONTY_H */
