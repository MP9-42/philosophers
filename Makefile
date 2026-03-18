# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 14:27:07 by MP9               #+#    #+#              #
#    Updated: 2026/03/18 14:41:53 by MP9              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

MAIN_DIR = objs

PHILO_FILES =	srcs/errors.c srcs/main.c srcs/parsing.c srcs/threads.c \
				srcs/utils1.c srcs/routine.c srcs/mutexes.c srcs/routine_utils.c \
				srcs/utils2.c \

OBJS = $(PHILO_FILES:srcs/%.c=$(MAIN_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/ -I./libft/includes/ \

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(MAIN_DIR)/%.o: srcs/%.c includes/philosophers.h
	@mkdir -p $(MAIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(MAIN_DIR)
		@echo "library and object files cleaned." 

fclean: clean
		rm -f $(NAME)
		@echo "Executable and library cleaned."

re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all bonus clean fclean re