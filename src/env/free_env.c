/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:47:25 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/20 00:47:26 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	size_t	index;

	index = 0;
	while (index < g_root.env_count)
	{
		free(env[index]);
		index++;
	}
	free(env);
}
