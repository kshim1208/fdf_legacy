/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:29:05 by kshim             #+#    #+#             */
/*   Updated: 2022/08/24 14:42:21 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>
// 반복문 돌리면서 한 번 세팅할 떄 x, y, z 점 회전만 호출하게 만드는게 낫겠다.
// 반복문 속에서 rotate_axis 계통을 호출하게 나중에 수정하자

// 2번 각 변환하기 - 축 함수 2번 사용 - 

void	ft_fdf_isomet_project(t_ft_fdf_data_set *set)
{
	set -> prg -> degree[0] = 0;
	set -> prg -> degree[1] = 0;
	set -> prg -> degree[2] = 45;
	return ;
}

void	ft_fdf_rotate_axis_all(t_ft_fdf_pnt_data *draw, t_ft_fdf_data_set *set)
{
	ft_fdf_rotate_axis_x(draw, set);
	ft_fdf_rotate_axis_y(draw, set);
	ft_fdf_rotate_axis_z(draw, set);
	return ;
}

// set의 degree를 받아서 그 각만큼 회전시킴
void	ft_fdf_rotate_axis_x(t_ft_fdf_pnt_data *draw, t_ft_fdf_data_set *set)
{
	double	rot;
	double	org_y;
	double	org_z;

	rot = set -> prg -> degree[0];
	org_y = draw -> y;
	org_z = draw -> z;
	draw -> y = (
			cos((M_PI / 180) * rot) * (org_y - (set -> prg -> axis_pnt[1])) + (
				(-1 * sin((M_PI / 180) * rot))) * (org_z - (set -> prg -> axis_pnt[2])))
		+ set -> prg -> axis_pnt[1];
	draw -> z = (
			sin((M_PI / 180) * rot) * (org_y - (set -> prg -> axis_pnt[1])) + (
				cos((M_PI / 180) * rot)) * (org_z - (set -> prg -> axis_pnt[2])))
		+ set -> prg -> axis_pnt[2];
	return ;
}

void	ft_fdf_rotate_axis_y(t_ft_fdf_pnt_data *draw, t_ft_fdf_data_set *set)
{
	int		rot;
	double	org_x;
	double	org_z;

	rot = set -> prg -> degree[1];
	org_x = draw -> x;
	org_z = draw -> z;
	draw -> x = (
			cos((M_PI / 180) * rot) * (org_x - (set -> prg -> axis_pnt[0])) + (
				sin((M_PI / 180) * rot)) * (org_z - (set -> prg -> axis_pnt[2])))
		+ set -> prg -> axis_pnt[0];
	draw -> z = (
			(-1 * sin((M_PI / 180) * rot)) * (org_x - (set -> prg -> axis_pnt[0])) + (
				cos((M_PI / 180) * rot)) * (org_z - (set -> prg -> axis_pnt[2])))
		+ set -> prg -> axis_pnt[2];
	return ;
}

void	ft_fdf_rotate_axis_z(t_ft_fdf_pnt_data *draw, t_ft_fdf_data_set *set)
{
	int		rot;
	double	org_x;
	double	org_y;

	rot = set -> prg -> degree[2];
	org_x = draw -> x;
	org_y = draw -> y;
	draw -> x = (
			cos((M_PI / 180) * rot) * (org_x - (set -> prg -> axis_pnt[0])) + (
				(-1 * sin((M_PI / 180) * rot))) * (org_y - (set -> prg -> axis_pnt[1])))
		+ set -> prg -> axis_pnt[0];
	draw -> y = ((
				sin((M_PI / 180) * rot) * (org_x - (set -> prg -> axis_pnt[0])) + (
					cos((M_PI / 180) * rot)) * (org_y - (set -> prg -> axis_pnt[1])))
			+ set -> prg -> axis_pnt[1]);
	return ;
}
