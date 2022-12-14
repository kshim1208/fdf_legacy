/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:24:09 by kshim             #+#    #+#             */
/*   Updated: 2022/09/16 14:03:58 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../mlx/mlx.h"

// 회전 함수 구조 조절
// key event에서 실행하기 좋은 형태 고려
// 반복문을 어떻게 다루는게 좋을까? iterate 함수를 만들까?


// 각도는 rotate 변경으로 바꿈
int	ft_fdf_key_event(int key, t_ft_fdf_data_set *set)
{
	set -> prg -> print = 1;
	if (key == KEY_W_X)
	{
		set -> prg -> rotation = 1;
		set -> draw_data -> rotate[0] += 5;
	}
	else if (key == KEY_S_X_R)
	{
		set -> prg -> rotation = 1;
		set -> draw_data -> rotate[0] -= 5;
	}
	else if (key == KEY_D_Y)
	{
		set -> prg -> rotation = 1;
		set -> draw_data -> rotate[1] += 5;
	}
	else if (key == KEY_A_Y_R)
	{
		set -> prg -> rotation = 1;
		set -> draw_data -> rotate[1] -= 5;
	}
	else if (key == KEY_R_Z)
	{
		set -> prg -> rotation = 1;
		set -> draw_data -> rotate[2] += 5;
	}
	else if (key == KEY_F_Z_R)
	{
		set -> prg -> rotation = 1;
		set -> draw_data -> rotate[2] -= 5;
	}
	else if (key == KEY_Q_ZOOMIN)
	{
		set -> prg -> zoom = 1
		if (set -> draw_data -> scale[0] == 5.0)
		{
			set -> prg -> zoom = 0;
			return ;
		}
		set -> draw_data -> scale[0] += 0.1;
		set -> draw_data -> scale[1] += 0.1;
		set -> draw_data -> scale[2] += 0.1;
	}
	else if (key == KEY_E_ZOOMOUT)
	{
		set -> prg -> zoom = 1;
		if (set -> draw_data -> scale[0] == 0.1)
		{
			set -> prg -> zoom = 0;
			return ;
		}
		set -> draw_data -> scale[0] -= 0.1;
		set -> draw_data -> scale[1] -= 0.1;
		set -> draw_data -> scale[2] -= 0.1;
	}
	else if (key == KEY_P_PARALLEL)
	{
		set -> prg -> rotation = 1;
		set -> draw_data -> rotate[0] = 90;
		set -> draw_data -> rotate[1] = 0;
		set -> draw_data -> rotate[2] = 0;
	}
	else if (key == KEY_I_ISOMET)
	{
		set -> prg -> rotation = 1;
		ft_fdf_matrix_iterator(set, ft_fdf_set_x_y_after_pnt);
		ft_fdf_isomet_project(set);
	}
	else if (key == KEY_ESC)
	{
		
	}
	else
	{
		set -> prg -> print = 0;
		return (0);
	}
	return (1);
}

int	ft_fdf_loop_hook(t_ft_fdf_data_set *set)
{
	void	*tmp_img_ptr;
	// 초기화하고, 찍기 필요
	tmp_img_ptr = 0;
	if (set -> prg -> print == 1)
	{
		mlx_destroy_image(set -> mlx, set -> img -> img_ptr);
		tmp_img_ptr = mlx_new_image(set -> mlx, set -> prg -> window[0], set -> prg -> window[1]);
		set -> img = ft_mlx_init_img_data(tmp_img_ptr);
		set -> img -> addr = mlx_get_data_addr(set -> img -> img_ptr, &(set -> img -> bits_per_pixel),
				&(set -> img -> line_length), &(set -> img -> endian));
		ft_fdf_set_transformation(set);
		ft_fdf_matrix_iterator(set, ft_fdf_iter_draw_line);
		set -> prg -> print = 0;
		set -> prg -> rotation= 0;
		set -> prg -> zoom = 0;
		mlx_put_image_to_window(set -> mlx, set -> mlx_win, set -> img -> img_ptr, 0, 0);
	}
	return (1);
}
