/*
** EPITECH PROJECT, 2026
** exec_pipe
** File description:
** minishell2
*/

#include "include/mysh.h"

int init_pipe_ctx(pipe_ctx_t *ctx, int n)
{
    ctx->pids = malloc(sizeof(pid_t) * n);
    ctx->n = n;
    ctx->prev_fd = -1;
    ctx->pfd[0] = -1;
    ctx->pfd[1] = -1;
    return (ctx->pids ? 0 : -1);
}

int open_pipe_if_needed(pipe_ctx_t *ctx, int i)
{
    if (i < ctx->n - 1) {
        if (pipe(ctx->pfd) < 0) {
            perror("mysh: pipe");
            return (-1);
        }
    } else {
        ctx->pfd[0] = -1;
        ctx->pfd[1] = -1;
    }
    return (0);
}

void close_parent_fds(pipe_ctx_t *ctx)
{
    if (ctx->prev_fd != -1)
        close(ctx->prev_fd);
    if (ctx->pfd[1] != -1)
        close(ctx->pfd[1]);
    ctx->prev_fd = ctx->pfd[0];
}

int run_cmd_in_pipe(cmd_t *cmd, shell_t *sh, pipe_ctx_t *ctx, int i)
{
    if (open_pipe_if_needed(ctx, i) < 0)
        return (-1);
    ctx->pids[i] = fork();
    if (ctx->pids[i] < 0) {
        perror("mysh: fork");
        return (-1);
    }
    if (ctx->pids[i] == 0) {
        if (ctx->pfd[0] != -1)
            close(ctx->pfd[0]);
        child_exec(cmd, sh, ctx->prev_fd, ctx->pfd[1]);
    }
    close_parent_fds(ctx);
    return (0);
}

static int get_exit_status(int status)
{
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (0);
}

int wait_all(pipe_ctx_t *ctx)
{
    int status;
    int last = 0;
    int i;

    for (i = 0; i < ctx->n; i++) {
        waitpid(ctx->pids[i], &status, 0);
        if (i == ctx->n - 1)
            last = get_exit_status(status);
    }
    return (last);
}
