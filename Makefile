# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 01:07:10 by mchliyah          #+#    #+#              #
#    Updated: 2022/03/25 20:00:07 by mchliyah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
#BONUS = pipex_bonus
CC = gcc
FLAGS =  -Wall -Werror -Wextra -c

RM = rm -f

FILES = \
		fdf.c

OBJECTS = $(FILES:.c=.o)

#FILES_bonus =	

#OBJECTS_bonus = $(FILES_bonus:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -c $^ -o $@

LIBFT = ./libft
ARLIB = $(LIBFT)/libft.a
ALLIBFT = make -C $(LIBFT)
CLEANLIBFT = make clean -C $(LIBFT)
FCLEANLIBFT = rm -f $(ARLIB)
RELIBFT = make re -C $(LIBFT)

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

.PHONY : all clean fclean rebonus

all : $(NAME)

$(NAME) :  $(OBJECTS)
	@$(ALLIBFT)
	@$(CC) $(FILES) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(C_GREEN)[FDF MANDATORY CREATED!]$(C_RES)"

#bonus : $(BONUS)

#$(BONUS) : $(OBJECTS_bonus)
#	@$(ALLIBFT)
#	@$(CC) $(FILES_bonus) -o $(BONUS)
#	@echo "$(C_L_BLUE)[FDF BONUS CREATED!]$(C_RES)"

clean : 
	@$(CLEANLIBFT)
	@$(RM) $(OBJECTS)
	@echo "$(C_RED)[FDF OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@$(FCLEANLIBFT)
	@$(RM) $(NAME)
	@echo "$(C_RED)[FDF && EXECUTABLES DELETED!]$(C_RES)"

re : fclean all

#rebonus : fclean bonus