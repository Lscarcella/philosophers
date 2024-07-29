CFLAGS = -Wall -Wextra -Werror -g
DEPS = ./include/philosophers.h
RM = rm -rf
SRC_DIR = ./src/
NAME = philosophers
SRC =  $(SRC_DIR)main.c $(SRC_DIR)utils.c

# -- COLORS -- #
BLACK=\033[0;30m# Black
RED=\033[0;31m# Red
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE

all: $(NAME)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compilation successful. Library: $(NAME) $(WHITE)"

# création des fichiers objets à partir des fichiers source.
%.o: %.c $(DEPS_BONUS) $(DEPS) 
	@$(CC) -c -o $@ $< -I$(LIBFT_DIR) $(CFLAGS)

# supprime les fichiers objets. #
clean:
	@$(RM) $(OBJ)
	@echo "$(CYAN)Object files cleaned successfully. Library: $(NAME) $(WHITE)"
	@echo "--------------------------------------------------------"

# supprime les fichiers objets et la bibliothèque.
fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)Library cleaned successfully. Library: $(NAME) $(WHITE)"
	@echo "--------------------------------------------------------"

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes ./philosophers

# indique que 'all', 'clean', 'fclean' et 're' ne sont pas des fichiers. #
.PHONY: all bonus clean fclean re
