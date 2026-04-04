/*
** EPITECH PROJECT, 2025
** strlen
** File description:
** strlen
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

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        i++;
    }
    return i;
}
