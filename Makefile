# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/11 22:28:04 by hdo-minh          #+#    #+#              #
#    Updated: 2018/12/12 19:12:57 by hdo-minh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = clang

SRC = main.c read.c solve.c utility.c

OBJ = $(SRC:.c=.o)

INCLUDES = -I libft/libft.h -I includes/fillit.h

LIBS = -L libft/ -lft

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	make -C libft/
	$(CC) -o $(NAME) $(OBJ) $(LIBS)

clean:
	make clean -C libft/
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)

.PHONY: all clean fclean re
