#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "examine.h"


int calc_file_size(int fd)
{
    struct stat st;
    fstat(fd, &st);
    return st.st_size;
}

void load_elf_header(char *elf_mapped, Elf32_Ehdr *elf_header)
{
    (*elf_header) = *(Elf32_Ehdr *)elf_mapped;
}

/* Fill buff with Bytes 1,2,3 of the magic number (in ASCII). 
Henceforth, you should check that the number is consistent with an ELF file, and refuse to continue if it is not.
*/
void magic_num123(char *buf, char *mapped_file)
{
    strncpy(buf, mapped_file + 1, 3);
    buf[3] = 0;
}

/* Print the data encoding scheme of the object file which could be - 
    ELFDATANONE   Unknown data format
    ELFDATA2LSB   Two's complement, little-endian
    ELFDATA2MSB   Two's complement, big-endian                          */
void print_data_encoding_format(Elf32_Ehdr *elf_header)
{
    switch (elf_header->e_ident[5])
    {
    case ELFDATA2LSB:
        printf("Data: Two's complement, little-endian\n");
        break;

    case ELFDATA2MSB:
        printf("Data: Two's complement, big-endian\n");
        break;

    default:
        printf("Data: Unknown data format\n");
    }
}

/*Print entry point (hexadecimal address). */
void print_entry_point(Elf32_Ehdr *elf_header)
{
    printf("Entry point: 0x%x\n", elf_header->e_entry);
}

/* The file offset in which the section header table resides. */
void print_section_h_offset(Elf32_Ehdr *elf_header)
{
    printf("Start of section headers: %d (bytes into file)\n", elf_header->e_shentsize);
}

/* The number of section header entries. */
void print_section_h_num(Elf32_Ehdr *elf_header)
{
    printf("Number of section headers: %d\n", elf_header->e_shnum);
}

Elf32_Shdr *load_section_headers(Elf32_Ehdr *elf_header, char *mapped_file)
{
    Elf32_Shdr *sectin_headers = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr) * elf_header->e_shnum);

    int i;
    int cur_offset;
    for (i = 0; i < elf_header->e_shnum; i++)
    {
        cur_offset = elf_header->e_shoff + i * sizeof(Elf32_Shdr);
        sectin_headers[i] = *(Elf32_Shdr *)(mapped_file + cur_offset);
    }

    return sectin_headers;
}

/* The size of each section header entry. */
void print_section_header_sizes(Elf32_Shdr *section_headers, int section_headers_num)
{
    int i;
    for (i = 0; i < section_headers_num; i++)
        printf("Section #[%d] size: [%d Bytes]\n", i, section_headers[i].sh_size);
}

/* The index of the shstrtab in the section header. */
void print_shstrtab_index(Elf32_Ehdr *elf_header)
{
    printf("Section header string table index: %d\n", elf_header->e_shstrndx);
}


int map_file(char *file_path, char **mapped_file_p)
{
    int fd = open(file_path, O_RDONLY, 0);
    if (fd == -1)
    {
        printf("Failed to open %s\n", file_path);
        return 1;
    }

    int file_size = calc_file_size(fd);
    printf("File size: [%d Bytes]\n", file_size);
    (*mapped_file_p) = (char *)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (*mapped_file_p == MAP_FAILED)
    {
        printf("Failed to Map %s\n", file_path);
        return 1;
    }

    return 0;
}

/*
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
    printf("Magic: [%s]\n", info_buf);
    if (strncmp(ELF_MAGIC, info_buf, 3) != 0)
    {
        printf("File %s is not of elf format!\n", file_path);
        return 1;
    }

    load_elf_header(mapped_file, &elf_header);

    print_data_encoding_format(&elf_header);
    print_entry_point(&elf_header);
    print_section_h_offset(&elf_header);
    print_section_h_num(&elf_header);

    Elf32_Shdr *section_headers = load_section_headers(&elf_header, mapped_file);
    print_section_header_sizes(section_headers, elf_header.e_shnum);
    print_shstrtab_index(&elf_header);

    free(section_headers);
    return 0;
}
*/