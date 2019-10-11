#!/bin/sh
SRCS = ft_printf.c
OBJS = ${SRCS:.c=.o}
NAME = libft.a
HEADER = .
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c -I ${HEADER} 

all : ${NAME}	

clean : 
		rm -f ${OBJS}

fclean : clean
		 rm -f ${NAME}

$(NAME) : ${OBJS}
		  ar rc ${NAME} ${OBJS}
		  ranlib ${NAME}

re : fclean all

.PHONY : all clean re fclean libft.a