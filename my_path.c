/*
** EPITECH PROJECT, 2026
** my_path
** File description:
** minishell2 - path string utilities (no forbidden functions)
*/

#include "include/mysh.h"

static void copy_str(char *dst, char *src, int *pos)
{
    int i = 0;

    while (src[i]) {
        dst[*pos] = src[i];
        (*pos)++;
        i++;
    }
}

void my_path_join(char *buf, int size, char *dir, char *name)
{
    int pos = 0;
    int i = 0;

    while (dir[i] && pos < size - 1) {
        buf[pos] = dir[i];
        pos++;
        i++;
    }
    if (pos < size - 1) {
        buf[pos] = '/';
        pos++;
    }
    copy_str(buf, name, &pos);
    if (pos < size)
        buf[pos] = '\0';
}

void my_str_join(char *dst, char *a, char *sep, char *b)
{
    int pos = 0;

    copy_str(dst, a, &pos);
    copy_str(dst, sep, &pos);
    copy_str(dst, b, &pos);
    dst[pos] = '\0';
}
