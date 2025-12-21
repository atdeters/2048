NAME        = 2048
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
DEBUG_FLAGS = -g -O0 -DDEBUG=true

SRC_DIR     = src
OBJ_DIR     = obj

INC_DIR     = inc
INCLUDES    = -I$(INC_DIR)

LDLIBS      = -lncurses
LIBFT		= src/libft.a

SRCS = \
	src/main.c \
	src/game.c \
	src/helpers.c \
	src/state_menu.c \
	src/state_play.c \
	src/render_grid.c \
	src/grid_manipulation.c \
	src/colors.c \
	src/set.c \

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)
DEPFLAGS = -MMD -MP

all: $(LIBFT) $(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re
	@./2048

run: all
	@./2048

valgrind: all
	@valgrind ./2048

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/data.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)

clean:
	@rm -f $(OBJS) $(DEPS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all verbose run valgrind clean fclean re
