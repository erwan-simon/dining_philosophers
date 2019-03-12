##
## Makefile for  in /home/antoine/Rendu/PSU_Concurrency/PSU_2016_philo
## 
## Made by Antoine
## Login   <antoine.roche@epitech.eu>
## 
## Started on  Mon Mar  6 15:55:52 2017 Antoine
## Last update Wed Mar 15 16:28:36 2017 Simon
##

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
