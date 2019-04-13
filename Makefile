NAME	= philo

CC	= gcc

RM	= rm -f

SRCS	= ./threads.c	\
	  ./play.c	\
	  ./main.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I./
CFLAGS += -W -Wall -Wextra -Werror
LDFALGS = -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) -L. -lriceferee -lpthread

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
