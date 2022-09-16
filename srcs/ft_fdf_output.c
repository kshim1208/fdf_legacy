/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:21:38 by kshim             #+#    #+#             */
/*   Updated: 2022/09/16 16:03:42 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/fdf.h"
#include "stdlib.h"

// img 파트는 따로 함수로 묶어내기 (loop_hook에서 사용)
// main 함수로 빼기

void	ft_fdf_mlx(t_ft_fdf_prg_data *prg, t_ft_fdf_pnt_data **pnt)
{
	t_ft_fdf_data_set	set;

	ft_fdf_init_mlx_set_data(&set, prg, pnt);
	ft_fdf_set_pnt_data(&set);
	ft_fdf_init_draw_data(&set);
	ft_fdf_isomet_project(&set);
	ft_fdf_set_transformation(&set);
	ft_fdf_matrix_iterator(&set, ft_fdf_iter_draw_line);
	ft_fdf_mlx_loop(&set);
	// after_pnt, draw_data, mlx 해제 처리
	return ;
}

void	ft_fdf_set_pnt_data(t_ft_fdf_data_set *set)
{
	t_ft_fdf_output_data	data;

	ft_memset(&data, 0, sizeof(t_ft_fdf_output_data));
	set -> output = &data;
	ft_fdf_init_output_data(set);
	ft_fdf_set_pnt_len(set);
	ft_fdf_matrix_iterator(set, ft_fdf_set_x_y_len);
	ft_fdf_init_after_pnt(set);
	ft_fdf_matrix_iterator(set, ft_fdf_set_x_y_after_pnt);
	set -> output = 0;
	return ;
}

void	ft_fdf_init_output_data(t_ft_fdf_data_set *set)
{
	set -> output -> wht_sp[0] = set -> prg -> window[0] / 5;
	set -> output -> wht_sp[1] = set -> prg -> window[1] / 5;
	set -> output -> org_pnt[0] = set -> output -> wht_sp[0];
	set -> output -> org_pnt[1] = set -> output -> wht_sp[1];
	set -> prg -> axis_pnt[0] = set -> prg -> window[0] / 2;
	set -> prg -> axis_pnt[1] = -1 * (set -> prg -> window[1] / 2);
	set -> prg -> axis_pnt[2] = (set -> prg -> min_max_z[1])
		- (((set -> prg -> min_max_z[1]) - (set -> prg -> min_max_z[0])) / 2);
	return ;
}

void	ft_fdf_set_pnt_len(t_ft_fdf_data_set *set)
{
	if (set -> prg -> window[0] / ((set -> prg -> column) - 1)
		< set -> prg -> window[1] / ((set -> prg -> row) - 1))
	{
		set -> output -> pnt_len = (
				set -> output -> wht_sp[0] * 3) / ((set -> prg -> column) - 1);
		set -> output -> org_pnt[1] += ((set -> output -> wht_sp[1] * 3) - (
					(set -> prg -> row - 1) * set -> output -> pnt_len)) / 2;
	}
	else
	{
		set -> output -> pnt_len = (
				set -> output -> wht_sp[1] * 3) / ((set -> prg -> row) - 1);
		set -> output -> org_pnt[0] += ((set -> output -> wht_sp[0] * 3) - (
					(set -> prg -> column - 1) * set -> output -> pnt_len)) / 2;
	}
	return ;
}

void	ft_fdf_set_x_y_len(int i, int j, t_ft_fdf_data_set *set)
{
	set -> pnt[i][j].x = set -> output -> org_pnt[0] + (
			(set -> output -> pnt_len) * j);
	set -> pnt[i][j].y = set -> output -> org_pnt[1] + (
			(set -> output -> pnt_len) * i);
	set -> pnt[i][j].y *= -1;
	set -> pnt[i][j].is_pnt = 1;
	return ;
}

void	ft_fdf_init_after_pnt(t_ft_fdf_data_set *set)
{
	int	i;

	set -> after_pnt = (t_ft_fdf_pnt_data **)malloc(
			sizeof(t_ft_fdf_pnt_data *) * set -> prg -> row);
	if (set -> after_pnt == 0)
		ft_fdf_exit("ft_fdf_output.c", FAIL_MEMORY_ALLOC);
	i = 0;
	while (i < set -> prg -> row)
	{
		set -> after_pnt[i] = (t_ft_fdf_pnt_data *)malloc(
				sizeof(t_ft_fdf_pnt_data) * set -> prg -> column);
		if (set -> after_pnt[i] == 0)
		ft_fdf_exit("ft_fdf_output.c", FAIL_MEMORY_ALLOC);
		i++;
	}
	return ;
}

void	ft_fdf_set_x_y_after_pnt(int i, int j, t_ft_fdf_data_set *set)
{
	set -> after_pnt[i][j].x = set -> pnt[i][j].x;
	set -> after_pnt[i][j].y = set -> pnt[i][j].y;
	set -> after_pnt[i][j].z = set -> pnt[i][j].z;
	set -> after_pnt[i][j].color = set -> pnt[i][j].color;
	set -> after_pnt[i][j].is_pnt = set -> pnt[i][j].is_pnt;
	return ;
}

void	ft_fdf_set_transform(t_ft_fdf_data_set *set)
{
	ft_fdf_init_transform(set -> draw_data);
	//scale matrix
	ft_fdf_scale_transform(set -> draw_data);
	//rotation matrix
	if (set -> prg -> rotation == 1)
		ft_fdf_rotate_axis_all(set);
	//translate matrix
	return ;
}

void	ft_fdf_scale_transform(t_ft_fdf_draw_data *draw_data)
{
	draw_data -> transform[0][0] = draw_data -> scale[0];
	draw_data -> transform[1][1] = draw_data -> scale[1];
	draw_data -> transform[2][2] = draw_data -> scale[2];
	return ;
}

//test 함수 - 삭제 필요
void	ft_fdf_print(int i, int j, t_ft_fdf_data_set *set)
{
	if (j == 0)
		printf("\n");
	printf("x : %.f, y : %.f, z : %.f|", set -> pnt[i][j].x, set -> pnt[i][j].y, set -> pnt[i][j].z);
	if (i == set -> prg -> row)
		printf("\n");
	return ;
}
