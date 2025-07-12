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
SRC_ROOT = $(wildcard src/*.c)
SRC_BUILTINS = $(wildcard src/builtins/*.c)
SRC_PARSING = $(wildcard src/parsing/*.c)
SRC_EXEC = $(wildcard src/executor/*.c)
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

