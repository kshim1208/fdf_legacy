/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:35:30 by kshim             #+#    #+#             */
/*   Updated: 2022/07/28 17:08:11 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi_fdf(const char *str, int *num)
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
	if (*str == '\0' && ((*str - 1) != '+' || (*str - 1) != '-'))
		*num = (int)(ret * sign);
	else
		return (0);
	return (1);
}

void	ft_fdf_del_value_ptr(void *content)
{
	int	*value;

	value = (int *)content;
	*value = 0;
	free(value);
	value = 0;
	return ;
}