#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "task0/examine.h"

#define SEC_P_FORMAT "[%2d] %20s %15x %10d %10d \n"
#define SEC_HEAD "[%2s] %20s %15s %10s %10s \n", "ID", "Name", "Address", "Offset", "Size"

/* [index] section_name section_address section_offset section_size */
void print_sctions(char *mapped_file, Elf32_Ehdr *elf_header,
                   Elf32_Shdr *section_headers, int section_headers_num)
{
    char *section_str_table = mapped_file + section_headers[elf_header->e_shstrndx].sh_offset;

    printf(SEC_HEAD);

    int i;
    for (i = 0; i < section_headers_num; i++)
    {
        printf(SEC_P_FORMAT,
               i,
               section_str_table + section_headers[i].sh_name,
               section_headers[i].sh_addr,
               section_headers[i].sh_offset,
               section_headers[i].sh_size);
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

    print_sctions(mapped_file, &elf_header, section_headers, elf_header.e_shnum);

    free(section_headers);
    return 0;
}