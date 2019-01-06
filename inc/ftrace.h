/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#ifndef FTRACE_H_
# define FTRACE_H_

#include <sys/user.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_sym_tab {
	unsigned long address;
	char *name;
	struct s_sym_tab *next;
	struct s_sym_tab *prev;
} t_sym_tab;

typedef struct s_call_stack {
	unsigned long address;
	char *name;
	struct s_call_stack *next;
	struct s_call_stack *prev;
} t_call_stack;

t_sym_tab *add_to_list(t_sym_tab *, t_sym_tab *);
t_call_stack *add_to_list_cs(t_call_stack *, t_call_stack *);
t_sym_tab *create_node(unsigned long, char *);
t_call_stack *create_node_cs(unsigned long, char *);
void display_list_sym_tab(t_sym_tab *);
unsigned long get_func_addr(t_sym_tab *, char *);
void print_entering(unsigned long, t_sym_tab *, unsigned long,
		t_call_stack **);
void print_syscall(struct user_regs_struct);
int trace(t_sym_tab *, char **);

#endif
