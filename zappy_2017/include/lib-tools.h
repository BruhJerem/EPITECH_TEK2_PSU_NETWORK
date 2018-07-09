/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Lib tools header file
*/

#ifndef PSU_ZAPPY_2017_LIB_TOOLS_H
#define PSU_ZAPPY_2017_LIB_TOOLS_H

#include <unistd.h>
#include <stdbool.h>

// Typedef
typedef struct s_circular_buffer *circular_buffer_t;

// Struct
struct s_circular_buffer {
	char *buffer;
	size_t head;
	size_t tail;
	size_t size;
};

// Tab manipulation
void free_tab(char **tab);
size_t tab_len(char **tab);
size_t tab_str_len(char **tab);

// Tab string manipulation
char *wordtab_to_str(char **tab, char separator);
char **str_to_wordtab(char *str, char delimiter);

// Circular buffer
bool circular_buf_reset(circular_buffer_t cbuf);
bool circular_buf_put(circular_buffer_t cbuf, char *data);
char *circular_buf_get(circular_buffer_t cbuf);
bool circular_buf_is_empty(circular_buffer_t cbuf);
bool circular_buf_is_full(circular_buffer_t cbuf);
circular_buffer_t create_circular_buf(size_t size);
bool free_circular_buf(circular_buffer_t cbuff);

// String number manipulation
bool str_is_number(const char *str);

// String manipulation
char *ov_strcat(char *dest, char *src, size_t overwrite_n);

#endif //PSU_ZAPPY_2017_LIB_TOOLS_H
