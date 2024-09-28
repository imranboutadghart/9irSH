/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:08:44 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_key_validity(char *key);

int	set_env(char *key, char *value)
{
	char	*key_value;

	if ((*key != '_' && ft_isalpha(*key) == 0) || check_key_validity(key))
	{
		g_root.exit_status = 2;
		return (FAIL);
	}
	if (!value)
		return (SUCCESS);
	__unset_env(key);
	key_value = get_key_value(key, value);
	if (!key_value)
		return (FAIL);
	if (g_root.env_count == g_root.env_size)
		g_root.env = realloc_env(g_root.env, 1);
	if (!g_root.env)
		return (FAIL);
	g_root.env[g_root.env_count] = key_value;
	g_root.env[g_root.env_count + 1] = NULL;
	g_root.env_count += 1;
	return (SUCCESS);
}

int	set_empty_env(char *key)
{
	if (!key)
		return (FAIL);
	if ((*key != '_' && ft_isalpha(*key) == 0) || check_key_validity(key))
	{
		g_root.exit_status = 2;
		return (FAIL);
	}
	if (get_env(key) != NULL)
	{
		free(key);
		return (SUCCESS);
	}
	__unset_env(key);
	if (g_root.env_count == g_root.env_size)
		g_root.env = realloc_env(g_root.env, 1);
	if (!g_root.env)
		return (FAIL);
	g_root.env[g_root.env_count] = key;
	g_root.env[g_root.env_count + 1] = NULL;
	g_root.env_count += 1;
	return (SUCCESS);
}

int	check_key_validity(char *key)
{
	size_t	index;

	index = 0;
	while (key[index])
	{
		if (key[index] != '_' && ft_isalnum(key[index]) == 0)
			break ;
		index++;
	}
	return (key[index]);
}
