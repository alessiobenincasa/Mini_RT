# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 16:18:07 by albeninc          #+#    #+#              #
#    Updated: 2024/03/18 16:59:14 by albeninc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END=$'\033[0m'
_BOLD=$'\033[1m'
_UNDER=$'\033[4m'
_REV=$'\033[7m'

# Colors
_GREY=$'\033[30m'
_RED=$'\033[31m'
_GREEN=$'\033[32m'
_YELLOW=$'\033[33m'
_BLUE=$'\033[34m'
_PURPLE=$'\033[35m'
_CYAN=$'\033[36m'
_WHITE=$'\033[37m'

################################################################################
#                                VARIABLES									   #
################################################################################

SRCS_DIR		=	src/Engine
SRCS			=	$(shell find $(SRCS_DIR) -name '*.c')
MAIN_SRCS		=	$(SRCS_DIR)/main.c
NAME			= 	MiniRT
RM				= 	rm -rf
CC				=	gcc $(CFLAGS)
CFLAGS			=	-Wall -Werror -Wextra -IInclude -IInclude/libft/
LDFLAGS			=	-LInclude/libft -lft -lm
OBJECTS 		=	$(SRCS:.c=.o)
MLX_DIR			= ./minilibx
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -lXext -lX11
CFLAGS			+= -I$(MLX_DIR)

################################################################################
#                                MAIN RULES								       #
################################################################################

all:	$(NAME)

$(NAME):	$(OBJECTS)
	@echo "${_UNDER}${_RED}Creating binary for Project${_END}"
	@$(CC) -o $(NAME) $(OBJECTS) $(LDFLAGS) $(MLX_FLAGS)
	@echo "${_BOLD}${_GREEN}$(NAME) compiled successfully!${_END}"

%.o: %.c
	@echo "${_BOLD}${_BLUE}Compiling $<${_END}"
	@$(CC) $(CFLAGS) -c $< -o $@

################################################################################
#                              	TEST VARIABLES					   		   	   #
################################################################################

CR_HEADER_PATH	=	-I${HOME}/Criterion/include/criterion
T_NAME			= 	UNIT_TEST
T_SRCS			=	src/Unit_testing/unit-test.c
T_CC			=	gcc $(CFLAGS) $(CR_HEADER_PATH) $(CR_LIB_PATH) $(T_FLAGS)
CR_LIB_PATH     =   -L${HOME}/Criterion/build/src -Wl,-rpath=${HOME}/Criterion/build/src
T_FLAGS         =   -lcriterion $(CR_LIB_PATH)
# Test object files (add more as needed)
T_OBJECTS =	$(T_SRCS:.c=.o)

# Possibly needed source object files excluding main.o
# Adjust this list to include only the objects needed for testing
TESTED_OBJECTS := $(filter-out $(MAIN_SRCS:.c=.o), $(OBJECTS)) src/Engine/main.o

################################################################################
#                                TEST RULES                                    #
################################################################################


$(T_OBJECTS): %.o: %.c
	@echo "${_BOLD}${_BLUE}Compiling test $<${_END}"
	@$(CC) $(CFLAGS) $(CR_HEADER_PATH) -c $< -o $@

tests:	$(T_OBJECTS) $(TESTED_OBJECTS)
	@echo "${_UNDER}${_RED}Linking tests...${_END}"
	@$(CC) -o $(T_NAME) $(T_OBJECTS) $(TESTED_OBJECTS) $(LDFLAGS) $(T_FLAGS)
	@echo "${_BOLD}${_GREEN}Running tests...${_END}"
	@./$(T_NAME)



################################################################################
#                               	CLEANUP								       #
################################################################################

clean:
	@echo "${_UNDER}${_RED}Deleting Objects and Dependencies${_END}"
	@$(RM) $(OBJECTS) $(T_OBJECTS)
	@echo "${_BOLD}${_YELLOW}Cleanup complete${_END}"

fclean: clean
	@echo "${_UNDER}${_RED}Deleting Executable${_END}"
	@$(RM) $(NAME) $(T_NAME)
	@echo "${_BOLD}${_RED}Executable removed${_END}"

re:	fclean all

.PHONY:		all clean fclean re tests
