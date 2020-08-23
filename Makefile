# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/04 13:31:13 by mbenjell          #+#    #+#              #
#    Updated: 2017/09/18 12:40:00 by mbenjell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	tools.c \
		buffer.c \
		argument.c \
		format.c \
		format_unicode.c \
		conversion.c \
		writer.c \
		unicode.c \
		unicode_tools.c \
		ft_printf.c

FLAG = -Wall -Werror -Wextra

RM = /bin/rm -rf

OBJ = $(addsuffix .o, $(basename $(SRC)))

.PHONY: all clean fclean re

all: $(NAME)

%.o : %.c
	gcc -c $(FLAG) -o $@ $^

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all
