/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** Splits a string into a NULL-terminated array of words
*/

#include <stdlib.h>

static int is_sep(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static int count_words(char const *str)
{
    int count = 0;
    int in_word = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (!is_sep(str[i]) && !in_word) {
            count++;
            in_word = 1;
        } else if (is_sep(str[i])) {
            in_word = 0;
        }
        i++;
    }
    return count;
}

static char *dup_word(char const *str, int start, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (word == NULL)
        return NULL;
    while (i < len) {
        word[i] = str[start + i];
        i++;
    }
    word[len] = '\0';
    return word;
}

static void free_arr(char **arr, int idx)
{
    while (idx >= 0) {
        free(arr[idx]);
        idx--;
    }
    free(arr);
}

static int get_word_len(char const *str, int i)
{
    int len = 0;

    while (str[i + len] != '\0' && !is_sep(str[i + len]))
        len++;
    return len;
}

static int fill_arr(char **arr, char const *str)
{
    int idx = 0;
    int i = 0;
    int len;

    while (str[i] != '\0') {
        if (is_sep(str[i++]))
            continue;
        len = get_word_len(str, i - 1);
        arr[idx] = dup_word(str, i - 1, len);
        if (arr[idx] == NULL) {
            free_arr(arr, idx - 1);
            return -1;
        }
        i += len - 1;
        idx++;
    }
    return 0;
}

char **my_str_to_word_array(char const *str)
{
    int nb = count_words(str);
    char **arr = malloc(sizeof(char *) * (nb + 1));

    if (arr == NULL)
        return NULL;
    if (fill_arr(arr, str) == -1)
        return NULL;
    arr[nb] = NULL;
    return arr;
}
