/*
** EPITECH PROJECT, 2026
** exec_child
** File description:
** minishell2
*/

#include "include/mysh.h"

static void wire_fds(int prev_fd, int write_fd)
{
    if (prev_fd != -1) {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (write_fd != -1) {
        dup2(write_fd, STDOUT_FILENO);
        close(write_fd);
    }
}

static void do_exec(cmd_t *cmd, shell_t *sh)
{
    char *bin;
    int ret;

    if (!cmd->argv || !cmd->argv[0])
        exit(0);
    if (is_builtin(cmd->argv[0])) {
        ret = exec_builtin(cmd, sh);
        free_env(sh->env);
        exit(ret);
    }
    bin = find_binary(cmd->argv[0], sh->env);
    if (!bin) {
        write(2, cmd->argv[0], my_strlen(cmd->argv[0]));
        write(2, ": command not found\n", 20);
        exit(127);
    }
    execve(bin, cmd->argv, sh->env);
    perror(bin);
    free(bin);
    exit(84);
}

void child_exec(cmd_t *cmd, shell_t *sh, int prev_fd, int write_fd)
{
    if (cmd->has_error)
        exit(1);
    wire_fds(prev_fd, write_fd);
    if (apply_redirs(cmd->redirs) < 0)
        exit(1);
    do_exec(cmd, sh);
}
