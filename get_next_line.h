#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/headers/ft_printf.h"
# include "libft/headers/libft.h"
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef MAP_FILE
#  define MAP_FILE "maps/map_2.ber"
# endif

typedef struct s_game
{
	char	**map;
	int		moves;
	int		collected;
	int		nb_collectibles;
}						t_game;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*textures[5];
	t_game				*game;
}						t_data;

typedef struct s_list_gnl
{
	int					fd;
	char				*content;
	struct s_list_gnl	*next;
}						t_list_gnl;

typedef struct s_map_ch
{
	int					nb_c;
	int					nb_e;
	int					nb_p;
}						t_map_ch;

typedef struct s_play
{
	int					player_x;
	int					player_y;
	int					nb_c;
	int					collected;
	int					exits;
	int					rows;
	int					cols;
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
int						ft_strlen_nl(char *str);

// UTILS_2.C
int						ft_count_map_lines(int *count);
char					**fill_map(int count);
char					**read_map(int *rows);
int						ber_extension(const char *filename);

// CHECK_MAP.C
int						surrounded_by_walls(char **map, int rows);
int						is_rectangular(char **map, int rows);
int						check_caracters(char **map, int rows);
int						check_map_info(t_map_ch map_info);
void					get_c_e_p(char **map, int rows, t_map_ch *map_info);
int						get_map_info(char **map, int rows);
void					fill_struct_player_map(char **map,
							t_play *play_map_info, int rows);
int						flood_fill(char **map, int x, int y,
							t_play *play_map_info);
char					**copy_map(char **map, int rows);
int						is_map_valid(char **map, int rows);

// GAME.C
void	mvt_ud(t_data *data);
void	mvt_lr(t_data *data);
int	on_keypress(int keysym, t_data *data);
int on_destroy(t_data *data);

#endif