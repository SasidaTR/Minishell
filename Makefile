NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = $(wildcard src/*.c src/libft/*.c)
OBJ_DIR = obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/src/%.o: src/%.c | $(OBJ_DIR)/src
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/src/libft/%.o: src/libft/%.c | $(OBJ_DIR)/src/libft
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/src:
	mkdir -p $(OBJ_DIR)/src

$(OBJ_DIR)/src/libft:
	mkdir -p $(OBJ_DIR)/src/libft

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
