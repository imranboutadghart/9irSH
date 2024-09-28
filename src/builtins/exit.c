/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:41:26 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/21 19:24:56 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_atoi_err(const char *str, int *err_flag)
{
	size_t	i;
	size_t	result;
	int		sign;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_strchr(BLANK, str[i]))
		i++;
	if ('+' == str[i] || '-' == str[i])
		if ('-' == str[i++])
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i++] - '0';
		if (result > (size_t)9223372036854775807 + (sign == -1))
		{
			*err_flag = 1;
			break ;
		}
	}
	if (str[i] && !ft_isdigit(str[i]))
		*err_flag = 1;
	return ((int )(sign * result));
}

int	ft_exit(int ac, char **av)
{
	int				err_flag;
	unsigned char	ret;

	err_flag = 0;
	write(1, "exit\n", 5);
	if (ac <= 1)
	{
		clean_exit();
		exit(g_root.exit_status);
	}
	ret = (unsigned char)ft_atoi_err(av[1], &err_flag);
	if (err_flag)
	{
		error(NULL, NAME": exit: numeric argument required\n");
		clean_exit();
		exit(2);
	}
	if (ac > 2)
	{
		error(NULL, NAME": exit: Too many arguments\n");
		return (1);
	}
	clean_exit();
	exit(ret);
	return (0);
}
