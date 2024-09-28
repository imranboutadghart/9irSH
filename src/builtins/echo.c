/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:41:34 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/23 00:34:33 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_params(int ac, char **av, int start)
{
	int	i;

	i = start;
	while (i < ac - 1)
	{
		write(1, av[i], ft_strlen(av[i]));
		write(1, " ", 1);
		i++;
	}
	if (i < ac)
		write(1, av[i], ft_strlen(av[i]));
}

static int	get_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(int ac, char **av)
{
	int	flag;
	int	i;

	if (ac == 1)
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	i = 0;
	flag = 0;
	while (++i < ac && av[i][0] == '-')
	{
		if (!av[i][1] || av[i][1] != 'n')
			break ;
		if (!flag)
			flag = get_flag(av[i]);
		if (!get_flag(av[i]))
			break ;
	}
	print_params(ac, av, i);
	if (0 == flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
