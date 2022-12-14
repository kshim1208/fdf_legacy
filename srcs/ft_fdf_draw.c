/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:22:44 by kshim             #+#    #+#             */
/*   Updated: 2022/09/16 16:01:51 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>
#include <stdlib.h>

// 어느 점부터, 어느 방향으로 연결할 지 고려할 수 있는가?
// 현재 메커니즘은 어떠한 문제가 있는가? 

/*
void	ft_fdf_iter_draw_line(int i, int j, t_ft_fdf_data_set *set)
{
	t_ft_fdf_pnt_data	draw;
	t_ft_fdf_pnt_data	draw_prev_i;
	t_ft_fdf_pnt_data	draw_prev_j;

	ft_fdf_after_zoom(&draw, &(set -> after_pnt[i][j]), set);
	ft_fdf_rotate_axis_all(&draw, set);
	if ((draw.x > 0 && draw.x < set -> prg -> window[0])
		&& ((-1 * draw.y) > 0 && (-1 * draw.y) < set -> prg -> window[1]))
		ft_mlx_pixel_put(set -> img, draw.x,
			(-1 * draw.y), draw.color);
	if (j != 0)
	{
		ft_fdf_after_zoom(&draw_prev_j, &(set -> after_pnt[i][j - 1]), set -> prg);
		ft_fdf_rotate_axis_all(&draw_prev_j, set);
		ft_fdf_draw_line(&draw, &draw_prev_j, set);
	}
	if (i != 0)
	{
		ft_fdf_after_zoom(&draw_prev_i, &(set -> after_pnt[i - 1][j]), set -> prg);
		ft_fdf_rotate_axis_all(&draw_prev_i, set);
		ft_fdf_draw_line(&draw, &draw_prev_i, set);
	}
	return ;
}
*/

void	ft_fdf_iter_draw_line(int i, int j, t_ft_fdf_data_set *set)
{
	t_ft_fdf_pnt_data	draw;
	t_ft_fdf_pnt_data	draw_prev_i;
	t_ft_fdf_pnt_data	draw_prev_j;

	//transformation 행렬 만든 다음에 각 점에 적용 가능
	// ft_fdf_after_zoom(&draw, &(set -> after_pnt[i][j]), set);
	// ft_fdf_rotate_axis_all(&draw, set);

	if ((draw.x > 0 && draw.x < set -> prg -> window[0])
		&& ((-1 * draw.y) > 0 && (-1 * draw.y) < set -> prg -> window[1]))
		ft_mlx_pixel_put(set -> img, draw.x,
			(-1 * draw.y), draw.color);
	if (j != 0)
	{
		// ft_fdf_after_zoom(&draw_prev_j, &(set -> after_pnt[i][j - 1]), set -> prg);
		// ft_fdf_rotate_axis_all(&draw_prev_j, set);
		ft_fdf_draw_line(&draw, &draw_prev_j, set);
	}
	if (i != 0)
	{
		// ft_fdf_after_zoom(&draw_prev_i, &(set -> after_pnt[i - 1][j]), set -> prg);
		// ft_fdf_rotate_axis_all(&draw_prev_i, set);
		ft_fdf_draw_line(&draw, &draw_prev_i, set);
	}
	return ;
}

/*
void	ft_fdf_after_zoom(t_ft_fdf_pnt_data *after_zoom,
	t_ft_fdf_pnt_data *bef_zoom, t_ft_fdf_data_set *set)
{
	after_zoom -> x = set -> prg -> axis_pnt[0] + (
			set -> draw_data -> scale[0] * (
				bef_zoom -> x - set -> prg -> axis_pnt[0]));
	after_zoom -> y = set -> prg -> axis_pnt[1] + (
			set -> draw_data -> scale[1] * (
				bef_zoom -> y - set -> prg -> axis_pnt[1]));
	after_zoom -> z = set -> prg -> axis_pnt[2] + (
			set -> draw_data -> scale[2] * (
				bef_zoom -> z - set -> prg -> axis_pnt[2]));
	after_zoom -> color = bef_zoom -> color;
	return ;
}
*/

