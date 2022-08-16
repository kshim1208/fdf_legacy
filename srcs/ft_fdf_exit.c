/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:51:11 by kshim             #+#    #+#             */
/*   Updated: 2022/08/16 15:35:52 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/fdf.h"
#include <stdio.h>

void    ft_fdf_exit(char *func_name, int msg_index)
{
	char	*message[12];
	char	*err_msg;

	ft_px_set_error_message(message);
	err_msg = ft_strjoin(func_name, message[msg_index]);
	if (err_msg == NULL)
	{
		perror("ft_fdf_exit");
		exit(1);
	}
	perror(err_msg);
	free(err_msg);
	exit(1);
}

void	ft_px_set_error_message(char *message[])
{
	message[FAIL_INPUT] = " : fail to input file";
	message[FAIL_OPEN_FILE] = " : fail to open()";
	message[FAIL_MEMORY_ALLOC] = " : fail to allocate memory";
	message[FAIL_GNL] = " : fail to get_next_line";
	message[FAIL_INVAL_VALUE] = " : invalid value in input file";
	message[FAIL_INPUT_LEN] = " : invalid input line length)";
	message[FAIL_ATOI] = " : fail to atoi";
	message[FAIL_HEX_ATOI] = " : fail to hex atoi";
	
	/*
	message[FAIL_REDRCT] = " : fail to redirect";
	message[FAIL_EXECVE] = " : fail to execve()";
	message[FAIL_NO_FILE] = " : pipex : No such file or directory";
	message[FAIL_OPEN_FILE] = " : fail to open() file";
	message[FAIL_PARSE_ENVP] = " : fail to parse PATH for envp";
	*/
	return ;
}
