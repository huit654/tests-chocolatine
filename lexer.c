/*
** EPITECH PROJECT, 2026
** lexer
** File description:
** minishell2
*/

#include "include/mysh.h"

static token_t *lex_double(int *i, token_type_t type, char *val)
{
    token_t *tok = new_token(type, val);

    (*i) += 2;
    return (tok);
}

static token_t *lex_single(int *i, token_type_t type, char *val)
{
    token_t *tok = new_token(type, val);

    (*i)++;
    return (tok);
}

static token_t *lex_angle(char *line, int *i)
{
    if (line[*i + 1] == '>')
        return (lex_double(i, TOK_REDIR_APPEND, ">>"));
    return (lex_single(i, TOK_REDIR_OUT, ">"));
}

static token_t *lex_angle_left(char *line, int *i)
{
    if (line[*i + 1] == '<')
        return (lex_double(i, TOK_HEREDOC, "<<"));
    return (lex_single(i, TOK_REDIR_IN, "<"));
}

static token_t *lex_get_tok(char *line, int *i)
{
    if (line[*i] == ';')
        return (lex_single(i, TOK_SEMI, ";"));
    if (line[*i] == '|')
        return (lex_single(i, TOK_PIPE, "|"));
    if (line[*i] == '>')
        return (lex_angle(line, i));
    return (lex_angle_left(line, i));
}

void lex_operator(char *line, int *i, token_t **h, token_t **t)
{
    append_token(h, t, lex_get_tok(line, i));
}

int is_operator(char c)
{
    return (c == ';' || c == '|' || c == '>' || c == '<');
}

void lex_word(char *line, int *i, token_t **h, token_t **t)
{
    char *word = read_word(line, i);
    token_t *tok;

    if (!word)
        return;
    tok = new_token(TOK_WORD, word);
    free(word);
    append_token(h, t, tok);
}

token_t *lexer(char *line)
{
    token_t *head = NULL;
    token_t *tail = NULL;
    int i = 0;

    while (line[i]) {
        if (line[i] == ' ' || line[i] == '\t') {
            i++;
            continue;
        }
        if (is_operator(line[i]))
            lex_operator(line, &i, &head, &tail);
        else
            lex_word(line, &i, &head, &tail);
    }
    append_token(&head, &tail, new_token(TOK_EOF, NULL));
    return (head);
}

void free_tokens(token_t *tok)
{
    token_t *next;

    while (tok) {
        next = tok->next;
        free(tok->value);
        free(tok);
        tok = next;
    }
}
