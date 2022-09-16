/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:39:54 by kshim             #+#    #+#             */
/*   Updated: 2022/09/16 13:34:58 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/fdf.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_ft_fdf_prg_data	prg_data;
	t_ft_fdf_pnt_data	**pnt_data;

	ft_memset(&prg_data, 0, sizeof(t_ft_fdf_prg_data));
	if (argc < 2)
		ft_fdf_exit("main", FAIL_INPUT);
	pnt_data = ft_fdf_parse_file(argv[1], &prg_data);
	prg_data.window[0] = 1600;
	prg_data.window[1] = 900;
	prg_data.print = 0;
	prg_data.zoom = 1;
	ft_fdf_mlx(&prg_data, pnt_data);
	ft_fdf_free_str_arr_ptr_arr(&prg_data, pnt_data);
	// draw_data, after_pnt도 처리 해야함.
	return (0);
}