// 조건 잘 설정하면 첫 번째 if문을 합칠 수 있을 것 같음
void	ft_fdf_draw_line(t_ft_fdf_pnt_data *pnt1, t_ft_fdf_pnt_data *pnt2,
		t_ft_fdf_data_set *set)
{
	t_ft_fdf_draw_line	line_data;

	ft_fdf_init_draw_line(&line_data, pnt1, pnt2);
	if (line_data.length > line_data.height)
	{
		line_data.i = line_data.x_dir;
		line_data.mid = (2 * line_data.height) - line_data.length;
		while ((line_data.x_dir == 1 && pnt1 -> x + line_data.i < pnt2 -> x)
			|| (line_data.x_dir == -1 && pnt1 -> x + line_data.i > pnt2 -> x))
		{
			if (line_data.mid < 0)
			{
				line_data.mid = line_data.mid + (2 * line_data.height);
			}
			else
			{
				line_data.mid = line_data.mid + (2 * line_data.height) - (2 * line_data.length);
				line_data.codomain += line_data.y_dir;
			}
			ft_fdf_line_pixel_color(&line_data, set -> draw_data);
			if ((pnt1 -> x + line_data.i > 0 && pnt1 -> x + line_data.i < set -> prg -> window[0])
				&& ((-1 * pnt1 -> y + line_data.codomain > 0) && (-1 * pnt1 -> y + line_data.codomain < set -> prg -> window[1])))
				ft_mlx_pixel_put(set -> img, pnt1 -> x + line_data.i,
					-1 * pnt1 -> y + line_data.codomain, line_data.color);
			line_data.i += line_data.x_dir;
		}
	}
	else
	{
		line_data.i = line_data.y_dir;
		line_data.mid = (2 * line_data.length) - line_data.height;
		while ((line_data.y_dir == 1 && -1 * pnt1 -> y + line_data.i < -1 * pnt2 -> y)
			|| (line_data.y_dir == -1 && -1 * pnt1 -> y + line_data.i > -1 * pnt2 -> y))
		{
			if (line_data.mid < 0)
			{
				line_data.mid = line_data.mid + (2 * line_data.length);
			}
			else
			{
				line_data.mid = line_data.mid + (2 * line_data.length) - (2 * line_data.height);
				line_data.codomain += line_data.x_dir;
			}
			ft_fdf_line_pixel_color(&line_data, set -> draw_data);
			if ((pnt1 -> x + line_data.codomain > 0 && pnt1 -> x + line_data.codomain < set -> prg -> window[0])
				&& (-1 * pnt1 -> y + line_data.i > 0) && (-1 * pnt1 -> y + line_data.i < set -> prg -> window[1]))
				ft_mlx_pixel_put(set -> img, pnt1 -> x + line_data.codomain,
					-1 * pnt1 -> y + line_data.i, line_data.color);
			line_data.i += line_data.y_dir;
		}
	}
	return ;
}

void	ft_fdf_line_pixel_color(t_ft_fdf_draw_line *line_data, t_ft_fdf_draw_data *draw_data)
{
	int	var;

	line_data -> clr_accum[0] += line_data -> clr_change[0];
	if ((line_data -> clr_change[0] < 0 && (-1 * line_data -> clr_accum[0]) >= draw_data -> hex_power[1])
		|| (line_data -> clr_change[0] > 0 && line_data -> clr_accum[0] >= draw_data -> hex_power[1]))
	{
		if (line_data -> clr_change[0] < 0)
			var = ft_fdf_calc_color_change(&(line_data -> clr_accum[0]), -1 * draw_data -> hex_power[1]);
		else
			var = ft_fdf_calc_color_change(&(line_data -> clr_accum[0]), draw_data -> hex_power[1]);
		line_data -> color += var;
	}
	line_data -> clr_accum[1] += line_data -> clr_change[1];
	if ((line_data -> clr_change[1] < 0 && (-1 * line_data -> clr_accum[1]) >= draw_data -> hex_power[3])
		|| (line_data -> clr_change[1] > 0 && line_data -> clr_accum[1] >= draw_data -> hex_power[3]))
	{
		if (line_data -> clr_change[1] < 0)
			var = ft_fdf_calc_color_change(&(line_data -> clr_accum[1]), -1 * draw_data -> hex_power[3]);
		else
			var = ft_fdf_calc_color_change(&(line_data -> clr_accum[1]), draw_data -> hex_power[3]);
		line_data -> color += var;
	}
	line_data -> clr_accum[2] += line_data -> clr_change[2];
	if ((line_data -> clr_change[2] < 0 && (-1 * line_data -> clr_accum[2]) >= draw_data -> hex_power[5])
		|| (line_data -> clr_change[2] > 0 && line_data -> clr_accum[2] >= draw_data -> hex_power[5]))
	{
		if (line_data -> clr_change[2] < 0)
			var = ft_fdf_calc_color_change(&(line_data -> clr_accum[2]), -1 * draw_data -> hex_power[5]);
		else
			var = ft_fdf_calc_color_change(&(line_data -> clr_accum[2]), draw_data -> hex_power[5]);
		line_data -> color += var;
	}
	return ;
}

int	ft_fdf_calc_color_change(double *clr_accum, int hex_power)
{
	int	i;
	int	var;

	i = 0;
	var = 0;
	if (hex_power > 0)
	{
		while (*clr_accum >= hex_power)
		{
			*clr_accum = *clr_accum - hex_power;
			i++;
		}
		var = i * hex_power;
	}
	else if (hex_power < 0)
	{
		while (*clr_accum <= hex_power)
		{
			*clr_accum = *clr_accum - hex_power;
			i++;
		}
		var = i * hex_power;
	}
	return (var);
}

void	ft_mlx_pixel_put(t_mlx_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data -> addr + (y * data -> line_length + x * (data -> bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return ;
}