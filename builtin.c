/*
** EPITECH PROJECT, 2026
** builtin
** File description:
** minishell2
*/

#include "include/mysh.h"

int is_builtin(char *name)
{
    if (!name)
        return (0);
    return (my_strcmp(name, "cd") == 0
        || my_strcmp(name, "env") == 0
        || my_strcmp(name, "setenv") == 0
        || my_strcmp(name, "unsetenv") == 0
        || my_strcmp(name, "exit") == 0);
}

static void builtin_exit(cmd_t *cmd, shell_t *sh)
{
    if (cmd->argv[1])
        exit(my_atoi(cmd->argv[1]));
    exit(sh->last_exit);
}

int exec_builtin(cmd_t *cmd, shell_t *sh)
{
    if (my_strcmp(cmd->argv[0], "cd") == 0)
        return (builtin_cd(cmd, sh));
    if (my_strcmp(cmd->argv[0], "env") == 0)
        return (builtin_env(sh));
    if (my_strcmp(cmd->argv[0], "setenv") == 0)
        return (builtin_setenv(cmd, sh));
    if (my_strcmp(cmd->argv[0], "unsetenv") == 0)
        return (builtin_unsetenv(cmd, sh));
    if (my_strcmp(cmd->argv[0], "exit") == 0)
        builtin_exit(cmd, sh);
    return (84);
}
