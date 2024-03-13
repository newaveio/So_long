#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/headers/ft_printf.h"
# include "../libft/headers/get_next_line.h"
# include "../libft/headers/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 32
# define EXTRA_HEIGHT 100
# define TRANSPARENT_COLOR 0x000000
# define PLAYER_IMAGE_PATH "assets/player/coin_1.xpm"

typedef struct s_flood
{
	int				collected;
	int				exits;
	int				rows;
	int				cols;
	int				x;
	int				y;
}					t_flood;

typedef struct s_game
{
	struct s_flood	*flood;
	char			**map;
	int				moves;
	int				collected;
	int				nb_collectibles;
	int				nb_e;
	int				nb_p;
	int				nb_x;
	int				exit_x;
	int				exit_y;
	int				old_x;
	int				old_y;
	int				pos_x;
	int				pos_y;
	int				rows;
	int				cols;
}					t_game;

typedef struct s_window
{
	int				width;
	int				height;
}					t_window;

typedef struct s_enemies
{
	int				x;
	int				y;
}					t_enemies;

typedef struct s_col
{
	int				x;
	int				y;
	int				*collected;
}					t_col;

typedef struct s_data
{
	char			**buf_map;
	int				misc1;
	int				misc2;
	int				player_is_moving;
	int				player_dir;
	void			*mlx_ptr;
	void			*win_ptr;
	// int					img_to_win;
	int				anim_counter[4];
	void			*player_text[4][8];
	void			*tile_text[2];
	void			*wall_text[2];
	void			*exit_text[5];
	void			*collec_text[4];
	void			*opps_text[4];
	char			*opps_data[4];
	int				bpp;
	int				size_line;
	int				endian;
	t_game			*game;
	t_window		*window;
	t_enemies		*enemies;
	t_col			*collectibles;
}					t_data;

int					animation_update(void *param);
void				anim_player(t_data *data);
void				anim_opps(t_data *data, int frame);
void				anim_exit(t_data *data, int frame);
void				anim_collectibles(t_data *data, int frame);
void				init_anim_counter(t_data *data);
void				draw_moves(t_data *data);
void				collect(t_data *data, int flag);
int					on_destroy(t_data *data);
int					on_keypress(int keysym, t_data *data);
void				initialize_map(t_data *data);
void				ft_update_map(t_data *data, int old_x, int old_y);
int					surrounded_by_walls(t_data *data);
int					is_rectangular(t_data *data);
int					check_caracters(t_data *data);
int					check_map_info(t_data *data);
void				get_c_e_p(t_data *data);
int					get_map_info(t_data *data);
int					mapping_enemies(t_data *data);
int					mapping_collectibles_bis(t_data *data, int index);
int					mapping_collectibles(t_data *data);
char				**copy_map(t_data *data);
int					copy_map_bis(t_data *data);
int					is_map_valid(t_data *data);
int					flood_fill_c(char **map, int x, int y, t_data *data);
int					flood_fill_e(char **map, int x, int y, t_data *data);
int					ber_extension(const char *filename);
int					check_map(t_data *data, const char *filename);
int					fill_map(t_data *data, const char *filename);
int					read_map(t_data *data);
void				free_2d_array(char **map, int rows);
void				free_map(t_data *data);
void				free_structure(t_data *data);
void				free_if(t_data *data);
void				player_move(t_data *data, int a);
int					mvt_checker(t_data *data, int a);
int					is_mvt_possible(t_data *data, char *mvt);
void				mvt_ud(t_data *data, int keysym);
void				mvt_lr(t_data *data, int keysym);
int					fill_data_struct(t_data *data);
void				fill_game_struct(t_data *data);
void				fill_struct_player_map(t_data *data);
int					ft_init_tiles(t_data *data);
int					ft_init_walls(t_data *data);
int					ft_init_opps(t_data *data);
int					ft_init_exit(t_data *data);
int					ft_init_collectibles(t_data *data);
char				*ft_init_player_bis(t_data *data);
int					ft_init_player(t_data *data);
int					ft_load_textures(t_data *data);
int					ft_strlen_nl(char *str);
int					ft_count_map_lines(t_data *data, const char *filename);
void				print_map(t_data *data);

#endif