/*
** EPITECH PROJECT, 2026
** builtin_env
** File description:
** minishell2
*/

#include "include/mysh.h"

int builtin_env(shell_t *sh)
{
    int i;

    for (i = 0; sh->env[i]; i++) {
        write(1, sh->env[i], my_strlen(sh->env[i]));
        write(1, "\n", 1);
    }
    return (0);
}

int builtin_setenv(cmd_t *cmd, shell_t *sh)
{
    if (!cmd->argv[1]) {
        write(2, "setenv: missing variable name\n", 30);
        return (84);
    }
    return (env_set(sh, cmd->argv[1], cmd->argv[2] ? cmd->argv[2] : ""));
}

int builtin_unsetenv(cmd_t *cmd, shell_t *sh)
{
    if (!cmd->argv[1]) {
        write(2, "unsetenv: missing variable name\n", 32);
        return (84);
    }
    return (env_unset(sh, cmd->argv[1]));
}
