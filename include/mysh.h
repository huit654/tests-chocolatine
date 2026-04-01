/*
** EPITECH PROJECT, 2025
** include
** File description:
** minishell2
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <dirent.h>
    #include <signal.h>
    #include <fcntl.h>

typedef enum e_token_type {
    TOK_WORD,
    TOK_SEMI,
    TOK_PIPE,
    TOK_REDIR_OUT,
    TOK_REDIR_IN,
    TOK_REDIR_APPEND,
    TOK_HEREDOC,
    TOK_EOF
} token_type_t;

typedef struct s_token {
    token_type_t type;
    char *value;
    struct s_token *next;
} token_t;

typedef struct s_redir {
    token_type_t type;
    char *file;
    int fd;
    struct s_redir *next;
} redir_t;

typedef struct s_cmd {
    char **argv;
    redir_t *redirs;
    int has_error;
    struct s_cmd *next;
} cmd_t;

typedef struct s_pipeline {
    cmd_t *cmds;
    struct s_pipeline *next;
} pipeline_t;

typedef struct s_shell {
    char **env;
    int last_exit;
    int should_exit;
} shell_t;

typedef struct s_pipe_ctx {
    pid_t *pids;
    int n;
    int prev_fd;
    int pfd[2];
} pipe_ctx_t;

token_t *lexer(char *line);
void free_tokens(token_t *tok);
token_t *new_token(token_type_t type, char *value);
void append_token(token_t **head, token_t **tail, token_t *tok);
char *read_quoted(char *line, int *pos, char quote);
char *read_word(char *line, int *pos);
pipeline_t *parse(token_t **tok);
cmd_t *parse_command(token_t **tok);
void add_redir(cmd_t *cmd, token_type_t type, char *file);
void handle_redir_tok(token_t **tok, cmd_t *cmd);
void push_word(cmd_t *cmd, char *word, int *argc, int *cap);
void collect_tokens(token_t **tok, cmd_t *cmd);
void free_pipelines(pipeline_t *pl);
void free_cmd(cmd_t *cmd);
int exec_pipelines(pipeline_t *pl, shell_t *sh);
int exec_pipeline(pipeline_t *pl, shell_t *sh);
void child_exec(cmd_t *cmd, shell_t *sh, int prev_fd, int write_fd);
int init_pipe_ctx(pipe_ctx_t *ctx, int n);
int run_cmd_in_pipe(cmd_t *cmd, shell_t *sh, pipe_ctx_t *ctx, int i);
int wait_all(pipe_ctx_t *ctx);
int is_builtin(char *name);
int exec_builtin(cmd_t *cmd, shell_t *sh);
int builtin_cd(cmd_t *cmd, shell_t *sh);
int builtin_env(shell_t *sh);
int builtin_setenv(cmd_t *cmd, shell_t *sh);
int builtin_unsetenv(cmd_t *cmd, shell_t *sh);
char **env_dup(char **env);
void free_env(char **env);
char *env_get(char **env, char *key);
int env_set(shell_t *sh, char *key, char *value);
int env_unset(shell_t *sh, char *key);
int env_count(char **env);
char **env_append(char **env, char *entry, int n);
int apply_redirs(redir_t *redirs);
int do_heredoc(char *delim);
char *find_binary(char *name, char **env);
char *search_in_path(char *name, char *path_env);
int shell_loop(shell_t *sh);
int my_strlen(char *s);
int my_strcmp(char *a, char *b);
int my_strncmp(char *a, char *b, int n);
char *my_strdup(char *s);
char *my_strchr(char *s, char c);
void my_memcpy(char *dst, char *src, int n);
void *my_realloc(void *ptr, int old_size, int new_size);
int my_atoi(char *s);
void my_path_join(char *buf, int size, char *dir, char *name);
void my_str_join(char *dst, char *a, char *sep, char *b);

#endif
