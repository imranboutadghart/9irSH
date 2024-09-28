/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:02:52 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	env(int ac, char **av)
{
	size_t	index;

	(void)av;
	index = 0;
	if (ac != 1)
		return (error("env", "no options allowed\n"), 127);
	while (g_root.env && g_root.env[index])
	{
		if (ft_strchr(g_root.env[index], '='))
			printf("%s\n", g_root.env[index]);
		index++;
	}
	return (SUCCESS);
}
