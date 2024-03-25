NAME 				= miniRT
CC 					= cc
CFLAGS 				= -Wall -Wextra -Werror

INCLUDES 			= -IInclude -IInclude/libft/srcs/includes -Iminilibx

LIB_MINILIBX 		= -Lminilibx -lmlx -lXext -lX11 -lm -lz
LIB_LIBFT 			= -LInclude/libft -lft

SRCS_DIR			= ./src/
OBJS_PATH			= ./objs/

SRCS				= $(shell find $(SRCS_DIR) -name '*.c')
OBJS				= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_PATH)%.o)

MAKEFLAGS 			+= --no-print-directory
TOTAL_FILES     	= $(words $(SRCS))
CURRENT_INDEX   	= 0

all: 				$(NAME)

$(NAME): 			lib $(OBJS)
					@$(CC) $(OBJS) $(LIB_MINILIBX) $(LIB_LIBFT) $(INCLUDES) -o $(NAME)
					@echo "\n$(BOLD)┗▷$(GREEN)『./miniRT Created』[✅]$(RESET)"

$(OBJS_PATH)%.o: 	$(SRCS_DIR)%.c
					@mkdir -p $(@D)
					@$(eval CURRENT_INDEX=$(shell echo $$(($(CURRENT_INDEX)+1))))
					@$(eval PERCENT=$(shell echo $$(($(CURRENT_INDEX) * 100 / $(TOTAL_FILES)))))
					@printf "\r$(YELLOW)🔧 $(GREEN)%3d%% $(YELLOW)$(BOLD)Compiling: $(RESET)$(BLUE)$(ITALIC)%-50s $(MAGENTA)[%3d/%3d]$(RESET)" $(PERCENT) "$<" $(CURRENT_INDEX) $(TOTAL_FILES)
					@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

lib:
					@make -C minilibx
					@make -C Include/libft

clean:
					@echo "$(BOLD) [🗑️ ] $(YELLOW)$(REVERSED)Cleaning up$(RESET)"
					@make -C minilibx clean
					@make -C Include/libft clean
					@echo "┗▷$(YELLOW)『Libraries cleaned』$(RESET)"
					@rm -rf $(OBJS_PATH)
					@echo "┗▷$(YELLOW)『Object files from $(ITALIC)./miniRT/$(RESET)$(YELLOW) cleaned』$(RESET)"

fclean:				clean
					@rm -f $(NAME)
					@make -C Include/libft fclean
					@echo "┗▷$(YELLOW)『executables from $(ITALIC)./miniRT/$(RESET)$(YELLOW) cleaned』$(RESET)"

re: 				fclean all

.PHONY:				all lib clean fclean re

# Colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[0;37m
RESET := \033[0m

# Text Styles
BOLD := \033[1m
UNDERLINE := \033[4m
REVERSED := \033[7m
ITALIC := \033[3m