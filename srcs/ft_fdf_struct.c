/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:37:32 by kshim             #+#    #+#             */
/*   Updated: 2022/08/18 15:30:58 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../libft/libft.h"
#include <math.h>

void	ft_fdf_init_draw_line(t_ft_fdf_draw_line *line_data,
	t_ft_fdf_pnt_data *pnt1, t_ft_fdf_pnt_data *pnt2)
{
	ft_memset(line_data, 0, sizeof(t_ft_fdf_draw_line));
	line_data -> length = fabs(pnt2 -> x - pnt1 -> x);
	line_data -> height = fabs(pnt2 -> y - pnt1 -> y);
	if (pnt1 -> x < pnt2 -> x)
		line_data -> x_dir = 1;
	else
		line_data -> x_dir = -1;
	if (pnt1 -> y < pnt2 -> y)
		line_data -> y_dir = 1;
	else
		line_data -> y_dir = -1;
	line_data -> hex_power[0] = pow(16, 5);
	line_data -> hex_power[1] = pow(16, 4);
	line_data -> hex_power[2] = pow(16, 3);
	line_data -> hex_power[3] = pow(16, 2);
	line_data -> hex_power[4] = pow(16, 1);
	line_data -> hex_power[5] = pow(16, 0);
	ft_fdf_set_clr_change(line_data, pnt1 -> color, pnt2 -> color);
	line_data -> color = pnt1 -> color;
	return ;
}

void	ft_fdf_set_clr_change(t_ft_fdf_draw_line *line_data,
	int color_pnt1, int color_pnt2)
{
	int		pnt1[6];
	int		pnt2[6];
	double	longer_len_hei;

	ft_fdf_hex_diviner(color_pnt1, pnt1);
	ft_fdf_hex_diviner(color_pnt2, pnt2);
	line_data -> clr_change[0] = (pnt2[0] - pnt1[0]) * line_data -> hex_power[0]
		+ (pnt2[1] - pnt1[1]) * line_data -> hex_power[1];
	line_data -> clr_change[1] = (pnt2[2] - pnt1[2]) * line_data -> hex_power[2]
		+ (pnt2[3] - pnt1[3]) * line_data -> hex_power[3];
	line_data -> clr_change[2] = (pnt2[4] - pnt1[4]) * line_data -> hex_power[4]
		+ (pnt2[5] - pnt1[5]) * line_data -> hex_power[5];
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
