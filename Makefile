# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 13:41:10 by akozin            #+#    #+#              #
#    Updated: 2024/03/07 15:55:58 by akozin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

MAKE = make

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCNAMES = main.c \
		   input_parser.c \
		   input_parser_utils.c

SRCS = $(addprefix src/, $(SRCNAMES))
OBJS = $(SRCS:.c=.o)
DFILES = $(SRCS:.c=.d)

RM = rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) #-fsanitize=address

$(OBJS):	%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $< #-fsanitize=address

-include $(DFILES)

clean:
	$(RM) $(OBJS) $(DFILES)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
