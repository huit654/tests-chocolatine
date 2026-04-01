/*
** EPITECH PROJECT, 2026
** redir_heredoc
** File description:
** minishell2
*/

#include "include/mysh.h"

static void write_heredoc_line(int wfd, char *line, ssize_t rd)
{
    line[rd - 1] = '\n';
    write(wfd, line, rd);
}

int read_heredoc_lines(int wfd, char *delim)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t rd;

    while (1) {
        if (isatty(STDIN_FILENO))
            write(1, "> ", 2);
        rd = getline(&line, &n, stdin);
        if (rd < 0)
            break;
        line[rd - 1] = '\0';
        if (my_strcmp(line, delim) == 0)
            break;
        write_heredoc_line(wfd, line, rd);
    }
    free(line);
    return (0);
}

int do_heredoc(char *delim)
{
    int pfd[2];

    if (pipe(pfd) < 0) {
        perror("mysh: pipe");
        return (-1);
    }
    read_heredoc_lines(pfd[1], delim);
    close(pfd[1]);
    return (pfd[0]);
}
