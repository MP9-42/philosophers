#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 14:27:07 by MP9               #+#    #+#              #
#    Updated: 2026/02/09 14:35:43 by MP9              ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = philosophers

MAIN_DIR = objs

PHILO_FILES = srcs/errors.c srcs/main.c srcs/parsing.c \

OBJS = $(PHILO_FILES:srcs/%.c=$(MAIN_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/ -I./libft/includes/ \

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all : $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(MAIN_DIR)/%.o: srcs/%.c includes/philosophers.h
	@mkdir -p $(MAIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

clean:
		rm -rf $(MAIN_DIR)
		$(MAKE) clean -C $(LIBFT_DIR)
		@echo "library and object files cleaned." 

fclean: clean
		rm -f $(NAME)
		$(MAKE) fclean -C $(LIBFT_DIR)
		@echo "Executable and library cleaned."

re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all bonus clean fclean re