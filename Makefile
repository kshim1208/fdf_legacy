# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/05 14:14:37 by kshim             #+#    #+#              #
#    Updated: 2022/08/30 08:10:33 by kshim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG = -g
RM = rm
RMFLAGS = -f

MATHLIBOPTION = -lm

HEADERS = -I$(INCLUDE)

INCLUDE = ./include

SRCSDIR = ./srcs/

BONUS_SRCSDIR = ./srcs_bonus/

SRCS_FILES = fdf_main.c ft_fdf_parse_file.c ft_fdf_output.c ft_fdf_rotate.c ft_fdf_draw.c ft_fdf_mlx_img.c ft_fdf_key_event.c ft_fdf_utils.c ft_fdf_struct.c ft_fdf_exit.c ft_fdf_lst.c get_next_line.c

BONUS_SRCS_FILES = 

MLX_WSL2 = ./minilibx_linux

MLX_MACOS = ./mlx

MLX_FLAG_WSL2_UBUNTU = -L./minilibx_linux -lmlx -lXext -lX11

MLX_FLAG_CLUSTER_MACOS = -Lmlx -lmlx -framework OpenGL -framework AppKit 

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
	make -C $(MLX_MACOS) all
	make -C ./libft all
	$(CC) $(CFLAGS) $(DEBUG) $(HEADERS) $(OBJECTS) $(MATHLIBOPTION) -Llibft -lft $(MLX_FLAG_CLUSTER_MACOS) -o $(NAME)

%.o	: %.c
	$(CC) $(CFLAGS) $(DEBUG) $(HEADERS) -Imlx -c $< -o $@

all : $(NAME)

bonus: 
	make DO_BONUS=1 all
	
clean:
	make -C $(MLX_MACOS) clean
	make -C ./libft clean
	$(RM) $(RMFLAGS) $(OBJS) $(BONUS_OBJS)

fclean: clean
	-C $(MLX_MACOS) $(RM) $(RMFLAGS) libmlx.a
	make -C ./libft fclean
	$(RM) $(RMFLAGS) $(NAME)

re: 
	make fclean 
	make all

.PHONY:all bonus clean fclean re
