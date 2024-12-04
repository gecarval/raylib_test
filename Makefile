CC = gcc
NAME = render
CFLAGS = -Wall -Wextra -Werror
INCS = -I./includes -L./includes/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS = ./srcs/main.c

OBJS = ${SRCS:.c=.o}
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
