/*
** EPITECH PROJECT, 2026
** main
** File description:
** minishell2
*/

#include "include/mysh.h"

void print_prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(1, "$> ", 3);
}

void process_line(char *line, shell_t *sh)
{
    token_t *tokens;
    token_t *ptr;
    pipeline_t *pipelines;

    tokens = lexer(line);
    if (!tokens)
        return;
    ptr = tokens;
    pipelines = parse(&ptr);
    if (pipelines) {
        sh->last_exit = exec_pipelines(pipelines, sh);
        free_pipelines(pipelines);
    }
    free_tokens(tokens);
}

int shell_loop(shell_t *sh)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t rd;

    print_prompt();
    rd = getline(&line, &n, stdin);
    while (rd != -1) {
        if (rd > 0 && line[rd - 1] == '\n')
            line[rd - 1] = '\0';
        if (line[0] != '\0')
            process_line(line, sh);
        print_prompt();
        rd = getline(&line, &n, stdin);
    }
    free(line);
    return (sh->last_exit);
}

int main(int argc, char **argv, char **envp)
{
    shell_t sh;

    (void)argc;
    (void)argv;
    sh.env = env_dup(envp);
    if (!sh.env) {
        write(2, "mysh: env init failed\n", 22);
        return (84);
    }
    sh.last_exit = 0;
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    return (shell_loop(&sh));
}
