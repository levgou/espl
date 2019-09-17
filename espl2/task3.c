/* Menu interface to previous tasks

Usage example:

#> menu
Please enter a string (0<size<=10):
La
Please choose printer type:
0) echo printer
1) ascii printer
2) binary printer (least to most)
3) binary printer (most to least)
4) bitwise or

Option: 1
76 97
Option: 0
L a 
Option: DONE.

*/

#include <stdio.h>
#include <stdlib.h>

void echo_printer(char c);
void binary_printer(char c);
void binary_printerML(char c);
void ascii_printer(char c);

void string_printer(char *array, void (*f)(char));

void bitwise_or(char *s);
void string_reader(char *s);

typedef struct FuncDesc
{
    char *name;
    void (*func)(char);
} FuncDesc;

FuncDesc FUNCTIONS[] = {
    {.name = "echo printer", .func = echo_printer},
    {.name = "ascii printer", .func = ascii_printer},
    {.name = "binary printer (least to most)", .func = binary_printer},
    {.name = "binary printer (most to least)", .func = binary_printerML},
};
size_t FUNC_NUM = sizeof(FUNCTIONS) / sizeof(FuncDesc);

void printMenu()
{
    char *menuTemplate = "%d) %s\n";
    size_t i = 0;

    printf("Please choose printer type:\n");
    for (; i < FUNC_NUM; i++)
        printf(menuTemplate, i, FUNCTIONS[i].name);

    printf(menuTemplate, FUNC_NUM, "bitwise_or\n");
}

int getUserChoise()
{
    char printerChoise[3];
    size_t printerNum;

    printf("Option: ");
    string_reader(printerChoise);

    printerNum = atoi(printerChoise);
    return printerNum;
}

void printWithUserChoise(size_t userChoise, char *str)
{
    if (userChoise < FUNC_NUM)
    {
        string_printer(str, FUNCTIONS[userChoise].func);
    }
    else
    {
        bitwise_or(str);
    }
}

int main(int argc, char const *argv[])
{
    char str[11];
    size_t printerNum;

    printf("Please enter a string (0<size<=10):\n");
    string_reader(str);

    printMenu();

    while ((printerNum = getUserChoise()) != -1)
    {
        printWithUserChoise(printerNum, str);
    }

    printf("DONE.\n");

    return 0;
}
