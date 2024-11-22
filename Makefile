NAME = minishell

SRC = main.c \
	src/pwd/pwd.c \
	src/execute_command.c \
	src/initialize_data.c \
	src/export/export.c \
	src/export/export_utils.c \
	src/pipex_and_operators/pipex.c \
	src/pipex_and_operators/operators.c \
	src/parsing.c \
	src/free_and_null.c \
	src/echo/echo.c \
	src/utils/utils.c

INCLUDES = ./includes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libftprintf.a

#FLAGS		= -Wall -Werror -Wextra -I includes -pthread -fsanitize=thread -g
CFLAGS		=  -Wall -Wextra -Werror -I includes -pthread -g

# -s : for valgrind
$(NAME): $(SRC)
	@make all -C $(LIBFT_DIR)
	@cc $(SRC) $(CFLAGS) $(LIBFT) -I $(INCLUDES) -o $(NAME) -lreadline -s 
	@echo "$(GREEN)[MINISHELL]:\t PROJECT COMPILED$(RESET)"

all:$(NAME)

clean:
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)[MINISHELL]:\t CLEAN$(RESET)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f *.a
	@rm -f *.gch
	@rm -f $(NAME)
	@echo "$(RED)[MINISHELL]:\t FCLEAN$(RESET)"

re: fclean all

hel: all
	valgrind --tool=helgrind --history-level=approx ./$(NAME)

val: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=./supp/supp.supp ./$(NAME)

t: all
	 ./$(NAME)

#COLORS
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m

.PHONY: all clean fclean re
