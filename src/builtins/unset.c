/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:41:20 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__unset_env(const char *name);

int	unset_env(int ac, char **av)
{
	int	index;

	index = 1;
	while (index < ac)
	{
		if (av[index][0] && ft_strchr(av[index], '=') == NULL)
			__unset_env((const char *)av[index]);
		index++;
	}
	g_root.exit_status = 0;
	return (SUCCESS);
}

int	__unset_env(const char *name)
{
	size_t	idx;
	size_t	len;
	char	**ep;

	idx = 0;
	ep = g_root.env;
	len = ft_strlen(name);
	while (ep && ep[idx] && g_root.env_count)
	{
		if (ep[idx][0] == name[0] && 0 == ft_strncmp(name, ep[idx], len))
		{
			if (ep[idx][len] == '=' || ep[idx][len] == '\0')
			{
				free(ep[idx]);
				ep[idx] = ep[g_root.env_count - 1];
				ep[g_root.env_count - 1] = NULL;
				g_root.env_count -= 1;
				return (SUCCESS);
			}
		}
		idx++;
	}
	return (FAIL);
}
