NAME			= libft.a

AR				= ar rcs
RM				= rm -f
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
CFLAGS			+= -I ./

SRCS_DIR		= ./srcs/
SRCS			= $(shell find $(SRCS_DIR) -name '*.c')
OBJS_PATH		= ./objs/
OBJS			= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_PATH)%.o)

TOTAL_FILES     = $(words $(SRCS))
CURRENT_INDEX   = 0

#!---------------------------------------- MAIN LIBFT ----------------------------------------!#

all:		$(NAME)

$(NAME): 	$(OBJS)
			@echo "\n$(BOLD)┗▷$(GREEN)『libft.a Created』[✅]$(RESET)"
			@$(AR) $(NAME) $(OBJS)

$(OBJS_PATH)%.o : $(SRCS_DIR)%.c
			@mkdir -p $(@D)
			@$(eval CURRENT_INDEX=$(shell echo $$(($(CURRENT_INDEX)+1))))
			@$(eval PERCENT=$(shell echo $$(($(CURRENT_INDEX) * 100 / $(TOTAL_FILES)))))
			@printf "\r$(YELLOW)🔧 $(GREEN)%3d%% $(YELLOW)$(BOLD)Compiling: $(RESET)$(BLUE)$(ITALIC)%-50s $(MAGENTA)[%3d/%3d]$(RESET)" $(PERCENT) "$<" $(CURRENT_INDEX) $(TOTAL_FILES)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@echo "$(BOLD) [🗑️ ] $(YELLOW)$(REVERSED)Cleaning up object files from LIBFT...$(RESET)"
			@$(RM) $(OBJS)
			@echo "┗▷$(YELLOW)『\".o\" files from $(ITALIC)./libft/$(RESET)$(YELLOW) cleaned』$(RESET)"

fclean:		clean
			@$(RM) $(NAME)
			@if [ -d "$(OBJS_PATH)" ]; then rm -rf $(OBJS_PATH); fi

re:			fclean all

.PHONY: 	all bonus clean fclean re

#*------------------------------------------ DESIGN ------------------------------------------*#
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
