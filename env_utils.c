/*
** EPITECH PROJECT, 2026
** env_utils
** File description:
** minishell2
*/

#include "include/mysh.h"

int env_count(char **env)
{
    int i = 0;

    while (env[i])
        i++;
    return (i);
}

char **env_append(char **env, char *entry, int n)
{
    char **newenv;
    int i;

    newenv = malloc(sizeof(char *) * (n + 2));
    if (!newenv)
        return (NULL);
    for (i = 0; i < n; i++)
        newenv[i] = env[i];
    newenv[n] = entry;
    newenv[n + 1] = NULL;
    free(env);
    return (newenv);
}
