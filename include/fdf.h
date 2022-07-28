/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:18:23 by kshim             #+#    #+#             */
/*   Updated: 2022/07/28 17:29:18 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

typedef struct s_data {
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef enum e_fdf_errors {
	FAIL_INPUT = 0,
	FAIL_OPEN_FILE,
	FAIL_MEMORY_ALLOC,
	FAIL_GNL,
	FAIL_INVAL_VALUE,
	FAIL_INPUT_LEN,
	FAIL_ATOI
}			t_ft_fdf_errors;

typedef struct s_point_data{
	double	x;
	double	y;
	double	z;
}			t_ft_fdf_pnt_data;

int		get_next_line(int fd, char **ret_str);

t_ft_fdf_pnt_data	**ft_fdf_parse_file(char *filename);
void	ft_fdf_parse_gl_to_lst(char *gl, t_list *val_list, int *len);
void	ft_fdf_set_gl_to_lst(char *start, t_list *val_list);
t_ft_fdf_pnt_data	*ft_fdf_set_val_to_s_lst(t_list *val_list, int len);
t_ft_fdf_pnt_data	**ft_fdf_set_s_lst_to_ptr_lst(t_list *ptr_arr, int size);

int	ft_atoi_fdf(const char *str, int *num);
void	ft_fdf_del_value_ptr(void *content);

void    ft_fdf_exit(char *func_name, int msg_index);
void	ft_px_set_error_message(char *message[]);

#endif