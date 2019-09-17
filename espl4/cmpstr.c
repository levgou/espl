
/* 
	Compare 2 strings in a lexicographical way
	Assumption: both strings end with \0
*/
int cmpstr(char *str1, char *str2)
{

    while (*str1 && *str2)
    {
        if (*str1 < *str2)
            return 2;
        else if (*str1 > *str2)
            return 1;

        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 == '\0')
        return 0;
    else if (*str1 == '\0')
        return 2;
    else
        return 1;
}
