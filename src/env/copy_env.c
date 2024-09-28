/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:19:58 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_env_len(char **env);
char	**realloc_env(char **old_env, int freeable);

char	**realloc_env(char **old_env, int freeable)
{
	char	**new_env;
	size_t	len;
	size_t	index;

	if (freeable && g_root.env_count == g_root.env_size)
		len = g_root.env_size * 2 + 2;
	else
		len = count_env_len(old_env) * 2 + 2;
	new_env = (char **)malloc(len * sizeof(char *));
	if (!new_env)
		return (return_error(malloc_fail));
	index = 0;
	while (old_env[index])
	{
		new_env[index] = ft_strdup(old_env[index]);
		if (!new_env[index])
			return (return_error(malloc_fail));
		index++;
	}
	new_env[index] = NULL;
	if (freeable)
		free_env(old_env);
	g_root.env_size = len - 1;
	g_root.env_count = index;
	return (new_env);
}

size_t	count_env_len(char **env)
{
	size_t	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}
