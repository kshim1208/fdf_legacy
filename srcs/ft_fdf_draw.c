/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:22:44 by kshim             #+#    #+#             */
/*   Updated: 2022/08/16 17:31:30 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>
#include <stdlib.h>

// rotate를 묶고, set -> prg -> rotate가 1일 때만 하기
void	ft_fdf_iter_draw_line(int i, int j, t_ft_fdf_data_set *set)
{
	t_ft_fdf_pnt_data	draw;
	t_ft_fdf_pnt_data	draw_prev_j;
	t_ft_fdf_pnt_data	draw_prev_i;

	ft_fdf_after_zoom(&draw, &(set -> pnt[i][j]), set -> prg);
	ft_fdf_rotate_axis_all(&draw, set);
	if ((draw.x > 0 && draw.x < set -> prg -> window[0])
		&& (draw.y > 0 && draw.y < set -> prg -> window[1]))
		ft_mlx_pixel_put(set -> img, draw.x,
			draw.y, draw.color);
	if (j != 0)
	{
		ft_fdf_after_zoom(&draw_prev_j, &(set -> pnt[i][j - 1]), set -> prg);
		ft_fdf_rotate_axis_all(&draw_prev_j, set);
		t_ft_fdf_draw_line(&draw, &draw_prev_j,
			set -> img, set);
	}
	if (i != 0)
	{
		ft_fdf_after_zoom(&draw_prev_i, &(set -> pnt[i - 1][j]), set -> prg);
		ft_fdf_rotate_axis_all(&draw_prev_i, set);
		t_ft_fdf_draw_line(&draw, &draw_prev_i,
			set -> img, set);
	}
	return ;
}

void	ft_fdf_after_zoom(t_ft_fdf_pnt_data *after_zoom,
	t_ft_fdf_pnt_data *bef_zoom, t_ft_fdf_prg_data *prg)
{
	after_zoom -> x = prg -> axis_pnt[0] - (
			prg -> zoom * (
				bef_zoom -> x - prg -> axis_pnt[0]));
	after_zoom -> y = prg -> axis_pnt[1] - (
			prg -> zoom * (
				bef_zoom -> y - prg -> axis_pnt[1]));
	after_zoom -> z = prg -> axis_pnt[2] - (
			prg -> zoom * (
				bef_zoom -> z - prg -> axis_pnt[2]));
	after_zoom -> color = bef_zoom -> color;
	return ;
}

//img와 set는 set로 합쳐도 됨
void	t_ft_fdf_draw_line(t_ft_fdf_pnt_data *pnt1, t_ft_fdf_pnt_data *pnt2,
		t_mlx_img_data *img, t_ft_fdf_data_set *set)
{
	double	length;
	double	height;
	int		x_variat;
	int		y_variat;
	int		i;
	double	mid;
	int		codomain;	// 이름 변경 필요. 사실 초기 y값 + 변동치가 codomain임

	length = fabs(pnt2 -> x - pnt1 -> x);
	height = fabs(pnt2 -> y - pnt1 -> y);
	if (pnt1 -> x < pnt2 -> x)
		x_variat = 1;
	else
		x_variat = -1;
	if (pnt1 -> y < pnt2 -> y)
		y_variat = 1;
	else
		y_variat = -1;
	codomain = 0;
	if (length > height)
	{
		i = x_variat;
		mid = (2 * height) - length;
		while ((x_variat == 1 && pnt1 -> x + i < pnt2 -> x)
			|| (x_variat == -1 && pnt1 -> x + i > pnt2 -> x))
		{
			if (mid < 0)
			{
				mid = mid + (2 * height);
			}
			else
			{
				mid = mid + (2 * height) - (2 * length);
				codomain += y_variat;
			}
			if ((pnt1 -> x + i > 0 && pnt1 -> x + i < set -> prg -> window[0])
				&& ((pnt1 -> y + codomain > 0) && (pnt1 -> y + codomain < set -> prg -> window[1])))
				ft_mlx_pixel_put(img, pnt1 -> x + i,
					pnt1 -> y + codomain, 0xFFFFFF);
			i += x_variat;
		}
	}
	else
	{
		i = y_variat;
		mid = (2 * length) - height;
		while ((y_variat == 1 && pnt1 -> y + i < pnt2 -> y)
			|| (y_variat == -1 && pnt1 -> y + i > pnt2 -> y))
		{
			if (mid < 0)
			{
				mid = mid + (2 * length);
			}
			else
			{
				mid = mid + (2 * length) - (2 * height);
				codomain += x_variat;
			}
			if ((pnt1 -> x + codomain > 0 && pnt1 -> x + codomain < set -> prg -> window[0])
				&& ((pnt1 -> y + i > 0) && (pnt1 -> y + i < set -> prg -> window[1])))
				ft_mlx_pixel_put(img, pnt1 -> x + codomain,
					pnt1 -> y + i, 0xFFFFFF);
			i += y_variat;
		}
	}
	return ;
}

void	ft_mlx_pixel_put(t_mlx_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data -> addr + (y * data -> line_length + x * (data -> bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return ;
}
