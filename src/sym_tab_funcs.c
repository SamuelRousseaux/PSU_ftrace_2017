/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ftrace.h"

void print_entering(unsigned long rip, t_sym_tab *lsm, unsigned long srip,
	t_call_stack **cs)
{
	t_sym_tab *tmp = lsm;

	while (tmp != NULL) {
		if (rip == tmp->address && tmp->name[0] != '_') {
			printf("Entering function %s at %#lx\n",
				tmp->name, tmp->address);
			*cs = add_to_list_cs(*cs,
					create_node_cs(srip, tmp->name));
			break;
		}
		tmp = tmp->next;
	}
}

unsigned long get_func_addr(t_sym_tab *lsm, char *name)
{
	t_sym_tab *tmp = lsm;

	while (tmp != NULL) {
		if (strcmp(tmp->name, name) == 0)
			return (tmp->address);
		tmp = tmp->next;
	}
	return (0);
}
