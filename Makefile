COMP		=	cc
NAME		=	pipex
FLAGS		=	-Wall -Wextra -Werror

SRCS		=	utils.c	pipex.c libft/libft.a

all: libft $(NAME)

libft:
	@make -C libft

$(NAME):
	$(COMP) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	@make -C libft clean

fclean:
	rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

bonus:
	$(COMP) $(FLAGS) utils.c pipex_bonus.c libft/libft.a -o $(NAME)

.PHONY: libft
