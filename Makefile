SRC = main.c game.c state_play.c state_menu.c helpers.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
LDFLAGS = -lncursesw
NAME = 2048

all: $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

run: all
	@./2048

valgrind: all
	@valgrind ./2048

.PHONY: all clean fclean re run valgrind

-include $(OBJS:.o=.d)
