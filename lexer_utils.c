/*
** EPITECH PROJECT, 2026
** lexer_utils
** File description:
** minishell2
*/

#include "include/mysh.h"

token_t *new_token(token_type_t type, char *value)
{
    token_t *tok = malloc(sizeof(token_t));

    if (!tok)
        return (NULL);
    tok->type = type;
    tok->value = value ? my_strdup(value) : NULL;
    tok->next = NULL;
    return (tok);
}

void append_token(token_t **head, token_t **tail, token_t *tok)
{
    if (!*head) {
        *head = tok;
        *tail = tok;
    } else {
        (*tail)->next = tok;
        *tail = tok;
    }
}

char *read_quoted(char *line, int *pos, char quote)
{
    int start;
    int len;
    char *res;
    int i;

    (*pos)++;
    start = *pos;
    while (line[*pos] && line[*pos] != quote)
        (*pos)++;
    len = *pos - start;
    res = malloc(len + 1);
    if (!res)
        return (NULL);
    for (i = 0; i < len; i++)
        res[i] = line[start + i];
    res[len] = '\0';
    if (line[*pos] == quote)
        (*pos)++;
    return (res);
}

void word_append_quoted(char *buf, int *bi, char *line, int *pos)
{
    char *part;
    int plen;
    int i;

    part = read_quoted(line, pos, line[*pos]);
    if (!part)
        return;
    plen = my_strlen(part);
    if (*bi + plen < 4095) {
        for (i = 0; i < plen; i++)
            buf[*bi + i] = part[i];
        *bi += plen;
    }
    free(part);
}

char *read_word(char *line, int *pos)
{
    char buf[4096];
    int bi = 0;

    while (line[*pos] && line[*pos] != ' ' && line[*pos] != '\t'
        && line[*pos] != ';' && line[*pos] != '|'
        && line[*pos] != '>' && line[*pos] != '<') {
        if (line[*pos] == '\'' || line[*pos] == '"')
            word_append_quoted(buf, &bi, line, pos);
        else {
            buf[bi] = line[*pos];
            bi++;
            (*pos)++;
        }
    }
    buf[bi] = '\0';
    return (my_strdup(buf));
}
