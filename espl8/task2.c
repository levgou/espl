#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "task0/examine.h"

#define SYM_P_FORMAT "[%2d] %15x %8d %10s %40s \n"
#define SYM_HEAD "[%2s] %15s %8s %10s %40s \n", "ID", "Value", "Sec ID", "Sec name", "Symbol name"

void print_sym_table(Elf32_Shdr *cur_section, char *mapped_file, Elf32_Shdr *str_table,
                     int section_index, char *section_name);

/* [index] value section_index section_name symbol_name */
void print_sym_tables(char *mapped_file, Elf32_Ehdr *elf_header,
                      Elf32_Shdr *section_headers, int section_headers_num)
{
    int i;
    char *section_str_table = mapped_file + section_headers[elf_header->e_shstrndx].sh_offset;
    char *cur_section_name = NULL;

    Elf32_Shdr *cur_section = NULL;
    Elf32_Shdr *str_table = NULL;

    for (i = 0; i < section_headers_num; i++)
    {
        if (strncmp(".strtab", section_str_table + section_headers[i].sh_name, 7) == 0)
        {
            str_table = &section_headers[i];
            break;
        }
    }

    printf(SYM_HEAD);
    for (i = 0; i < section_headers_num; i++)
    {
        cur_section = &section_headers[i];
        cur_section_name = section_str_table + section_headers[i].sh_name;

        if (cur_section->sh_type != SHT_SYMTAB && cur_section->sh_type != SHT_DYNSYM)
            continue;
        
        print_sym_table(cur_section, mapped_file, str_table, i, cur_section_name);
    }
}

void print_sym_table(Elf32_Shdr *cur_section, char *mapped_file, Elf32_Shdr *str_table,
                     int section_index, char *section_name)
{
    int num_of_symbols = cur_section->sh_size / cur_section->sh_entsize;
    Elf32_Sym cur_symbol;

    int i;
    for (i = 0; i < num_of_symbols; i++)
    {
        cur_symbol = *(Elf32_Sym *)(mapped_file + cur_section->sh_offset + i * cur_section->sh_entsize);

        printf(SYM_P_FORMAT,
               i,
               cur_symbol.st_value,
               section_index,
               section_name,
               mapped_file + cur_symbol.st_name + str_table->sh_offset);
    }
}

int main(int argc, char const *argv[])
{
    char *mapped_file = NULL;
    Elf32_Ehdr elf_header;
    char info_buf[100];

    if (argc != 2)
    {
        printf("Wrong arg count - only one arg needed!\n");
        return 1;
    }
    char *file_path = (char *)argv[1];

    if (map_file(file_path, &mapped_file) != 0)
        return 1;

    magic_num123(info_buf, mapped_file);
    if (strncmp(ELF_MAGIC, info_buf, 3) != 0)
    {
        printf("File %s is not of elf format!\n", file_path);
        return 1;
    }

    load_elf_header(mapped_file, &elf_header);
    Elf32_Shdr *section_headers = load_section_headers(&elf_header, mapped_file);

    print_sym_tables(mapped_file, &elf_header, section_headers, elf_header.e_shnum);

    free(section_headers);
    return 0;
}