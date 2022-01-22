COMP	= cc
NAME	= pipex
FLAGS	= -Wall -Wextra -Werror

SRCS	= src/utils.c src/utils_bonus.c libft/libft.a libgnl/libgnl.a
INCS	= -I includes

all: libft $(NAME)

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

re: fclean all

bonus:
	$(COMP) $(FLAGS) $(SRCS) $(INCS) pipex_bonus.c -o $(NAME)

.PHONY: libft libgnl
