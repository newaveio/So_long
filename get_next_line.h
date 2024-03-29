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

# define TILE_SIZE 32
# define EXTRA_HEIGHT 100
# define TRANSPARENT_COLOR 0x000000
# define PLAYER_IMAGE_PATH "assets/player/coin_1.xpm"

typedef struct s_flood
{
	int					collected;
	int					exits;
	int					rows;
	int					cols;
	int					x;
	int					y;
}						t_flood;

typedef struct s_game
{
	struct s_flood		*flood;
	char				**map;
	int					moves;
	int					collected;
	int					nb_collectibles;
	int					nb_e;
	int					nb_p;
	int					nb_x;
	int					exit_x;
	int					exit_y;
	int					old_x;
	int					old_y;
	int					pos_x;
	int					pos_y;
	int					rows;
	int					cols;
}						t_game;

typedef struct s_window
{
	int					width;
	int					height;
}						t_window;

typedef struct s_enemies
{
	int					x;
	int					y;
}						t_enemies;

typedef struct s_col
{
	int					x;
	int					y;
	int					*collected;
}						t_col;

typedef struct s_data
{
	char				**buf_map;
	int					misc1;
	int					misc2;
	int					player_is_moving;
	int					player_dir;
	void				*mlx_ptr;
	void				*win_ptr;
	int					img_to_win;
	int					anim_counter[4];
	void				*player_text[4][8];
	void				*tile_text[2];
	void				*wall_text[2];
	void				*exit_text[5];
	void				*collec_text[4];
	void				*opps_text[4];
	t_game				*game;
	t_window			*window;
	t_enemies			*enemies;
	t_col				*collectibles;
}						t_data;

typedef struct s_list_gnl
{
	int					fd;
	char				*content;
	struct s_list_gnl	*next;
}						t_list_gnl;

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
void					read_and_stash(int fd, t_list_gnl **stash);
char					*get_next_line(int fd);
int						found_newline(t_list_gnl *stash);

// UTILS.C
int						ft_strlen_nl(char *str);
int						ft_count_map_lines(t_data *data, const char *filename);
int						fill_map(t_data *data, const char *filename);
int						read_map(t_data *data);
int						ber_extension(const char *filename);
int						check_map(t_data *data, const char *filename);

// TEXTURES_1.C
int						ft_init_tiles(t_data *data);
int						ft_init_walls(t_data *data);
int						ft_init_opps(t_data *data);
int						ft_init_exit(t_data *data);
int						ft_init_collectibles(t_data *data);

// TEXTURES_2.C
char					*ft_init_player_bis(t_data *data);
int						ft_init_player(t_data *data);
int						ft_load_textures(t_data *data);

// CHECK_MAP.C
int						surrounded_by_walls(t_data *data);
int						is_rectangular(t_data *data);
int						check_caracters(t_data *data);
int						check_map_info(t_data *data);
void					get_c_e_p(t_data *data);
int						mapping_enemies(t_data *data);
int						mapping_collectibles_bis(t_data *data, int index);
int						mapping_collectibles(t_data *data);
int						get_map_info(t_data *data);
void					fill_struct_player_map(t_data *data);
int						flood_fill_c(char **map, int x, int y, t_data *data);
int						flood_fill_e(char **map, int x, int y, t_data *data);
char					**copy_map(t_data *data);
int						is_map_valid(t_data *data);

// GAME.C
void					player_move(t_data *data, int a);
void					print_map(t_data *data);
void					collect(t_data *data, int i);
int						mvt_checker(t_data *data, int a);
int						is_mvt_possible(t_data *data, char *mvt);
void					mvt_ud(t_data *data, int keysym);
void					mvt_lr(t_data *data, int keysym);

int						on_keypress(int keysym, t_data *data);
int						on_destroy(t_data *data);

void					fill_game_struct(t_data *data);
int						fill_data_struct(t_data *data);

void					draw_moves(t_data *data);
void					ft_update_map(t_data *data, int old_x, int old_y);
void					initialize_map(t_data *data);
int						animation_update(void *param);

#endif