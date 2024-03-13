# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 16:18:07 by albeninc          #+#    #+#              #
#    Updated: 2024/03/13 10:39:52 by svolodin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Include directories
INCLUDES = -IInclude -IInclude/libft/srcs/includes -Iminilibx_macos

# Library paths and linking flags
LIB_MINILIBX = -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
LIB_LIBFT = -LInclude/libft -lft
# Recursively find all .c files in src directory and its subdirectories
SRCS_DIR = src
SRCS = $(shell find $(SRCS_DIR) -name '*.c')

OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

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
	$(CC) $(OBJS) $(LIB_MINILIBX) $(LIB_LIBFT) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(call progress_bar)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

lib:
	@make -C minilibx_macos
	@make -C Include/libft

clean:
	@make -C minilibx_macos clean
	@make -C Include/libft clean
	@rm -rf $(OBJS_DIR)
	@echo "$(YELLOW)Objects and libraries cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(NAME) removed.$(RESET)"

re: fclean all

.PHONY: all lib clean fclean re
