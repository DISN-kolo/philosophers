# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 13:41:10 by akozin            #+#    #+#              #
#    Updated: 2024/03/12 18:22:34 by akozin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

MAKE = make

CC = gcc
CFLAGS = -Wall -Wextra -Werror# -g -fsanitize=thread
SRCNAMES = data_init.c \
		   dinner.c \
		   free_bird.c \
		   ft_atol.c \
		   input_parser.c \
		   input_parser_utils_2.c \
		   input_parser_utils.c \
		   main.c \
		   monitor.c \
		   safe_funcs.c \
		   set.c \
		   set_2.c \
		   sync_utils.c \
		   utils.c \
		   write.c

SRCS = $(addprefix src/, $(SRCNAMES))
OBJS = $(SRCS:.c=.o)
DFILES = $(SRCS:.c=.d)

RM = rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS):	%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

-include $(DFILES)

clean:
	$(RM) $(OBJS) $(DFILES)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
