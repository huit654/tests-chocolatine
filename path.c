/*
** EPITECH PROJECT, 2026
** path
** File description:
** minishell2
*/

#include "include/mysh.h"

char *search_in_path(char *name, char *path_env)
{
    char buf[4096];
    char *copy = my_strdup(path_env);
    char *dir;
    struct stat st;

    dir = strtok(copy, ":");
    while (dir) {
        my_path_join(buf, 4096, dir, name);
        if (stat(buf, &st) == 0 && (st.st_mode & S_IXUSR)) {
            free(copy);
            return (my_strdup(buf));
        }
        dir = strtok(NULL, ":");
    }
    free(copy);
    return (NULL);
}

char *find_binary(char *name, char **env)
{
    char *path_env;
    struct stat st;

    if (!name || !name[0])
        return (NULL);
    if (my_strchr(name, '/')) {
        if (stat(name, &st) == 0 && (st.st_mode & S_IXUSR))
            return (my_strdup(name));
        return (NULL);
    }
    path_env = env_get(env, "PATH");
    if (!path_env)
        return (NULL);
    return (search_in_path(name, path_env));
}
