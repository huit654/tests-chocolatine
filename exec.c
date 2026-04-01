/*
** EPITECH PROJECT, 2026
** exec
** File description:
** minishell2
*/

#include "include/mysh.h"

static int cmd_count(cmd_t *cmd)
{
    int n = 0;

    while (cmd) {
        n++;
        cmd = cmd->next;
    }
    return (n);
}

static int run_single_builtin(cmd_t *cmd, shell_t *sh)
{
    if (cmd->has_error)
        return (1);
    if (apply_redirs(cmd->redirs) < 0)
        return (1);
    return (exec_builtin(cmd, sh));
}

static int fork_all(cmd_t *cmd, shell_t *sh, pipe_ctx_t *ctx, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        if (run_cmd_in_pipe(cmd, sh, ctx, i) < 0) {
            free(ctx->pids);
            return (-1);
        }
        cmd = cmd->next;
    }
    return (0);
}

int exec_pipeline(pipeline_t *pl, shell_t *sh)
{
    cmd_t *cmd = pl->cmds;
    int n = cmd_count(cmd);
    pipe_ctx_t ctx;
    int ret;

    if (n == 1 && cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
        return (run_single_builtin(cmd, sh));
    if (init_pipe_ctx(&ctx, n) < 0)
        return (84);
    if (fork_all(cmd, sh, &ctx, n) < 0)
        return (84);
    ret = wait_all(&ctx);
    free(ctx.pids);
    return (ret);
}

int exec_pipelines(pipeline_t *pl, shell_t *sh)
{
    int ret = 0;

    while (pl) {
        ret = exec_pipeline(pl, sh);
        sh->last_exit = ret;
        pl = pl->next;
    }
    return (ret);
}
