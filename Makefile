NAME = minishell
CC = cc

SRC_ROOT = $(wildcard src/*.c)
SRC_BUILTINS = $(wildcard src/builtins/*.c)
SRC_PARSING = $(wildcard src/parsing/*.c)
SRC = $(SRC_ROOT) $(SRC_BUILTINS) $(SRC_PARSING)

OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ_ROOT = $(SRC_ROOT:src/%.c=$(OBJ_DIR)/%.o)
OBJ_BUILTINS = $(SRC_BUILTINS:src/builtins/%.c=$(OBJ_DIR)/builtins/%.o)
OBJ_PARSING = $(SRC_PARSING:src/parsing/%.c=$(OBJ_DIR)/parsing/%.o)
OBJ = $(OBJ_ROOT) $(OBJ_BUILTINS) $(SRC_PARSING)

CFLAGS = -Wall -Wextra -Werror -g -Iinclude -I$(LIBFT_DIR) -Isrc/builtins -Isrc/parsing
LDFLAGS = -lreadline


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
