/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:18:23 by kshim             #+#    #+#             */
/*   Updated: 2022/08/24 13:34:38 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# include <stdio.h>

# define KEY_A_Y_R		97
# define KEY_D_Y		100
# define KEY_E_ZOOMOUT	101
# define KEY_F_Z_R		102
# define KEY_I_ISOMET	105
# define KEY_P_PARALLEL 112
# define KEY_Q_ZOOMIN	113
# define KEY_R_Z		114
# define KEY_S_X_R		115
# define KEY_W_X		119
# define KEY_ESC 		65307

typedef struct s_mlx_data {
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx_img_data;

typedef enum e_fdf_errors {
	FAIL_INPUT = 0,
	FAIL_OPEN_FILE,
	FAIL_MEMORY_ALLOC,
	FAIL_GNL,
	FAIL_INVAL_VALUE,
	FAIL_INPUT_LEN,
	FAIL_ATOI,
	FAIL_HEX_ATOI
}			t_ft_fdf_errors;

typedef struct s_fdf_value_lst
{
	int	val;
	int	color;
}			t_value_list;

typedef struct s_fdf_point_data{
	double	x;
	double	y;
	double	z;
	int		color;
}			t_ft_fdf_pnt_data;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_fdf_draw_line
{
	double	length;
	double	height;
	int		x_dir;
	int		y_dir;
	double	mid;
	int		i;
	int		codomain;
	int		color;
	double	clr_change[3];
	double	clr_accum[3];
	int		hex_power[6];
}				t_ft_fdf_draw_line;

typedef struct s_fdf_parse_data{
	t_ft_fdf_pnt_data	*struct_arr;
	t_list				*tmp_lst;
	t_list				*tmp_ptr_lst;
	char				*gotten_line;
	int					gnl_ret;
	int					prev_len;
}			t_ft_fdf_parse_data;

// prg_data 변수 중 잠깐 쓰는 변수는 나중에 해제할 수 있도록 다른 구조체로 묶어서 set에 넣기
typedef struct s_fdf_prg_data{
	int					row;
	int					column;
	double				window[2];
	int					min_max_z[2];
	double				zoom;
	int					rotate;
	int					print;
	double				axis_pnt[3];
	double				degree[3];
	// double					view_pnt[3]; - 도형 이동 가정시
}			t_ft_fdf_prg_data;

typedef struct s_fdf_output_data
{
	double				wht_sp[2];
	int					org_pnt[2];
	double				pnt_len;
}			t_ft_fdf_output_data;

	// img_ptr 분리할까? loop_hook에서 좀 지저분한데
typedef struct s_fdf_iter_data_set
{
	t_ft_fdf_prg_data		*prg;
	t_ft_fdf_pnt_data		**pnt;
	t_ft_fdf_output_data	*output;
	t_mlx_img_data			*img;
	void					*mlx;
	void					*mlx_win;
}			t_ft_fdf_data_set;

int					get_next_line(int fd, char **ret_str);

t_ft_fdf_pnt_data	**ft_fdf_parse_file(char *filename,
						t_ft_fdf_prg_data *prg_data);
int					ft_fdf_gnl(t_ft_fdf_prg_data *prg_data,
						t_ft_fdf_parse_data *parse, int file_fd);
void				ft_fdf_parse_gl_to_lst(char *gl,
						t_list **val_list, t_ft_fdf_prg_data *prg_data);
void				ft_fdf_set_gl_to_lst(char *str_start,
						char **str_end, t_list **val_list, int min_max_z[]);
t_ft_fdf_pnt_data	*ft_fdf_set_val_to_s_lst(t_list *val_list, int len);
t_ft_fdf_pnt_data	**ft_fdf_set_s_lst_to_ptr_lst(t_list *ptr_arr, int size);

void				ft_fdf_mlx(t_ft_fdf_prg_data *prg_data,
						t_ft_fdf_pnt_data **pnt_data, int argc, char **argv);
t_mlx_img_data		*ft_mlx_init_img_data(void	*img_ptr);
void				ft_fdf_init_output_data(t_ft_fdf_data_set *set);
void				ft_fdf_set_pnt_data(t_ft_fdf_data_set *set,
						int argc, char **argv);
void				ft_fdf_set_pnt_len(t_ft_fdf_data_set *set);
void				ft_fdf_check_pnt_len(t_ft_fdf_data_set *set);
void				ft_fdf_set_x_y_len(int i, int j, t_ft_fdf_data_set *set);

void				ft_fdf_isomet_project(t_ft_fdf_data_set *set);
void				ft_fdf_rotate_axis_all(t_ft_fdf_pnt_data *draw,
						t_ft_fdf_data_set *set);
void				ft_fdf_rotate_axis_x(t_ft_fdf_pnt_data *draw,
						t_ft_fdf_data_set *set);
void				ft_fdf_rotate_axis_y(t_ft_fdf_pnt_data *draw,
						t_ft_fdf_data_set *set);
void				ft_fdf_rotate_axis_z(t_ft_fdf_pnt_data *draw,
						t_ft_fdf_data_set *set);

void				ft_fdf_iter_draw_line(int i, int j,
						t_ft_fdf_data_set *set);
void				ft_fdf_after_zoom(t_ft_fdf_pnt_data *after_zoom,
						t_ft_fdf_pnt_data *bef_zoom, t_ft_fdf_prg_data *prg);
void				ft_fdf_draw_line(t_ft_fdf_pnt_data *pnt1,
						t_ft_fdf_pnt_data *pnt2, t_ft_fdf_data_set *set);
void				ft_fdf_line_pixel_color(t_ft_fdf_draw_line *line_data);
int					ft_fdf_calc_color_change(double *clr_accum, int hex_power);
void				ft_mlx_pixel_put(t_mlx_img_data *data,
						int x, int y, int color);

int					ft_fdf_key_event(int key, t_ft_fdf_data_set *set);
int					ft_fdf_loop_hook(t_ft_fdf_data_set *set);

int					ft_atoi_fdf(char *str, char **end, int *num);
int					ft_hex_atoi_fdf(char *str, char **end, int *num);
int					ft_hex_c_to_val(char **str, int *ret);
void				ft_fdf_del_value_ptr(void *content);
void				ft_fdf_free_str_arr_ptr_arr(t_ft_fdf_prg_data *prg_data,
						t_ft_fdf_pnt_data **pnt_data);
void				ft_fdf_matrix_iterator(t_ft_fdf_data_set *set,
						void (*iter)(int, int, t_ft_fdf_data_set *));
void				ft_fdf_hex_diviner(int color_pnt, int pnt[]);

void				ft_fdf_init_draw_line(t_ft_fdf_draw_line *line_data,
						t_ft_fdf_pnt_data *pnt1, t_ft_fdf_pnt_data *pnt2);
void				ft_fdf_set_clr_change(t_ft_fdf_draw_line *line_data,
						int color_pnt1, int color_pnt2);

void				ft_fdf_exit(char *func_name, int msg_index);
void				ft_px_set_error_message(char *message[]);

void				ft_fdf_init_mlx_set_data(t_ft_fdf_data_set *set,
						t_ft_fdf_prg_data *prg, t_ft_fdf_pnt_data **pnt);
t_mlx_img_data		*ft_mlx_init_img_data(void	*img_ptr);
void				ft_fdf_mlx_loop(t_ft_fdf_data_set *set);

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));

//test 함수
void	ft_fdf_print(int i, int j, t_ft_fdf_data_set *set);

#endif
