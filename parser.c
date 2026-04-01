/*
** EPITECH PROJECT, 2026
** parser
** File description:
** minishell2
*/

#include "include/mysh.h"

static pipeline_t *new_pipeline(void)
{
    pipeline_t *pl = malloc(sizeof(pipeline_t));

    if (!pl)
        return (NULL);
    pl->cmds = NULL;
    pl->next = NULL;
    return (pl);
}

static void pipeline_push(pipeline_t *pl, cmd_t *cmd, cmd_t **tail)
{
    if (!pl->cmds) {
        pl->cmds = cmd;
        *tail = cmd;
    } else {
        (*tail)->next = cmd;
        *tail = cmd;
    }
}

static pipeline_t *parse_pipeline(token_t **tok)
{
    pipeline_t *pl = new_pipeline();
    cmd_t *tail = NULL;
    cmd_t *cmd;

    if (!pl)
        return (NULL);
    while (1) {
        cmd = parse_command(tok);
        if (cmd)
            pipeline_push(pl, cmd, &tail);
        if (!*tok || (*tok)->type != TOK_PIPE)
            break;
        *tok = (*tok)->next;
    }
    if (!pl->cmds) {
        free(pl);
        return (NULL);
    }
    return (pl);
}

static void program_push(pipeline_t **head, pipeline_t **tail, pipeline_t *pl)
{
    if (!*head) {
        *head = pl;
        *tail = pl;
    } else {
        (*tail)->next = pl;
        *tail = pl;
    }
}

pipeline_t *parse(token_t **tok)
{
    pipeline_t *head = NULL;
    pipeline_t *tail = NULL;
    pipeline_t *pl;

    while (*tok && (*tok)->type != TOK_EOF) {
        if ((*tok)->type == TOK_SEMI) {
            *tok = (*tok)->next;
            continue;
        }
        pl = parse_pipeline(tok);
        if (pl)
            program_push(&head, &tail, pl);
        if (*tok && (*tok)->type == TOK_SEMI)
            *tok = (*tok)->next;
    }
    return (head);
}
