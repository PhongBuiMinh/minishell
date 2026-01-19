# Color codes
GREEN = \033[0;32m
RED = \033[0;31m
DEFAULT = \033[0m

# Compile and flags
CC = gcc
FLAGS = -Wall -Werror -Wextra
MODE ?= release

ifeq ($(MODE), debug)	
	FLAGS += -g
else
	FLAGS += -O2
endif

# Project name
NAME = minishell

# Direcories and source files
SRC_DIR = srcs
OBJ_DIR = objs
SRCS = minishell.c \
		lexer/lexer.c \
		lexer/utils.c \
		parser/parser.c
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

-include $(DEPS)

# Libraries
LIBFT_PATH = lib/libft
LIBFT = lib/libft/libft.a

# Targets
.PHONY: all clean fclean re test benchmark install uninstall
 
# Build targets
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Linking files...$(DEFAULT)"
	@$(CC) $(FLAGS) $^ -L$(LIBFT_PATH) -lft -lc -lreadline -o $@

# Object file rules

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling source files...$(DEFAULT)"
	@$(CC) $(FLAGS) -Iincludes -I$(LIBFT_PATH) -MMD -MP -c $< -o $@

# Library build
$(LIBFT):
	@echo "$(GREEN)Compling library...$(DEFAULT)"
	@make -C lib/libft

# Cleanup
clean:
	@echo "$(RED)Removing object files...$(DEFAULT)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "$(RED)Removing program and libraries...$(DEFAULT)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

# Testing and benchmarking
test:
	@./tests/run_tests.sh

benhmark:
	@./benchmarks/run_benchmarks.sh

# Install and Uninstall
install:
	@cp $(NAME) /usr/local/bin

uninstall:
	@rm -f /usr/local/bin/$(NAME)

re: fclean all