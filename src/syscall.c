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
#include "all_syscall.h"
#include "ftrace.h"

void print_args(struct user_regs_struct regs)
{
	size_t args[6] = { regs.rdi, regs.rsi, regs.rdx, regs.rcx, regs.r8,
			regs.r9 };

	for (int i = 0 ; i < g_sys[regs.orig_rax].nb_arg ; i++) {
		printf("%#lx", args[i]);
		if (i != g_sys[regs.orig_rax].nb_arg - 1)
			printf(", ");
	}
}

void print_syscall(struct user_regs_struct regs)
{
	if ((int)regs.orig_rax != -1) {
		if (regs.orig_rax > NB_SYS)
			printf("Unknown syscall\n");
		else if (regs.orig_rax == SYS_EXIT)
			printf("+++ exited with %lld +++\n", regs.rdi);
		else {
			printf("Syscall %s(", g_sys[regs.orig_rax].str);
			print_args(regs);
			printf(") = %#llx\n", regs.rax);
		}
	}
}
