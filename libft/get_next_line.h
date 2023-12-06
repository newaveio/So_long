#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	int				fd;
	char			*content;
	struct s_list	*next;
}					t_list;

int					ft_len_stash(t_list **stash, int fd);
void				ft_extract_line(t_list **stash, char **line, int fd);
t_list				*ft_get_last_node(t_list *stash);
void				addback_stash(t_list **stash, t_list *newnode);
t_list				*create_elem(int fd, char *buffer, int bytes_read);
void				remove_node(t_list **stash, t_list **current,
						t_list *previous);
void				free_stash(t_list **stash, int fd);
void				clean_and_store_remaining(t_list **stash, int fd, int index);
// void				read_and_stash(int fd, t_list **stash, char *buffer);
void				read_and_stash(int fd, t_list **stash);
char				*get_next_line(int fd);
int					found_newline(t_list *stash);

#endif