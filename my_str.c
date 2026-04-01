/*
** EPITECH PROJECT, 2026
** my_str
** File description:
** minishell2 - string utilities (no forbidden functions)
*/

#include "include/mysh.h"

int my_strlen(char *s)
{
    int i = 0;

    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

int my_strcmp(char *a, char *b)
{
    int i = 0;

    while (a[i] && b[i] && a[i] == b[i])
        i++;
    return ((unsigned char)a[i] - (unsigned char)b[i]);
}

int my_strncmp(char *a, char *b, int n)
{
    int i = 0;

    while (i < n && a[i] && b[i] && a[i] == b[i])
        i++;
    if (i == n)
        return (0);
    return ((unsigned char)a[i] - (unsigned char)b[i]);
}

char *my_strdup(char *s)
{
    int len = my_strlen(s);
    char *copy = malloc(len + 1);
    int i;

    if (!copy)
        return (NULL);
    for (i = 0; i <= len; i++)
        copy[i] = s[i];
    return (copy);
}

char *my_strchr(char *s, char c)
{
    int i;

    for (i = 0; s[i]; i++)
        if (s[i] == c)
            return (s + i);
    return (NULL);
}
