#!/bin/sh
SRCS = ft_printf.c \
	ft_size.c \
	ft_putnbr_base.c \
	ft_putnbr_base_p.c \
	ft_count.c \
	ft_countnbr.c \
	ft_write.c \
	ft_check.c \
	ft_atoi.c \
	ft_fill_caract.c \
	ft_putstr_n.c \
	ft_isdigit.c \
	ft_strlen.c
OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a
HEADER = .
CC = gcc
CFLAGS = -c -I ${HEADER} 

all : ${NAME}	

clean : 
		rm -f ${OBJS}

fclean : clean
		 rm -f ${NAME}

$(NAME) : ${OBJS}
		  ar rc ${NAME} ${OBJS}
		  ranlib ${NAME}

re : fclean all

.PHONY : all clean re fclean