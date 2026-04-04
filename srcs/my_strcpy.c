/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include <stdio.h>
#include <dirent.h>
#include "./../include/robot_factory.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *my_strcpy(char *dest, char const *src)
{
    int n = 0;
    int l = (2 * n) + 2;
    int len = my_strlen(dest) + my_strlen(src) + 2;

    while (src[n] != '\0') {
        dest[n] = src[n];
        n++;
    }
    dest[n] = '\0';
    return dest;
}
