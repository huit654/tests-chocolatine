/*
** EPITECH PROJECT, 2026
** builtin_cd
** File description:
** minishell2
*/

#include "include/mysh.h"

static char *resolve_target(cmd_t *cmd, shell_t *sh)
{
    if (!cmd->argv[1])
        return (env_get(sh->env, "HOME"));
    if (cmd->argv[1][0] == '-' && !cmd->argv[1][1])
        return (env_get(sh->env, "OLDPWD"));
    return (cmd->argv[1]);
}

static void update_pwd(shell_t *sh, char *old_pwd)
{
    char cwd[4096];

    if (old_pwd)
        env_set(sh, "OLDPWD", old_pwd);
    if (getcwd(cwd, sizeof(cwd)))
        env_set(sh, "PWD", cwd);
}

int builtin_cd(cmd_t *cmd, shell_t *sh)
{
    char *target;
    char old[4096];
    char *saved;

    target = resolve_target(cmd, sh);
    if (!target) {
        write(2, "cd: target not found\n", 21);
        return (1);
    }
    saved = getcwd(old, sizeof(old)) ? old : NULL;
    if (chdir(target) < 0) {
        perror(target);
        return (1);
    }
    update_pwd(sh, saved);
    return (0);
}
