
NAME = libftprintf.a

SRCS = main.c \
		ft_put.c \
		ft_strlen.c \
		itoa_base.c \

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
	