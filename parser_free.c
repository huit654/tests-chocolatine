/*
** EPITECH PROJECT, 2026
** parser_free
** File description:
** minishell2
*/

#include "include/mysh.h"

static void free_redir(redir_t *r)
{
    redir_t *next;

    while (r) {
        next = r->next;
        free(r->file);
        if (r->type == TOK_HEREDOC && r->fd >= 0)
            close(r->fd);
        free(r);
        r = next;
    }
}

void free_cmd(cmd_t *cmd)
{
    int i;

    if (!cmd)
        return;
    if (cmd->argv) {
        for (i = 0; cmd->argv[i]; i++)
            free(cmd->argv[i]);
        free(cmd->argv);
    }
    free_redir(cmd->redirs);
    free(cmd);
}

static void free_cmd_chain(cmd_t *cmd)
{
    cmd_t *next;

    while (cmd) {
        next = cmd->next;
        free_cmd(cmd);
        cmd = next;
    }
}

void free_pipelines(pipeline_t *pl)
{
    pipeline_t *next;

    while (pl) {
        next = pl->next;
        free_cmd_chain(pl->cmds);
        free(pl);
        pl = next;
    }
}
