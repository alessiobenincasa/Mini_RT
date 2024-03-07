NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = src
SRCS = main.c get_next_line.c read_map.c draw_grid.c color.c map_to_point.c keys.c keys2.c keys3.c mouse.c transformations.c menu.c screen.c rotations.c check_map.c check_map2.c
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

LIB_MINILIBX = -Lminilibx -lmlx -lXext -lX11 -lm -lz
LIB_LIBFT = Libft/libft.a

MINILIBX = minilibx/
LIBFT = Libft/

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

TOTAL_FILES = $(words $(SRCS))
CURRENT_INDEX = 0

define progress_bar
	$(eval CURRENT_INDEX=$(shell echo $$(($(CURRENT_INDEX)+1))))
	$(eval PERCENT=$(shell echo $$(($(CURRENT_INDEX) * 100 / $(TOTAL_FILES)))))
	@printf "\r$(YELLOW)Compiling: $(GREEN)%3d%% $(RESET)[$(CURRENT_INDEX)/$(TOTAL_FILES)] $<"
endef

all: $(NAME)

$(NAME): lib $(OBJS)
	@echo "$(GREEN)\nLinking...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIB_MINILIBX) $(LIB_LIBFT) -o $(NAME)
	@echo "$(GREEN)\n$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(call progress_bar)
	$(CC) $(CFLAGS) -c $< -o $@

lib:
	@make -C $(MINILIBX)
	@make -C $(LIBFT)

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C $(MINILIBX)
	@make clean -C $(LIBFT)
	@echo "$(GREEN)Object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo "$(GREEN)$(NAME) removed.$(RESET)"

re: fclean all

.PHONY: all lib clean fclean re
