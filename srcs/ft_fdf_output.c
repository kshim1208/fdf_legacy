/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:21:38 by kshim             #+#    #+#             */
/*   Updated: 2022/08/30 10:00:37 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/fdf.h"
#include "stdlib.h"

// img 파트는 따로 함수로 묶어내기 (loop_hook에서 사용)
// main 함수로 빼기

void	ft_fdf_mlx(t_ft_fdf_prg_data *prg, t_ft_fdf_pnt_data **pnt,
			int argc, char **argv)
{
	t_ft_fdf_data_set	set;

	ft_fdf_init_mlx_set_data(&set, prg, pnt);
	ft_fdf_set_pnt_data(&set, argc, argv);
	ft_fdf_isomet_project(&set);
	ft_fdf_matrix_iterator(&set, ft_fdf_iter_draw_line);
	ft_fdf_mlx_loop(&set);
	return ;
}

void	ft_fdf_set_pnt_data(t_ft_fdf_data_set *set, int argc, char **argv)
{
	t_ft_fdf_output_data	data;

	ft_memset(&data, 0, sizeof(t_ft_fdf_output_data));
	set -> output = &data;
	ft_fdf_init_output_data(set);
	ft_fdf_check_pnt_len(set);

	ft_fdf_matrix_iterator(set, ft_fdf_set_x_y_len);
	set -> output = 0;

	int i = argc;
	char **s = argv;

	i = 0;
	s = 0;
	
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
	ft_fdf_set_pnt_len(set);
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

void	ft_fdf_check_pnt_len(t_ft_fdf_data_set *set)
{
	t_ft_fdf_pnt_data	check;

	// if로 묶기 -> 서로 다른 projection 쓸 경우
	ft_fdf_isomet_project(set);
	set -> pnt[0][0].x = set -> output -> org_pnt[0] + (
			(set -> output -> pnt_len));
	set -> pnt[0][0].y = set -> output -> org_pnt[1] + (
			(set -> output -> pnt_len));
	set -> pnt[0][0].y *= -1;
	check.x = set -> pnt[0][0].x;
	check.y = set -> pnt[0][0].y;
	check.z = set -> pnt[0][0].z;
	ft_fdf_rotate_axis_all(&check, set);
	if (check.y > set -> prg -> window[1])
	{
		// 얼마나 줄일 것인가?
		// 00 pnt의 y 좌표가 정사각형을 등각 투사했을 때의 y 좌표가 되도록 pnt_len을 조정
		// wht_sp[1] 과의 공식화 필요할 듯
	}
	set -> prg -> degree[0] = 0;
	set -> prg -> degree[2] = 0;
}

void	ft_fdf_set_x_y_len(int i, int j, t_ft_fdf_data_set *set)
{
	set -> pnt[i][j].x = set -> output -> org_pnt[0] + (
			(set -> output -> pnt_len) * j);
	set -> pnt[i][j].y = set -> output -> org_pnt[1] + (
			(set -> output -> pnt_len) * i);
	set -> pnt[i][j].y *= -1;
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
