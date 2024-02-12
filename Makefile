SO_LONG = src/animation_1.c \
			src/animation_2.c \
			src/animation_3.c \
			src/check_map_1.c \
			src/check_map_2.c \
			src/check_map_3.c \
			src/check_map_4.c \
			src/clean_function.c \
			src/main.c \
			src/movement_1.c \
			src/movement_2.c \
			src/support.c \
			src/textures_1.c \
			src/textures_2.c \
			src/utils.c \

LIBFT = libft/libft.a

LIBFTDIR = libft/

SRC = $(SO_LONG)

OBJS = $(addprefix $(OBJDIR), $(notdir ${SRC:.c=.o}))

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

$(OBJDIR)%.o : src/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft $(MLX_FLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

l: $(NAME)
	./map_gen.pl \
	./$(NAME) rand_map.ber

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	rm -f rand_map.ber
	rm -f $(LIBFT)

re: fclean \
	all

.PHONY: all clean fclean re