#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list_gnl
{
	int					fd;
	char				*content;
	struct s_list_gnl	*next;
}						t_list_gnl;

typedef struct s_map
{
	int nb_c;
	int	nb_e;
	int	nb_p;
}						t_map;

typedef struct s_play
{
	int player_x;
	int player_y;
	int nb_c;
	int rows;
	int cols;
}						t_play;

// GET_NEXT_LINE
int						ft_len_stash(t_list_gnl **stash, int fd);
void					ft_extract_line(t_list_gnl **stash, char **line,
							int fd);
t_list_gnl				*ft_get_last_node(t_list_gnl *stash);
void					addback_stash(t_list_gnl **stash, t_list_gnl *newnode);
t_list_gnl				*create_elem(int fd, char *buffer, int bytes_read);
void					remove_node(t_list_gnl **stash, t_list_gnl **current,
							t_list_gnl *previous);
void					free_stash(t_list_gnl **stash, int fd);
void					clean_and_store_remaining(t_list_gnl **stash, int fd,
							int index);
// void				read_and_stash(int fd, t_list_gnl **stash, char *buffer);
void					read_and_stash(int fd, t_list_gnl **stash);
char					*get_next_line(int fd);
int						found_newline(t_list_gnl *stash);

// UTILS.C
int	ft_strlen_nl(char *str);

// CHECK_MAP.C
int	check_caracters(char **map, int rows);
int	get_map_info(char **map, int rows);
void    get_c_e_p(char **map, int rows, t_map *map_info);
int is_rectangular(char **map, int rows);
int surrounded_by_walls(char **map, int rows);
int	is_map_valid(char **map, int rows);
void    fill_struct_player_map(char **map, t_play *play_map_info, int rows);

#endif