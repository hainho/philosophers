CC = gcc
CFLAGS = -Wextra -Werror -Wall

NAME = philo

DIR_H = ./include/
DIR_S = ./src/
DIR_O = ./

SRC =	free.c	\
		ft_utils.c	\
		init.c	\
		main.c	\
		philo_action.c	\
		philo_utils.c		\
		philo.c	\
		validation.c	\

SRCS = $(addprefix $(DIR_S), $(SRC))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re