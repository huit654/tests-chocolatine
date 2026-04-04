/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "./../include/robot_factory.h"
#include "./../G-CPE-200_op/op.h"

int check(char c, char *delimiteurs)
{
    int i = 0;

    for (; delimiteurs[i] != '\0'; i++) {
        if (delimiteurs[i] == c)
            return 1;
    }
    return 0;
}

char *clean_str(char *av, char *delims)
{
    int i = 0;
    int j = 0;
    char *tab = malloc(sizeof(char) * (strlen(av) + 1));

    for (int i = 0; av[i] != '\0'; i++) {
        if (!check(av[i], delims)) {
            tab[j] = av[i];
            j++;
        } else if (!check(av[i + 1], delims)) {
            tab[j] = ' ';
            j++;
        }
    }
    tab[j] = '\0';
    return tab;
}

char *clean_the_string(char *av)
{
    int i = 0;
    int j = 0;
    char *tab = malloc(sizeof(char) * (strlen(av) + 1));

    for (int i = 0; av[i] != '\0'; i++) {
        if (my_char_isalpha(av[i]) == 0) {
            tab[j] = av[i];
            j++;
        }
    }
    tab[j] = '\0';
    return tab;
}

char *get_comment(header_t *ptr, char *rd)
{
    FILE *stream = fopen(rd, "r");
    char *line = NULL;
    size_t len = 0;
    char *p = NULL;

    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    while (getline(&line, &len, stream) != -1) {
        p = strtok(line, " \t");
        if (my_strcmp(clean_str(p, " \t"), ".comment") == 0) {
            my_strcpy(ptr->comment, clean_the_string((strtok(NULL, "\t"))));
        }
    }
    free(line);
    fclose(stream);
    return ptr->comment;
}

char *get_name(header_t *ptr, char *rd)
{
    FILE *stream = fopen(rd, "r");
    char *line = NULL;
    size_t len = 0;
    char *p = NULL;

    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    while (getline(&line, &len, stream) != -1) {
        p = strtok(line, " \t");
        if (my_strcmp(clean_str(p, " \t"), ".name") == 0) {
            my_strcpy(ptr->prog_name, clean_the_string((strtok(NULL, "\t"))));
        }
    }
    free(line);
    fclose(stream);
    return ptr->prog_name;
}
