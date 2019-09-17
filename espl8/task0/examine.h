#include <elf.h>

#define ELF_MAGIC "ELF"

int map_file(char *file_path, char **mapped_file_p);
void magic_num123(char *buf, char *mapped_file);
void load_elf_header(char *elf_mapped, Elf32_Ehdr *elf_header);
Elf32_Shdr *load_section_headers(Elf32_Ehdr *elf_header, char *mapped_file);
