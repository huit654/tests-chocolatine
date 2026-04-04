/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#ifndef ROBOT_FACTORY_H
    #define ROBOT_FACTORY_H
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

void print_usage(void);
char *my_strcpy(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_strlen(char const *str);
char *my_strtok(char *av, char *delim);
int check(char c, char *delimiteurs);

#endif
