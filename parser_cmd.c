/*
** EPITECH PROJECT, 2026
** parser_cmd
** File description:
** minishell2
*/

#include "include/mysh.h"

void add_redir(cmd_t *cmd, token_type_t type, char *file)
{
    redir_t *r = malloc(sizeof(redir_t));
    redir_t *cur;

    if (!r)
        return;
    r->type = type;
    r->file = my_strdup(file);
    r->fd = -1;
    if (type == TOK_HEREDOC)
        r->fd = do_heredoc(file);
    r->next = NULL;
    if (!cmd->redirs) {
        cmd->redirs = r;
        return;
    }
    cur = cmd->redirs;
    while (cur->next)
        cur = cur->next;
    cur->next = r;
}

void handle_redir_tok(token_t **tok, cmd_t *cmd)
{
    token_type_t rtype = (*tok)->type;

    *tok = (*tok)->next;
    if (*tok && (*tok)->type == TOK_WORD) {
        add_redir(cmd, rtype, (*tok)->value);
        *tok = (*tok)->next;
    } else {
        write(2, "mysh: syntax error near redirection\n", 36);
        cmd->has_error = 1;
    }
}

static void free_argv(char **argv)
{
    int i;

    for (i = 0; argv[i]; i++)
        free(argv[i]);
    free(argv);
}

cmd_t *parse_command(token_t **tok)
{
    cmd_t *cmd = malloc(sizeof(cmd_t));

    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->redirs = NULL;
    cmd->next = NULL;
    cmd->has_error = 0;
    collect_tokens(tok, cmd);
    if ((!cmd->argv || !cmd->argv[0]) && !cmd->redirs) {
        if (cmd->argv)
            free_argv(cmd->argv);
        free(cmd);
        return (NULL);
    }
    return (cmd);
}
