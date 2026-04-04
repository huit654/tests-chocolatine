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

void print_usage(void)
{
    printf("USAGE\n");
    printf("./robot-factory file_name[.s]\n");
    printf("DESCRIPTION\n");
    printf("file_name file in assembly language to be converted into ");
    printf("file_name.cor, an executable in the Virtual Machine.\n");
}

int main(int argc, char **argv)
{
    header_t *ptr = malloc(sizeof(header_t));

    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    if (argc == 2 && my_strcmp(argv[1], "-h") != 0) {
        get_name(ptr, argv[1]);
        get_comment(ptr, argv[1]);
    }
    free(ptr);
    return 0;
}
