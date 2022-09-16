/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:37:32 by kshim             #+#    #+#             */
/*   Updated: 2022/09/16 14:58:22 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../libft/libft.h"
#include <math.h>

void	ft_fdf_init_draw_data(t_ft_fdf_data_set *set)
{
	set -> draw_data = (t_ft_fdf_draw_data *)malloc(sizeof(t_ft_fdf_draw_data));
	if (set -> draw_data == 0)
		ft_fdf_exit("ft_fdf_struct.c", FAIL_MEMORY_ALLOC);
	ft_memset(set -> draw_data, 0, sizeof(t_ft_fdf_draw_data));
	draw_data -> hex_power[0] = pow(16, 5);
	draw_data -> hex_power[1] = pow(16, 4);
	draw_data -> hex_power[2] = pow(16, 3);
	draw_data -> hex_power[3] = pow(16, 2);
	draw_data -> hex_power[4] = pow(16, 1);
	draw_data -> hex_power[5] = pow(16, 0);
	draw_data -> scale[0] = 1;
	draw_data -> scale[0] = 1;
	draw_data -> scale[0] = 1;
	draw_data -> scale[0] = 1;
	draw_data -> translate[0] = 1;
	draw_data -> translate[0] = 1;
	draw_data -> translate[0] = 1;
	draw_data -> translate[0] = 1;
}

void	ft_fdf_init_transform(t_ft_fdf_draw_data *draw_data)
{
	// 반복문으로 요약 가능
	draw_data -> transform[0][0] = 1;
	draw_data -> transform[0][1] = 0;
	draw_data -> transform[0][2] = 0;
	draw_data -> transform[0][3] = 0;
	draw_data -> transform[1][0] = 0;
	draw_data -> transform[1][1] = 1;
	draw_data -> transform[1][2] = 0;
	draw_data -> transform[1][3] = 0;
	draw_data -> transform[2][0] = 0;
	draw_data -> transform[2][1] = 0;
	draw_data -> transform[2][2] = 1;
	draw_data -> transform[2][3] = 0;
	draw_data -> transform[3][0] = 0;
	draw_data -> transform[3][1] = 0;
	draw_data -> transform[3][2] = 0;
	draw_data -> transform[3][3] = 1;
	return ;
}

void	ft_fdf_init_draw_line(t_ft_fdf_draw_line *line_data, t_ft_fdf_draw_data *draw_data,
	t_ft_fdf_pnt_data *pnt1, t_ft_fdf_pnt_data *pnt2)
{
	ft_memset(line_data, 0, sizeof(t_ft_fdf_draw_line));
	line_data -> length = fabs(pnt2 -> x - pnt1 -> x);
	line_data -> height = fabs((-1 * pnt2 -> y) - (-1 * pnt1 -> y));
	if (pnt1 -> x < pnt2 -> x)
		line_data -> x_dir = 1;
	else
		line_data -> x_dir = -1;
	if ((-1 * pnt1 -> y) < (-1 * pnt2 -> y))
		line_data -> y_dir = 1;
	else
		line_data -> y_dir = -1;
	ft_fdf_set_clr_change(line_data, draw_data, pnt1 -> color, pnt2 -> color);
	line_data -> color = pnt1 -> color;
	return ;
}

void	ft_fdf_set_clr_change(t_ft_fdf_draw_line *line_data, t_ft_fdf_draw_data *draw_data,
	int color_pnt1, int color_pnt2)
{
	int		pnt1[6];
	int		pnt2[6];
	double	longer_len_hei;

	ft_fdf_hex_diviner(color_pnt1, pnt1);
	ft_fdf_hex_diviner(color_pnt2, pnt2);
	line_data -> clr_change[0] = (pnt2[0] - pnt1[0]) * draw_data -> hex_power[0]
		+ (pnt2[1] - pnt1[1]) * draw_data -> hex_power[1];
	line_data -> clr_change[1] = (pnt2[2] - pnt1[2]) * draw_data -> hex_power[2]
		+ (pnt2[3] - pnt1[3]) * draw_data -> hex_power[3];
	line_data -> clr_change[2] = (pnt2[4] - pnt1[4]) * draw_data -> hex_power[4]
		+ (pnt2[5] - pnt1[5]) * draw_data -> hex_power[5];
	if (line_data -> length > line_data -> height)
		longer_len_hei = line_data -> length;
	else
		longer_len_hei = line_data -> height;
	line_data -> clr_change[0] = (
			line_data -> clr_change[0]) / longer_len_hei;
	line_data -> clr_change[1] = (
			line_data -> clr_change[1]) / longer_len_hei;
	line_data -> clr_change[2] = (
			line_data -> clr_change[2]) / longer_len_hei;
	return ;
}
