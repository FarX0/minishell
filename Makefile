NAME = minishell

SRC = main.c \
	src/pwd/pwd.c \
	src/cd/cd.c \
	src/execute_command.c \
	src/initialize_data.c \
	src/export/export.c \
	src/export/export_utils.c \
	src/parsing.c \
	src/syntax_errors.c \
	src/free_and_null.c \
	src/echo/echo.c \
	src/unset/unset.c \
	src/utils/utils_matrix.c \
	src/utils/utils.c \
	src/utils/utils2.c \
	src/utils/utils3.c \
	src/exit/exit.c \
	src/here_doc/here_doc.c

INCLUDES = ./includes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libftprintf.a

#FLAGS		= -Wall -Werror -Wextra -I includes -pthread -fsanitize=thread -g
CFLAGS		=  -Wall -Wextra -Werror -I includes -lreadline -g

# -s : for valgrind
all:$(NAME)

$(NAME): $(SRC)
	@make all -C $(LIBFT_DIR)
	@cc $(SRC) $(CFLAGS) $(LIBFT) -I $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)[MINISHELL]:\t PROJECT COMPILED$(RESET)"


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

VALGRIND=@valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes
# FOR FD 		TRACKING: --track-fds=yes
# FOR CHILDREN	TRACKING: --trace-children=yes
val: all
	clear
	$(VALGRIND) ./$(NAME)

t: all
	 ./$(NAME)

#COLORS
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m

.PHONY: all clean fclean re
