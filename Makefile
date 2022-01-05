COMP	= cc
NAME	= pipex
FLAGS	= -Wall -Wextra -Werror

SRCS	= utils.c libft/libft.a

all: libft $(NAME)

libft:
	@make -C libft

$(NAME): pipex.c
	$(COMP) $(FLAGS) $(SRCS) pipex.c -o $(NAME)

clean:
	rm -rf $(NAME)

fclean:
	@make -C libft fclean

re: fclean all

bonus: pipex_bonus.c
	$(COMP) $(FLAGS) $(SRCS) pipex_bonus.c -o $(NAME)

.PHONY: libft
