# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/05 14:14:37 by kshim             #+#    #+#              #
#    Updated: 2022/07/28 17:15:36 by kshim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG = -g
RM = rm
RMFLAGS = -f

HEADERS = -I$(INCLUDE)

INCLUDE = ./include

SRCSDIR = ./srcs/

BONUS_SRCSDIR = ./srcs_bonus/

SRCS_FILES = fdf_main.c ft_fdf_parse_file.c ft_fdf_utils.c ft_fdf_exit.c get_next_line.c

BONUS_SRCS_FILES = 

SRCS = $(addprefix $(SRCSDIR), $(SRCS_FILES))

BONUS_SRCS = $(addprefix $(BONUS_SRCSDIR), $(BONUS_SRCS_FILES))

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef DO_BONUS
	OBJECTS = $(BONUS_OBJS)
else
	OBJECTS = $(OBJS)
endif

$(NAME): $(OBJECTS)
	make -C ./mlx all
	make -C ./libft all
	$(CC) $(CFLAGS) $(DEBUG) $(HEADERS) $(OBJECTS) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o	: %.c
	$(CC) $(CFLAGS) $(DEBUG) $(HEADERS) -Imlx -c $< -o $@

all : $(NAME)

bonus: 
	make DO_BONUS=1 all
	
clean:
	make -C ./mlx clean
	make -C ./libft clean
	$(RM) $(RMFLAGS) $(OBJS) $(BONUS_OBJS)

fclean: clean
	-C ./mlx $(RM) $(RMFLAGS) libmlx.a
	make -C ./libft fclean
	$(RM) $(RMFLAGS) $(NAME)

re: 
	make fclean 
	make all

.PHONY:all bonus clean fclean re
