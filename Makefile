GREEN = \033[0;32m
RED = \033[0;31m
DEFAULT = \033[0m

CC = gcc
FLAGS = -Wall -Werror -Wextra

NAME = minishell

SRC_DIR = srcs
SRCS = minishell.c

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

INCLUDE_LIBFT = lib/libft
LIBFT = lib/libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -C lib/libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(GREEN)Compling source files...$(DEFAULT)"
	@$(CC) $(FLAGS) -Iincludes -I$(INCLUDE_LIBFT) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Linking files...$(DEFAULT)"
	@$(CC) $(FLAGS) $^ -o $@

clean:
	@echo "$(RED)Removing object files...$(DEFAULT)"
	@rm -rf $(OBJ_DIR)
	@make clean -C lib/libft

fclean: clean
	@echo "$(RED)Removing program and libraries...$(DEFAULT)"
	@rm -f $(NAME)
	@make fclean -C lib/libft

re: fclean all

.PHONY: all clean fclean re