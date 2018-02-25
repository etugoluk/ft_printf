#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 13:43:50 by etugoluk          #+#    #+#              #
#    Updated: 2018/02/24 13:43:51 by etugoluk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

SRCS = main.c \
		struct.c \
		ft_put.c \
		itoa_base.c \
		unicode.c \
		print.c \
		count_digits.c \
		print_cs.c \
		print_ou.c \
		print_di.c \
		print_px.c \
		
INCLUDES = ft_printf.h

BINS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME)

$(NAME): $(BINS)
	ar rc $(NAME) $(BINS)
	ranlib $(NAME)

%.o: %.c
	gcc -I ./ -Wall -Wextra -Werror -o $@ -c $<

clean:
	rm -f $(BINS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	