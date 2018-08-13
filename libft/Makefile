# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtan <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 17:49:03 by mtan              #+#    #+#              #
#    Updated: 2018/03/08 10:29:52 by mtan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

# compiler
CC 			= gcc
FLAGS 		= -Wall -Wextra -Werror
INC			= -I ./includes/

# directories
SRC_DIR		= srcs/
OBJ_DIR		= obj/

# files
SRC_FILES	= $(notdir $(wildcard $(SRC_DIR)*.c))

SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# colors
LIGHT_GREEN	=\x1b[32;01m
GREEN		=\033[1;0m\033[32m
WHITE		=\x1b[0m
YELLOW		=\033[33m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(GREEN)Binary $(LIGHT_GREEN)$(NAME) $(GREEN)created."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "$(YELLOW)Compiled: $(WHITE)$(notdir $<)"

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
