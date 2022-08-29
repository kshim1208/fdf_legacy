/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_parse_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:44:36 by kshim             #+#    #+#             */
/*   Updated: 2022/08/24 11:56:11 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

t_ft_fdf_pnt_data	**ft_fdf_parse_file(char *filename,
		t_ft_fdf_prg_data *prg)
{
	t_ft_fdf_parse_data	parse;
	t_ft_fdf_pnt_data	**struct_arr_ptr_arr;
	int					file_fd;

	ft_memset(&parse, 0, sizeof(t_ft_fdf_parse_data));
	file_fd = open(filename, O_RDONLY);
	if (open < 0)
		ft_fdf_exit("ft_fdf_parse_file", FAIL_OPEN_FILE);
	parse.prev_len = -1;
	while (1)
	{
		if (ft_fdf_gnl(prg, &parse, file_fd) == 0)
			break ;
	}
	close(file_fd);
	struct_arr_ptr_arr = ft_fdf_set_s_lst_to_ptr_lst(
			parse.tmp_ptr_lst, prg -> row);
	if (struct_arr_ptr_arr == 0)
		ft_fdf_exit("ft_fdf_parse_file", FAIL_MEMORY_ALLOC);
	ft_lstclear(&(parse.tmp_ptr_lst), 0);
	return (struct_arr_ptr_arr);
}

int	ft_fdf_gnl(
		t_ft_fdf_prg_data *prg, t_ft_fdf_parse_data *parse, int file_fd)
{
	parse -> tmp_lst = 0;
	parse -> gotten_line = 0;
	parse -> gnl_ret = get_next_line(file_fd, &(parse -> gotten_line));
	if (parse -> gotten_line == 0 && parse -> gnl_ret < 0)
		ft_fdf_exit("ft_fdf_parse_file", FAIL_GNL);
	else if (parse -> gotten_line == 0 && parse -> gnl_ret == 0)
		return (0);
	(prg -> row)++;
	ft_fdf_parse_gl_to_lst(parse -> gotten_line, &parse -> tmp_lst,
		prg);
	if (parse -> prev_len == -1)
		parse -> prev_len = prg -> column;
	if (parse -> prev_len != prg -> column)
		ft_fdf_exit("fd_fdf_parse_file", FAIL_INPUT_LEN);
	parse -> struct_arr = ft_fdf_set_val_to_s_lst(
			parse -> tmp_lst, prg -> column);
	if (parse -> struct_arr == 0)
		ft_fdf_exit("ft_fdf_parse_file", FAIL_MEMORY_ALLOC);
	ft_lstclear(&(parse -> tmp_lst), &(ft_fdf_del_value_ptr));
	parse -> tmp_lst = ft_lstnew(parse -> struct_arr);
	ft_lstadd_back(&(parse -> tmp_ptr_lst), parse -> tmp_lst);
	free(parse -> gotten_line);
	return (1);
}

void	ft_fdf_parse_gl_to_lst(char *gl, t_list **val_list,
	t_ft_fdf_prg_data *prg)
{
	char	*now;
	char	*str_start;

	now = gl;
	prg -> column = 0;
	while (*now != '\0' && *now != '\n')
	{
		if (ft_isdigit(*now) == 0 && ft_issign(*now) == 0
			&& ft_isspace(*now) == 0 && *now != ',')
			ft_fdf_exit("ft_fdf_parse_gl_to_lst", FAIL_INVAL_VALUE);
		if (ft_isspace(*now) == 0)
		{
			str_start = now;
			ft_fdf_set_gl_to_lst(str_start, &now,
				val_list, prg -> min_max_z);
			(prg -> column)++;
			if (*now == '\0' || *now == '\n')
				return ;
		}
		now++;
	}
	return ;
}

void	ft_fdf_set_gl_to_lst(char *str_start, char **str_end,
	t_list **val_list, int min_max_z[])
{
	t_list				*tmp_list;
	t_value_list		*value_list;
	int					value;

	if (ft_atoi_fdf(str_start, str_end, &value) == 0)
		ft_fdf_exit("ft_fdf_set_gl_to_lst", FAIL_ATOI);
	value_list = (t_value_list *)malloc(sizeof(t_value_list));
	if (value_list == 0)
		ft_fdf_exit("ft_fdf_set_gl_to_lst", FAIL_MEMORY_ALLOC);
	ft_memset(value_list, 0, sizeof(t_value_list));
	if (value >= min_max_z[1])
		min_max_z[1] = value;
	if (value <= min_max_z[0])
		min_max_z[0] = value;
	value_list -> val = value;
	if (**str_end == ',')
	{
		if (ft_hex_atoi_fdf(*str_end, str_end, &value) == 0)
			ft_fdf_exit("ft_fdf_set_gl_to_lst", FAIL_HEX_ATOI);
		value_list -> color = value;
	}
	else
		value_list -> color = 0xFFFFFF;
	tmp_list = ft_lstnew(value_list);
	if (tmp_list == 0)
		ft_fdf_exit("ft_fdf_set_gl_to_lst", FAIL_MEMORY_ALLOC);
	ft_lstadd_back(val_list, tmp_list);
	return ;
}

t_ft_fdf_pnt_data	*ft_fdf_set_val_to_s_lst(t_list *val_list, int len)
{
	t_ft_fdf_pnt_data	*struct_arr;
	int					i;

	struct_arr = (t_ft_fdf_pnt_data *)malloc(sizeof(t_ft_fdf_pnt_data) * len);
	if (struct_arr == 0)
		ft_fdf_exit("ft_fdf_parse_file", FAIL_MEMORY_ALLOC);
	ft_memset(struct_arr, 0, sizeof(t_ft_fdf_pnt_data) * len);
	i = 0;
	while (i < len)
	{
		struct_arr[i].z = ((t_value_list *)(val_list -> content))-> val;
		struct_arr[i].color = ((t_value_list *)(val_list -> content))-> color;
		val_list = val_list -> next;
		i++;
	}
	return (struct_arr);
}

t_ft_fdf_pnt_data	**ft_fdf_set_s_lst_to_ptr_lst(t_list *ptr_arr, int size)
{
	t_ft_fdf_pnt_data	**struct_arr_ptr_arr;
	int					i;

	struct_arr_ptr_arr = (t_ft_fdf_pnt_data **)malloc(
			sizeof(t_ft_fdf_pnt_data *) * size);
	if (struct_arr_ptr_arr == 0)
		ft_fdf_exit("ft_fdf_parse_file", FAIL_MEMORY_ALLOC);
	i = 0;
	while (i < size)
	{
		struct_arr_ptr_arr[i] = (t_ft_fdf_pnt_data *)(ptr_arr -> content);
		ptr_arr = ptr_arr -> next;
		i++;
	}
	return (struct_arr_ptr_arr);
}
