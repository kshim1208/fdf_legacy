/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_mlx_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:27:47 by kshim             #+#    #+#             */
/*   Updated: 2022/08/30 08:09:36 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "stdlib.h"
#include "../include/fdf.h"

// set 부분은 util로 빼고, mlx 파트만 함수로 분리해서 여기 남기자
void	ft_fdf_init_mlx_set_data(t_ft_fdf_data_set *set,
			t_ft_fdf_prg_data *prg, t_ft_fdf_pnt_data **pnt)
{
	void				*mlx;
	void				*mlx_win;
	void				*img_ptr;
	t_mlx_img_data		*img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, prg -> window[0], prg -> window[1], "fdf");
	img_ptr = mlx_new_image(mlx, prg -> window[0], prg -> window[1]);
	img = ft_mlx_init_img_data(img_ptr);
	img -> addr = mlx_get_data_addr(img -> img_ptr, &(img -> bits_per_pixel),
			&(img -> line_length), &(img -> endian));
	set -> prg = prg;
	set -> pnt = pnt;
	set -> mlx = mlx;
	set -> mlx_win = mlx_win;
	set -> img = img;
	return ;
}

// set 쓰는게 나을까? line_length가 화면 크기 참조한다고 해서;
t_mlx_img_data	*ft_mlx_init_img_data(void	*img_ptr)
{
	t_mlx_img_data	*img;

	img = (t_mlx_img_data *)malloc(sizeof(t_mlx_img_data));
	if (img == 0)
		return (0);
	img -> img_ptr = img_ptr;
	img -> addr = 0;
	img -> bits_per_pixel = 8 * 4;
	img -> line_length = 4;
	img -> endian = 0;
	return (img);
}

// 윈도우 밑에 공간 조금 남기면 텍스트 출력시키기 좋을 것 같은데
// 실제 윈도우 크기랑 image 윈도우 크기 나눠볼까?
void	ft_fdf_mlx_loop(t_ft_fdf_data_set *set)
{
	mlx_put_image_to_window(set -> mlx, set -> mlx_win,
		set -> img -> img_ptr, 0, 0);
	mlx_key_hook(set -> mlx_win, ft_fdf_key_event, set);
	mlx_loop_hook(set -> mlx, ft_fdf_loop_hook, set);
	mlx_loop(set -> mlx);
	return ;
}
