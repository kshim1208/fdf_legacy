/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:35:30 by kshim             #+#    #+#             */
/*   Updated: 2022/09/16 16:49:41 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdlib.h>

int	ft_atoi_fdf(char *str, char **end, int *num)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	sign = 1 - ((*str == '-') << 1);
	str += (*str == '+' || *str == '-');
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + (*str - '0');
		if ((ret * sign) > 2147483647 || (ret * sign) < -2147483648)
			return (0);
		str++;
	}
	if (*str == '\0' || *str == ' ' || *str == '\n' || *str == ',')
	{
		*num = (int)(ret * sign);
		*end = str;
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_hex_atoi_fdf(char *str, char **end, int *num)
{
	int	ret;

	ret = 0;
	str++;
	if (*str == '0')
		str++;
	else
		return (0);
	if (*str == 'x')
		str++;
	else
		return (0);
	if (ft_hex_c_to_val(&str, &ret) == 0)
		return (0);
	if (*str == '\0' || *str == ' ' || *str == '\n')
	{
		*num = ret;
		*end = str;
		return (1);
	}
	else
		return (0);
}

int	ft_hex_c_to_val(char **str, int *ret)
{
	int	len;

	len = 0;
	while (len < 6)
	{
		if (**str >= '0' && **str <= '9')
			*ret = *ret * 16 + (**str - '0');
		else if (**str >= 'A' && **str <= 'F')
			*ret = *ret * 16 + ((**str - 'A') + 10);
		else if (**str >= 'a' && **str <= 'f')
			*ret = *ret * 16 + ((**str - 'a') + 10);
		else
			return (0);
		len++;
		(*str)++;
	}
	return (1);
}

void	ft_fdf_del_value_ptr(void *content)
{
	int	*value;

	value = (int *)content;
	free(value);
	return ;
}

void	ft_fdf_free_str_arr_ptr_arr(t_ft_fdf_prg_data *prg_data,
	t_ft_fdf_pnt_data **pnt_data)
{
	int	i;

	i = 0;
	while (i < prg_data -> row)
	{
		free(pnt_data[i]);
		pnt_data[i] = 0;
		i++;
	}
	free(pnt_data);
	pnt_data = 0;
	return ;
}

// img ????????? ?????? ????????? ???????????? (loop_hook?????? ??????)

void	ft_fdf_matrix_iterator(t_ft_fdf_data_set *set,
	void (*iter)(int, int, t_ft_fdf_data_set *))
{
	int	i;
	int	j;

	i = 0;
	while (i < set -> prg -> row)
	{
		j = 0;
		while (j < set -> prg -> column)
		{
			iter(i, j, set);
			j++;
		}
		i++;
	}
	return ;
}

void	ft_fdf_hex_diviner(int color_pnt, int pnt[])
{
	int		i;

	i = 6;
	while (i != 0)
	{
		pnt[i - 1] = color_pnt % 16;
		color_pnt = color_pnt / 16;
		i--;
	}
	return ;
}

void	ft_fdf_cpy_matrix(double **trans, double **tmp)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tmp[i][j] = trans[i][j];
			j++;
		}
		i++;
	}
	return ;
}

// tmp * z = trans
void	ft_fdf_multiply_matrix(double **trans, double **axis, double **tmp)
{
	int i;
	int j;
	int k;

	k = 0;
	while (k < 4)
	{
		j = 0
		while (j < 4)
		{
			i = 0
			while (i < 4)
			{
				trans[k][j] += tmp[k][i] * axis[i][j];
				i++;
			}
			j++;
		}
		k++;
	}
	return ;
}