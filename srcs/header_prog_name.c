/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "./../include/robot_factory.h"
#include "./../G-CPE-200_op/op.h"

/*char *prog_name(char *rd, header_t *ptr)
{
    FILE *stream = fopen(rd, "w+");
    char *line = NULL;
    size_t len = 0;

    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fwrite(buffer, sizeof(*buffer), ARRAY_SIZE(buffer), fp);
    fclose(stream);
    return ptr->prog_name;
}

char *comment(op_t *header, char *rd, header_t *ptr)
{
    FILE *stream = fopen(rd, "r");
    char *line = NULL;
    size_t len = 0;

    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fwrite(buffer, sizeof(*buffer), ARRAY_SIZE(buffer), fp);
    fclose(stream);
    return ptr->comment;
}
*/
int my_char_isalpha(char c)
{
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == ' ' || c == 39) {
        return 0;
    } else {
        return -1;
    }
    return 0;
}
