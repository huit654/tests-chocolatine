/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include "./../include/robot_factory.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (s1 == NULL && s2 != NULL)
        return s2 - s1;
    if (s1 != NULL && s2 == NULL)
        return s2 - s1;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] == s2[i]) {
            i++;
        } else {
            return 1;
        }
    }
    return 0;
}
