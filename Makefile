SRCS = so_long.c

OBJDIR = ./obj

OBJS = $(addprefix $(OBJDIR)/,${SRCS:.c=.o})

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
else
	INCLUDES = -I/opt/X11/include -Imlx
endif

ifeq ($(shell uname), Linux)
	MLX_DIR = ./minilibx-linux
else
	MLX_DIR = ./minilibx_opengl_20191021
endif

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lminilibx-linux -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = so_long

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	${CC} ${CFLAGS} -c -o $@ $< ${INCLUDES}

clean:
	rm -f $(OBJDIR)/*
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean \
	re

.PHONY: all clean fclean re