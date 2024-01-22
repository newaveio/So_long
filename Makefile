SO_LONG = get_next_line.c get_next_line_utils.c

LIBFT = libft/libft.a

LIBFTDIR = libft/

SRC = $(SO_LONG)

OBJS = $(addprefix $(OBJDIR),${SRC:.c=.o})

OBJDIR = objs/

NAME = solong.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

$(OBJDIR)%.o : %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	cp $(LIBFT) .
	mv libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

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