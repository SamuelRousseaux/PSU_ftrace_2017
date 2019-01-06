/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <err.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ftrace.h"

Elf *init_elf(char *file_name, Elf **e)
{
	int fd = open(file_name, O_RDONLY, 0);

	if (fd < 0) {
		fprintf(stderr, "Error: open_failed.\n");
		return (NULL);
	} else if (elf_version(EV_CURRENT) == EV_NONE) {
		fprintf(stderr, "Error: Elf init failed.\n");
		return (NULL);
	}
	*e = elf_begin(fd, ELF_C_READ, NULL);
	if (*e == NULL) {
		fprintf(stderr, "Error: couldn't retreive elf header.\n");
		return (NULL);
	} else if (elf_kind(*e) != ELF_K_ELF) {
		fprintf(stderr, "Error: %s isn't an elf file.\n", file_name);
		return (NULL);
	}
	return (*e);
}

t_sym_tab *get_sym_tab(Elf64_Shdr **sym_shdr, Elf_Scn **sym_scn, Elf **e)
{
	Elf_Data *data = elf_getdata(*sym_scn, NULL);
	t_sym_tab *list_sym_tab = NULL;
	int nb_sym = (*sym_shdr)->sh_size / (*sym_shdr)->sh_entsize;
	Elf64_Sym *symtab = (Elf64_Sym *)data->d_buf;
	int st_type = 0;

	for (int i = 0 ; i < nb_sym ; ++i) {
		st_type = ELF64_ST_TYPE(symtab[i].st_info);
		if (st_type == STT_FUNC || st_type == STT_NOTYPE) {
			list_sym_tab = add_to_list(list_sym_tab,
			create_node(symtab[i].st_value, elf_strptr(*e,
			(*sym_shdr)->sh_link, symtab[i].st_name)));
			if (list_sym_tab == NULL)
				return (NULL);
		}
	}
	return list_sym_tab;
}

t_sym_tab *get_sym_sec(Elf **e, Elf64_Shdr **shdr, Elf_Scn **scn)
{
	while ((*scn = elf_nextscn(*e, *scn)) != NULL) {
		*shdr = elf64_getshdr(*scn);
		if (!*shdr)
			return (NULL);
		else if ((*shdr)->sh_type == SHT_SYMTAB)
			return (get_sym_tab(shdr, scn, e));
	}
	fprintf(stderr, "Error: no symtab found.\n");
	return (NULL);
}

int main(int argc, char **argv)
{
	Elf *e = NULL;
	Elf64_Shdr *shdr = NULL;
	Elf_Scn *scn = NULL;
	t_sym_tab *list_sym_tab = NULL;

	if (argc < 2)
		return (84);
	if (init_elf(argv[1], &e) == NULL)
		return (84);
	if (gelf_getclass(e) != ELFCLASS64)
		return (84);
	list_sym_tab = get_sym_sec(&e, &shdr, &scn);
	if (list_sym_tab == NULL)
		return (84);
	trace(list_sym_tab, argv);
	elf_end(e);
	return (0);
}
