# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 16:18:07 by albeninc          #+#    #+#              #
#    Updated: 2024/03/17 19:56:12 by albeninc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
UNIT_TESTS_NAME = unit_tests
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Include directories
INCLUDES = -IInclude -Ilibft/srcs/includes -Iminilibx -I$HOME/Criterion/include/criterion

# Recursively find all .c files in src directory and its subdirectories
SRCS_DIR = src
SRCS = $(shell find $(SRCS_DIR) -name '*.c' ! -path "$(SRCS_DIR)/Unit-testing/*")

UNIT_TEST_SRC = $(SRCS_DIR)/Unit-testing/unit-test.c
UNIT_TEST_OBJS = $(patsubst %.c, %.o, $(UNIT_TEST_SRC))

OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

LIB_MINILIBX = -Lminilibx -lmlx -lXext -lX11 -lm -lz
LIB_LIBFT = Include/libft/libft.a
LIB_CRITERION = -L$HOME/Criterion/build/src -lcriterion -Wl,-rpath=$HOME/Criterion/build/src

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

unit_tests: $(UNIT_TEST_OBJS)
	@echo "$(GREEN)\nCompiling unit tests...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) $(UNIT_TEST_SRC) $(LIB_CRITERION) -o $(UNIT_TESTS_NAME)
	@echo "$(GREEN)\nUnit tests compiled successfully!$(RESET)"

$(SRCS_DIR)/Unit-testing/%.o: $(SRCS_DIR)/Unit-testing/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

lib:
	@make -C $(MINILIBX)
	@make -C $(LIBFT)

clean:
	@rm -rf $(OBJS_DIR) $(SRCS_DIR)/Unit-testing/*.o
	@make clean -C $(MINILIBX)
	@make clean -C $(LIBFT)
	@echo "$(GREEN)Object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME) $(UNIT_TESTS_NAME)
	@make fclean -C $(LIBFT)
	@echo "$(GREEN)$(NAME) and unit tests removed.$(RESET)"

re: fclean all

.PHONY: all lib clean fclean re unit_tests
