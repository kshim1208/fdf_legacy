/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_parse_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:44:36 by kshim             #+#    #+#             */
/*   Updated: 2022/07/28 17:28:57 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>

/* 구조체 배열의 포인터 배열을 반환시키는게 나을까? */
t_ft_fdf_pnt_data	**ft_fdf_parse_file(char *filename)
{
	int					file_fd;
	t_ft_fdf_pnt_data	*struct_arr;
	t_ft_fdf_pnt_data	**struct_arr_ptr_arr;
	t_list				*tmp_lst;
	t_list				*tmp_ptr_lst;
	char				*gotten_line;
	int					gnl_ret;
	int					prev_len; // 이전 줄의 길이;
	int					len; // tmp_lst의 길이 - gl에서 parse한 값의 개수
	int					size; // struct_ptr_arr의 길이 - 구조체 배열의 개수
	// len과 size의 scope는 어디일까? 이 값을 어느 수준에서 관리할지 결정
	// gnl 파트는 parsing용 구조체에서 다루면 될 것 같음. 줄일 수 있으면 줄이고

	file_fd = open(filename, O_RDONLY);
	if (open < 0)
		ft_fdf_exit("ft_fdf_parse_file", FAIL_OPEN_FILE);
	prev_len = -1;
	len = 0;
	size = 0;
	while (1)
	{
		tmp_lst = 0;
		gnl_ret = get_next_line(file_fd, &gotten_line);
		if (gotten_line == 0 && gnl_ret < 0)
			ft_fdf_exit("ft_fdf_parse_file", FAIL_GNL);
		else if (gnl_ret == 0)
			break ; // 다 읽었을 때
		size++;
		ft_fdf_parse_gl_to_lst(gotten_line, tmp_lst, &len);
		if (prev_len == -1)
			prev_len = len;
		else
		{
			if (len != prev_len)
				ft_fdf_exit("fd_fdf_parse_file", FAIL_INPUT_LEN);
		}
		struct_arr = ft_fdf_set_val_to_s_lst(tmp_lst, len);
		if (struct_arr == 0)
			// error
		ft_lstclear(&tmp_lst, &(ft_fdf_del_value_ptr));
		tmp_lst = ft_lstnew(struct_arr);
		ft_lstadd_back(&(tmp_ptr_lst), tmp_lst);
		free(gotten_line);
		gotten_line = 0;
	}
	struct_arr_ptr_arr = ft_fdf_set_s_lst_to_ptr_lst(tmp_ptr_lst, size);
	if (struct_arr_ptr_arr == 0)
		// error
	ft_lstclear(&tmp_ptr_lst, 0);
	return (struct_arr_ptr_arr);
}

void	ft_fdf_parse_gl_to_lst(char *gl, t_list *val_list, int *len)
{
	char	*now;
	char 	*start;
	int		i;

	i = 0;
	now = gl;
	start = &(now[i]); 
	while (now[i] != 0)
	{

		if (i >= 0)
		{
			if (ft_isdigit(now[i]) == 0 && ft_issign(now[i] == 0)
				&& ft_isspace(now[i]) == 0)
				ft_fdf_exit("ft_fdf_parse_gl_to_lst", FAIL_INVAL_VALUE);
		}
		if (ft_isspace(now[i]) == 0)
		{
			start = &(now[i]);
			if (i == 0)
				i++;
			while (now[i] != 0)
			{
				if ((ft_issign(now[i - 1]) == 1 && ft_isdigit(now[i]) == 0)
					|| (ft_isdigit(now[i - 1]) == 1 && ft_issign(now[i]) == 1))
					ft_fdf_exit("ft_fdf_parse_gl_to_lst", FAIL_INVAL_VALUE);
				if (ft_isdigit(now[i - 1]) == 1 && ft_isspace(now[i]) == 1)
				{
					ft_fdf_set_gl_to_lst(start, val_list); // 숫자가 나오다가 공백 나옴 -> parsing해서 lst에 넣기
					len++;
					break ;
				}
				i++;
			}
		}
		i++;
	}	
	if ((ft_issign(now[i - 1]) == 1 && now[i] == '\0'))
		ft_fdf_exit("ft_fdf_parse_gl_to_lst", FAIL_INVAL_VALUE);
	return ;
}

void	ft_fdf_set_gl_to_lst(char *start, t_list *val_list)
{
	t_list				*tmp_list;
	int					value;
	int					*content_value;

 // 사용 불가능한 문자는 parse_gl_to_lst에서 이미 처리되니 제일 처음부터 atoi만 하면 됨, libft atoi는 보는 범위 넓으니 전용 atoi 필요할지도? 아니면 int만 감지하게 libft를 수정하자
	if (ft_atoi_fdf(start, &value) == 0)
		ft_fdf_exit("ft_fdf_set_gl_to_lst", FAIL_ATOI);
	content_value = (int *)malloc(sizeof(int));
	*content_value = value;
	tmp_list = ft_lstnew(content_value);
	if (tmp_list == 0)
		ft_fdf_exit("ft_fdf_set_gl_to_lst", FAIL_MEMORY_ALLOC);
	ft_lstadd_back(&val_list, tmp_list);
	return ;
}

t_ft_fdf_pnt_data	*ft_fdf_set_val_to_s_lst(t_list *val_list, int len)
{
	t_ft_fdf_pnt_data	*struct_arr;
	int					i;
	
	struct_arr = (t_ft_fdf_pnt_data *)malloc(sizeof(t_ft_fdf_pnt_data) * len);
	if (struct_arr == 0)
		ft_fdf_exit("ft_fdf_parse_file", FAIL_MEMORY_ALLOC);
	i = 0;
	while (i < len)
	{
		struct_arr[i].z = *((double *)(val_list -> content));
		val_list = val_list -> next;
		i++;
	}
	return (struct_arr);
}

t_ft_fdf_pnt_data	**ft_fdf_set_s_lst_to_ptr_lst(t_list *ptr_arr, int size)
{
	t_ft_fdf_pnt_data	**struct_arr_ptr_arr;
	int					i;
	
	struct_arr_ptr_arr = (t_ft_fdf_pnt_data **)malloc(sizeof(t_ft_fdf_pnt_data *) * size);
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