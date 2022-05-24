# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcomic <jcomic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 16:35:28 by jcomic            #+#    #+#              #
#    Updated: 2021/12/21 16:35:29 by jcomic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c \
				ft_itoa.c \
				ft_atoi.c \
				globals.c \
				printer.c \
				spoons.c

OBJS		= ${SRCS:.c=.o}
DEPS		= ${SRCS:.c=.d}
NAME		= philo
CC			= gcc -g
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

all:		${NAME}


$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS}


%.o:		%.c
			${CC} ${CFLAGS} -c $< ${DEPFLAGS}

clean:
			${RM} ${OBJS} ${DEPS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
