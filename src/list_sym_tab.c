/*
** EPITECH PROJECT, 2018
** ftrace
** File description:
** list_sym_tab
*/

#include "ftrace.h"

t_sym_tab *create_node(unsigned long address, char *name)
{
	t_sym_tab *elem;

	elem = malloc(sizeof(t_sym_tab));
	if (elem == NULL)
		return (NULL);
	elem->address = address;
	elem->name = name;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_sym_tab *add_to_list(t_sym_tab *list, t_sym_tab *new_elem)
{
	t_sym_tab *tmp = list;

	if (list == NULL)
		return (new_elem);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_elem;
	new_elem->prev = tmp;
	return (list);
}

t_call_stack *create_node_cs(unsigned long address, char *name)
{
	t_call_stack *elem;

	elem = malloc(sizeof(t_call_stack));
	if (elem == NULL)
		return (NULL);
	elem->address = address;
	elem->name = name;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_call_stack *add_to_list_cs(t_call_stack *list, t_call_stack *new_elem)
{
	t_call_stack *tmp = list;

	if (list == NULL)
		return (new_elem);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_elem;
	new_elem->prev = tmp;
	return (list);
}

void display_list_sym_tab(t_sym_tab *list_sym_tab)
{
	t_sym_tab *tmp = list_sym_tab;

	while (tmp != NULL) {
		printf("0x%08lx %s\n", tmp->address, tmp->name);
		tmp = tmp->next;
	}
}
