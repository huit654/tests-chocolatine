/*
** EPITECH PROJECT, 2025
** my_strtok
** File description:
** Tokenizes a string by delimiter characters
*/

#include <stddef.h>

static int is_delim(char c, char const *delimiters)
{
    int j = 0;

    while (delimiters[j] != '\0') {
        if (c == delimiters[j])
            return 1;
        j++;
    }
    return 0;
}

static char *skip_and_end(char **saved, char const *delimiters)
{
    char *start;
    int i = 0;

    while (**saved != '\0' && is_delim(**saved, delimiters))
        (*saved)++;
    if (**saved == '\0')
        return NULL;
    start = *saved;
    while ((*saved)[i] != '\0' && !is_delim((*saved)[i], delimiters))
        i++;
    if ((*saved)[i] != '\0') {
        (*saved)[i] = '\0';
        *saved = &(*saved)[i + 1];
    } else {
        *saved = NULL;
    }
    return start;
}

char *my_strtok(char *str, char const *delimiters)
{
    static char *saved = NULL;

    if (str != NULL)
        saved = str;
    if (saved == NULL || *saved == '\0')
        return NULL;
    return skip_and_end(&saved, delimiters);
}
