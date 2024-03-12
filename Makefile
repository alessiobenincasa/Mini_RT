# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 16:18:07 by albeninc          #+#    #+#              #
#    Updated: 2024/03/12 17:32:34 by albeninc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Include directories
INCLUDES = -IInclude -Ilibft/srcs/includes -Iminilibx

# Recursively find all .c files in src directory and its subdirectories
SRCS_DIR = src
SRCS = $(shell find $(SRCS_DIR) -name '*.c')

OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

LIB_MINILIBX = -Lminilibx -lmlx -lXext -lX11 -lm -lz
LIB_LIBFT = Include/libft/libft.a

MINILIBX = minilibx/
LIBFT = Include/libft/

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
	@mkdir -p $(dir $@)
	@$(call progress_bar)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
