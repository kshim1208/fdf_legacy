/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:39:54 by kshim             #+#    #+#             */
/*   Updated: 2022/07/28 15:52:56 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>

/*
typedef struct	s_data {
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

t_data	*my_mlx_init_img_data(void	*img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
*/

int	main(int argc, char **argv)
{
	/* 구조체 배열의 포인터 만드는 법 생각하기 */
	t_ft_fdf_pnt_data	**data_arr_ptr_arr;

	if (argc < 2)
		ft_fdf_exit("main", FAIL_INPUT);
	data_arr_ptr_arr = ft_fdf_parse_file(argv[1]);
	// parsing 함수
	/*
	출력 파트 작업
	void	*mlx;
	void	*mlx_win;
	void	*img_ptr;
	t_data	*img_data;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "HELLO WORLD");
	img_ptr = mlx_new_image(mlx, 1920, 1080);
	img_data = my_mlx_init_img_data(img_ptr);
	img_data -> addr = mlx_get_data_addr(img_data -> img_ptr, &(img_data -> bits_per_pixel), &(img_data -> line_length),
								&(img_data -> endian));
	my_mlx_pixel_put(img_data, 50, 50, 0x00FFFFFF);
	mlx_put_image_to_window(mlx, mlx_win, img_data -> img_ptr, 0, 0);
	mlx_loop(mlx);
	*/
	return (0);
}


/*
t_data	*my_mlx_init_img_data(void	*img_ptr)
{
	t_data	*img_data;

	img_data = (t_data *)malloc(sizeof(t_data));
	if (img_data == 0)
		return (0);
	img_data -> img_ptr = img_ptr;
	img_data -> addr = 0;
	img_data -> bits_per_pixel = 0;
	img_data -> line_length = 0;
	img_data -> endian = 0;
	return (img_data);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data -> addr + (y * data -> line_length + x * (data -> bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

*/