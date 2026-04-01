/*
** EPITECH PROJECT, 2026
** env
** File description:
** minishell2
*/

#include "include/mysh.h"

static void free_copy_on_error(char **copy, int i)
{
    while (i > 0) {
        i--;
        free(copy[i]);
    }
    free(copy);
}

char **env_dup(char **env)
{
    int n = env_count(env);
    char **copy = malloc(sizeof(char *) * (n + 1));
    int i;

    if (!copy)
        return (NULL);
    for (i = 0; i < n; i++) {
        copy[i] = my_strdup(env[i]);
        if (!copy[i]) {
            free_copy_on_error(copy, i);
            return (NULL);
        }
    }
    copy[n] = NULL;
    return (copy);
}

char *env_get(char **env, char *key)
{
    int klen = my_strlen(key);
    int i;

    for (i = 0; env[i]; i++)
        if (my_strncmp(env[i], key, klen) == 0 && env[i][klen] == '=')
            return (env[i] + klen + 1);
    return (NULL);
}

int env_set(shell_t *sh, char *key, char *value)
{
    int klen = my_strlen(key);
    int n = env_count(sh->env);
    char *entry = malloc(klen + my_strlen(value) + 2);
    int i;

    if (!entry)
        return (84);
    my_str_join(entry, key, "=", value);
    for (i = 0; sh->env[i]; i++) {
        if (my_strncmp(sh->env[i], key, klen) == 0 && sh->env[i][klen] == '=') {
            free(sh->env[i]);
            sh->env[i] = entry;
            return (0);
        }
    }
    sh->env = env_append(sh->env, entry, n);
    return (sh->env ? 0 : 84);
}

static void shift_env_left(shell_t *sh, int i, int n)
{
    int j;

    for (j = i; j < n; j++)
        sh->env[j] = sh->env[j + 1];
}

int env_unset(shell_t *sh, char *key)
{
    int klen = my_strlen(key);
    int n = env_count(sh->env);
    int i;

    for (i = 0; sh->env[i]; i++) {
        if (my_strncmp(sh->env[i], key, klen) == 0 && sh->env[i][klen] == '=') {
            free(sh->env[i]);
            shift_env_left(sh, i, n);
            return (0);
        }
    }
    return (0);
}

void free_env(char **env)
{
    int i;

    if (!env)
        return;
    for (i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}
