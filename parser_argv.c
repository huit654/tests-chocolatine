/*
** EPITECH PROJECT, 2026
** parser_argv
** File description:
** minishell2
*/

#include "include/mysh.h"

void push_word(cmd_t *cmd, char *word, int *argc, int *cap)
{
    int old_size = sizeof(char *) * (*cap);
    int new_size;

    if (*argc + 1 >= *cap) {
        *cap *= 2;
        new_size = sizeof(char *) * (*cap);
        cmd->argv = my_realloc(cmd->argv, old_size, new_size);
    }
    cmd->argv[*argc] = my_strdup(word);
    (*argc)++;
    cmd->argv[*argc] = NULL;
}

int is_redir_type(token_type_t t)
{
    return (t == TOK_REDIR_OUT || t == TOK_REDIR_IN
        || t == TOK_REDIR_APPEND || t == TOK_HEREDOC);
}

int is_end_tok(token_type_t t)
{
    return (t == TOK_EOF || t == TOK_SEMI || t == TOK_PIPE);
}

static void handle_token(token_t **tok, cmd_t *cmd, int *argc, int *cap)
{
    if ((*tok)->type == TOK_WORD) {
        push_word(cmd, (*tok)->value, argc, cap);
        *tok = (*tok)->next;
    } else if (is_redir_type((*tok)->type)) {
        handle_redir_tok(tok, cmd);
    }
}

void collect_tokens(token_t **tok, cmd_t *cmd)
{
    int cap = 8;
    int argc = 0;

    cmd->argv = malloc(sizeof(char *) * cap);
    cmd->argv[0] = NULL;
    while (*tok && !is_end_tok((*tok)->type)) {
        if ((*tok)->type == TOK_WORD || is_redir_type((*tok)->type))
            handle_token(tok, cmd, &argc, &cap);
        else
            break;
    }
}
