/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include "ftrace.h"

int tracee(char **argv)
{
	ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	if (execv(argv[1], argv + 1) == -1)
		return (0);
	return (1);
}

int find_relative_call(pid_t child, t_sym_tab *lsm, unsigned long rip,
	t_call_stack **cs)
{
	struct user_regs_struct regs;
	unsigned ins;
	unsigned char sec;
	int status;

	ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
	wait(&status);
	if (WIFEXITED(status))
		return (0);
	ptrace(PTRACE_GETREGS, child, NULL, &regs);
	ins = ptrace(PTRACE_PEEKTEXT, child, regs.rip, NULL);
	sec = ((unsigned)0xFF00 & ins) >> 8;
	if (sec == 0x48) {
		print_entering(regs.rip, lsm, rip, cs);
	}
	return (1);
}

void find_relative_ret(t_call_stack *cs, unsigned long addr)
{
	t_call_stack *tmp = cs;

	while (tmp != NULL) {
		if (tmp->address == addr) {
			printf("Leaving function %s\n", tmp->name);
			break;
		}
		tmp = tmp->next;
	}
}

void tracer(pid_t child, t_sym_tab *lsm)
{
	struct user_regs_struct regs;
	t_call_stack *cs;
	unsigned ins;
	int status;

	while (1) {
		ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
		wait(&status);
		if (WIFEXITED(status))
			break;
		ptrace(PTRACE_GETREGS, child, NULL, &regs);
		ins = ptrace(PTRACE_PEEKTEXT, child, regs.rip, NULL);
		if (((unsigned)0xFF & ins) == 0xE8)
			find_relative_call(child, lsm, regs.rip, &cs);
		else if (((unsigned)0xFF & ins) == 0xC3)
			find_relative_ret(cs,
			ptrace(PTRACE_PEEKTEXT, child, regs.rsp, 0) - 5);
		else
			print_syscall(regs);
	}
}

int trace(t_sym_tab *lsm, char **argv)
{
	pid_t child = fork();

	if (child == 0 && tracee(argv))
		return (1);
	else if (child > 0) {
		printf("Entering function main at %#lx\n",
		get_func_addr(lsm, "main"));
		tracer(child, lsm);
		return (1);
	} else
		return (0);
	return (0);
}
