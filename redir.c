/*
** EPITECH PROJECT, 2026
** redir
** File description:
** minishell2
*/

#include "include/mysh.h"

int apply_out(char *file, int flags)
{
    int fd = open(file, flags, 0644);

    if (fd < 0) {
        perror(file);
        return (-1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

int apply_in(char *file)
{
    int fd = open(file, O_RDONLY);

    if (fd < 0) {
        perror(file);
        return (-1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

static int apply_heredoc_fd(int fd)
{
    if (fd < 0)
        return (-1);
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

int apply_one(redir_t *r)
{
    if (r->type == TOK_REDIR_OUT)
        return (apply_out(r->file, O_WRONLY | O_CREAT | O_TRUNC));
    if (r->type == TOK_REDIR_APPEND)
        return (apply_out(r->file, O_WRONLY | O_CREAT | O_APPEND));
    if (r->type == TOK_REDIR_IN)
        return (apply_in(r->file));
    if (r->type == TOK_HEREDOC)
        return (apply_heredoc_fd(r->fd));
    return (0);
}

int apply_redirs(redir_t *r)
{
    while (r) {
        if (apply_one(r) < 0)
            return (-1);
        r = r->next;
    }
    return (0);
}
