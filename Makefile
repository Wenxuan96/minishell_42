NAME = minishell
CC = cc

# Detect OS (Darwin = macOS)
UNAME_S := $(shell uname -s)

# Platform-specific Readline configuration
ifeq ($(UNAME_S),Darwin)
	READLINE_DIR = /usr/local/opt/readline
	CFLAGS += -I$(READLINE_DIR)/include
	LDFLAGS += -L$(READLINE_DIR)/lib -lreadline
else
	CFLAGS += -I/usr/include/readline
	LDFLAGS += -lreadline
endif

# Directories and sources
SRC_ROOT = \
	src/main.c \
	src/init.c \
	src/init_env_var.c \
	src/errors.c \
	src/pipes.c \
	src/processes.c \
	src/redirections.c \
	src/redir_heredoc.c \
	src/redir_heredoc_utils.c.c \
	src/singals.c \
	src/utils_clear.c \
	src/utils_free.c \
	src/utils_malloc.c \
	src/utils_pipes.c \
	src/utils_processes.c \
	src/utils_redir.c \
	src/utils_temp.c

SRC_BUILTINS = \
	src/builtins/builtins.c \
	src/builtins/cd.c \
	src/builtins/echo.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/export.c \
	src/builtins/export_utils.c \
	src/builtins/pwd.c \
	src/builtins/unset.c \
	src/builtins/utils_builtin.c

SRC_PARSING = \
	src/parsing/handle_quote.c \
	src/parsing/input_checker.c \
	src/parsing/populate_process.c \
	src/parsing/tokenize.c \
	src/parsing/tokenize_utils.c \
	src/parsing/utils_parse_redir.c \
	src/parsing/utils_prcs_parser.c \
	src/parsing/utils_token.c \
	src/parsing/utils_var_epansion.c \
	src/parsing/variable_expansion.c

SRC_EXEC = \
	src/executor/executor_builtins.c \
	src/executor/executor_outside_cmd.c \
	src/executor/execve_get_env_vars.c \
	src/executor/execve_get_path.c \
	src/executor/execve_get_path_utls.c \
	src/executor/execve_get_path_utls2.c

SRC = $(SRC_ROOT) $(SRC_BUILTINS) $(SRC_PARSING) $(SRC_EXEC)

OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ_ROOT = $(SRC_ROOT:src/%.c=$(OBJ_DIR)/%.o)
OBJ_BUILTINS = $(SRC_BUILTINS:src/builtins/%.c=$(OBJ_DIR)/builtins/%.o)
OBJ_PARSING = $(SRC_PARSING:src/parsing/%.c=$(OBJ_DIR)/parsing/%.o)
OBJ_EXEC = $(SRC_EXEC:src/executor/%.c=$(OBJ_DIR)/executor/%.o)
OBJ = $(OBJ_ROOT) $(OBJ_BUILTINS) $(OBJ_PARSING) $(OBJ_EXEC)

CFLAGS += -Wall -Wextra -Werror -g -Iinclude -I$(LIBFT_DIR) -Isrc/builtins -Isrc/parsing

# Build target
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile objects
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run with valgrind
valgrind: all
	valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full --track-fds=yes --suppressions=minishell.supp ./$(NAME)

# Clean up
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re valgrind

