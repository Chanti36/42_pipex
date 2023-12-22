CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = pipex

SRCS =	code/childs.c	\
		code/pipex.c	\
		code/rutes.c

BONUS_SRC = bonus/childs_bonus.c 	\
			bonus/forks_bonus.c 	\
			bonus/gnl_bonus.c		\
			bonus/gnl_utils_bonus.c	\
			bonus/here_doc_bonus.c	\
			bonus/pipex_bonus.c		\
			bonus/rutes_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRC:.c=.o)

all: $(NAME) 
$(NAME): $(OBJS) libft/libft.a
	$(CC) $(OBJS) -o $(NAME) -Llibft/ -lft

libft/libft.a:
	make -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus
.bonus: $(BONUS_OBJS) libft/libft.a
	$(CC) $(BONUS_OBJS) -o $(NAME) -Llibft/ -lft
	touch .bonus

clean:
	rm -rf $(OBJS)
	rm -rf $(BONUS_OBJS)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	make -C libft/ fclean

re: fclean
	make -C libft/ re
	make

.PHONY: clean fclean re
