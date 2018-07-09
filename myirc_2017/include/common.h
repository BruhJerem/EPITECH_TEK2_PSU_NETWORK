/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Common header
*/

#ifndef PSU_MYIRC_2017_COMMON_H
# define PSU_MYIRC_2017_COMMON_H

#include <stdbool.h>
#include <netinet/in.h>

typedef struct s_socket *socket_t;

struct s_socket {
	int fd;
	unsigned short port;
	char *ip;
};

/* socket.c */
socket_t create_socket(char *address, unsigned short port);
bool destruct_socket(socket_t sock);

/* str_to_wordtab.c */
char **str_to_wordtab(char *str, char separator);

/* rebind.c */
char *rebind(char **tab, char separator);
void free_tab(char **tab);

/* fix_buffer.c */
void fix_buffer(char *s);

# ifndef READ_SIZE
#  define READ_SIZE (1024)

# endif /* !READ_SIZE */

// tab_len
size_t tab_len(char **tab);

/* nmatch.c */
int nmatch(char *s1, char *s2);

#endif //PSU_MYIRC_2017_COMMON_H
