/*
** EPITECH PROJECT, 2026
** my_mem
** File description:
** minishell2 - memory utilities (no forbidden functions)
*/

#include "include/mysh.h"

void my_memcpy(char *dst, char *src, int n)
{
    int i;

    for (i = 0; i < n; i++)
        dst[i] = src[i];
}

void *my_realloc(void *ptr, int old_size, int new_size)
{
    char *new_ptr = malloc(new_size);
    int copy_size;

    if (!new_ptr)
        return (NULL);
    if (ptr) {
        copy_size = old_size < new_size ? old_size : new_size;
        my_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }
    return (new_ptr);
}

int my_atoi(char *s)
{
    int i = 0;
    int sign = 1;
    int result = 0;

    while (s[i] == ' ' || s[i] == '\t')
        i++;
    if (s[i] == '-') {
        sign = -1;
        i++;
    } else if (s[i] == '+') {
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9') {
        result = result * 10 + (s[i] - '0');
        i++;
    }
    return (result * sign);
}
