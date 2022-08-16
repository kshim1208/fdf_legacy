/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:21:38 by kshim             #+#    #+#             */
/*   Updated: 2022/08/16 14:38:02 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/fdf.h"
#include "stdlib.h"

void	ft_fdf_print(int i, int j, t_ft_fdf_data_set *set);
// img 파트는 따로 함수로 묶어내기 (loop_hook에서 사용)
// main 함수로 빼기

void	ft_fdf_mlx(t_ft_fdf_prg_data *prg, t_ft_fdf_pnt_data **pnt)
{
	t_ft_fdf_data_set	set;

	ft_fdf_init_mlx_set_data(&set, prg, pnt);
	ft_fdf_set_pnt_data(&set);
	ft_fdf_isomet_project(&set);
	ft_fdf_matrix_iterator(&set, ft_fdf_iter_draw_line);
	ft_fdf_mlx_loop(&set);
	return ;
}

void	ft_fdf_set_pnt_data(t_ft_fdf_data_set *set)
{
	t_ft_fdf_output_data	data;

	ft_memset(&data, 0, sizeof(t_ft_fdf_output_data));
	set -> output = &data;
	ft_fdf_init_output_data(set);
	set -> prg -> axis_pnt[0] = set -> prg -> window[0] / 2;
	set -> prg -> axis_pnt[1] = set -> prg -> window[1] / 2;
	set -> prg -> axis_pnt[2] = (set -> prg -> min_max_z[1])
		- (((set -> prg -> min_max_z[1]) - (set -> prg -> min_max_z[0])) / 2);
	ft_fdf_matrix_iterator(set, ft_fdf_set_x_y_len);
	set -> output = 0;
	return ;
}

void	ft_fdf_init_output_data(t_ft_fdf_data_set *set)
{
	set -> output -> wht_sp[0] = set -> prg -> window[0] / 4;
	set -> output -> wht_sp[1] = set -> prg -> window[1] / 4;
	set -> output -> org_pnt[0] = set -> output -> wht_sp[0];
	set -> output -> org_pnt[1] = set -> output -> wht_sp[1];
	if (set -> prg -> window[0] / ((set -> prg -> column) - 1)
		< set -> prg -> window[1] / ((set -> prg -> row) - 1))
	{
		set -> output -> pnt_len = (
				set -> output -> wht_sp[0] * 2) / ((set -> prg -> column) - 1);
		set -> output -> org_pnt[1] += ((set -> output -> wht_sp[1] * 2) - (
					(set -> prg -> row - 1) * set -> output -> pnt_len)) / 2;
	}
	else
	{
		set -> output -> pnt_len = (
				set -> output -> wht_sp[1] * 2) / ((set -> prg -> row) - 1);
		set -> output -> org_pnt[0] += ((set -> output -> wht_sp[0] * 2) - (
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
