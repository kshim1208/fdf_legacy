/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:29:05 by kshim             #+#    #+#             */
/*   Updated: 2022/09/16 16:50:01 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../libft/libft.h"
#include <math.h>

	// scale, rotation, translation 한 번에 결합법칙으로 계산하는게 성능은 좋음.
	// 그런데 그렇게 쓸 일이 있을까?
	//		-> 각도에선 rotation에 해당하는 matrix만 계산 및 결합
	//		draw 함수에서 scale과 rotation 곱하고, 그 후 translation 곱하기

void	ft_fdf_isomet_project(t_ft_fdf_data_set *set)
{
	set -> draw_data -> rotate[0] = 30;
	set -> draw_data -> rotate[2] = 45;
	return ;
}

void	ft_fdf_rotate_axis_all(t_ft_fdf_data_set *set)
{
	// 나중에 각도 회전 순서에 따른 경우의 수 반영
	ft_fdf_rotate_sin_cos(set -> draw_data);
	ft_fdf_rotate_axis_z(set -> draw_data, set -> draw_data -> transform);
	ft_fdf_rotate_axis_y(set);
	ft_fdf_rotate_axis_x(set);
	ft_fdf_rotate_set_0(set);
	return ;
}

void ft_fdf_rotate_sin_cos(t_ft_fdf_draw_data *draw_data);
{
	if (draw_data -> rotate[0] != 0)
	{
		draw_data -> sin_theta[0] = sin((M_PI / 180) * set -> draw_data -> rotate[0]);
		draw_data -> cos_theta[0] = cos((M_PI / 180) * set -> draw_data -> rotate[0]);
	}
	if (draw_data -> rotate[1] != 0)
	{
		draw_data -> sin_theta[1] = sin((M_PI / 180) * set -> draw_data -> rotate[1]);
		draw_data -> cos_theta[1] = cos((M_PI / 180) * set -> draw_data -> rotate[1]);
	}
	if (draw_data -> rotate[2] != 0)
	{
		draw_data -> sin_theta[2] = sin((M_PI / 180) * set -> draw_data -> rotate[2]);
		draw_data -> cos_theta[2] = cos((M_PI / 180) * set -> draw_data -> rotate[2]);
	}
	return ;
}

void	ft_fdf_rotate_set_0(t_ft_fdf_data_set *set);
{
	set -> draw_data -> rotate[0] = 0;
	set -> draw_data -> rotate[1] = 0;
	set -> draw_data -> rotate[2] = 0;
	return ;
}

void	ft_fdf_rotate_axis_z(t_ft_fdf_draw_data *draw_data,
			double **trans)
{	
	double	z[4][4];
	double	tmp[4][4];
	
	z[0][0] = draw_data -> cos_theta[2];
	z[0][1] = draw_data -> sin_theta[2];
	z[1][0] = -1 * (draw_data -> sin_theta[2]);
	z[1][1] = draw_data -> cos_theta[2];
	z[2][2] = 1;
	z[3][3] = 1;
	ft_fdf_cpy_matrix(trans, tmp);
	ft_fdf_multiply_matrix(trans, z, tmp);
	return ;
}

void	ft_fdf_rotate_axis_y(t_ft_fdf_draw_data *draw_data,
			double **trans)
{
	double	y[4][4];
	double	tmp[4][4];
	
	y[0][0] = draw_data -> cos_theta[1];
	y[0][2] = -1 * (draw_data -> sin_theta[1]);
	y[1][1] = 1;
	y[2][0] = draw_data -> sin_theta[1];
	y[2][2] = draw_data -> cos_theta[1];
	y[3][3] = 1;
	ft_fdf_cpy_matrix(trans, tmp);
	ft_fdf_multiply_matrix(trans, y, tmp);
	return ;
}

void	ft_fdf_rotate_axis_x(t_ft_fdf_draw_data *draw_data,
			double **trans)
{
	double	x[4][4];
	double	tmp[4][4];
	
	x[0][0] = 1;
	x[1][1] = draw_data -> cos_theta[0];
	x[1][2] = draw_data -> sin_theta[0];
	x[2][1] = -1 * (draw_data -> sin_theta[0]);
	x[2][2] = draw_data -> cos_theta[0];
	x[3][3] = 1;
	ft_fdf_cpy_matrix(trans, tmp);
	ft_fdf_multiply_matrix(trans, x, tmp);
	return ;
}
