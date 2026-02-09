#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 13:08:28 by MP9               #+#    #+#              #
#    Updated: 2025/12/18 19:05:27 by MP9              ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

PRINTF_DIR = printf/srcs
OBJ_DIR = objs

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_putnbr_fd.c ft_putendl_fd.c \
		ft_putstr_fd.c ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c \
		ft_strtrim.c ft_split.c ft_strjoin.c ft_substr.c ft_sqrt.c ft_isspace.c\
		ft_atodub.c ft_free_matrix.c ft_matrixlen.c ft_realloc.c\

BONUSSRCS = ft_lstiter_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstmap_bonus.c \

PRINTF_SRCS = ft_printf.c ft_printf_utils.c ft_putchar.c ft_putnbr.c ft_putstr.c \

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUSOBJS = $(addprefix $(OBJ_DIR)/, $(BONUSSRCS:.c=.o))
PRINTF_OBJS = $(addprefix $(OBJ_DIR)/, $(PRINTF_SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(PRINTF_DIR)

all : $(NAME)

$(NAME): $(OBJS) $(PRINTF_OBJS)
		ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS)

bonus:  $(OBJS) $(BONUSOBJS) $(PRINTF_OBJS)
		ar rcs $(NAME) $(OBJS) $(BONUSOBJS) $(PRINTF_OBJS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ_DIR)
		@echo "library and object files cleaned." 

fclean: clean
		rm -f $(NAME)
		@echo "library and object files cleaned."

re: $(MAKE) fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re 