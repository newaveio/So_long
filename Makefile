SO_LONG = main.c \
			get_next_line.c \
			get_next_line_utils.c \
			check_map.c \
			textures_1.c \
			textures_2.c \
			utils.c \
			game.c

LIBFT = libft/libft.a

LIBFTDIR = libft/

SRC = $(SO_LONG)

OBJS = $(addprefix $(OBJDIR),${SRC:.c=.o})

OBJDIR = objs/

NAME = solong

CC = cc

CFLAGS = -Wall -Wextra -Werror

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	INCLUDES = -I/usr/include -Imlx
endif

MLX_DIR = ./mlx

MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(UNAME), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
endif

all: $(MLX_LIB) $(NAME)

$(OBJDIR)%.o : %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft $(MLX_FLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean \
	all

.PHONY: all clean fclean re