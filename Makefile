COMP		= cc
NAME		= pipex
FLAGS		= -Wall -Wextra -Werror
SRCS		= src/utils.c libft/libft.a
SRCS_BONUS	= src/utils.c src/utils_bonus.c src/utils_heredoc_bonus.c libft/libft.a libgnl/libgnl.a
INCS		= -I includes

all: libft libgnl $(NAME)

libft:
	@make -C libft

libgnl:
	@make -C libgnl

$(NAME):
	$(COMP) $(FLAGS) $(SRCS) $(INCS) pipex.c -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	@make -C libft fclean
	@make -C libgnl fclean

re: fclean all

bonus: libft libgnl
	$(COMP) $(FLAGS) $(SRCS_BONUS) $(INCS) pipex_bonus.c -o $(NAME)

.PHONY: libft libgnl
