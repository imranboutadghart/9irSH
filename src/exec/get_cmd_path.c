/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:49 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/26 20:29:29 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_path(char *prefix, char *suffix);

char	*get_cmd_path(char *cmd)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	char	*tmp;
	size_t	i;

	if (ft_strcmp(cmd, "") == 0)
		return (NULL);
	path_var = get_env("PATH");
	if (!path_var)
		return (get_path("", cmd));
	tmp = ft_strdup(path_var);
	paths = imbo_split(tmp, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = get_path(paths[i], cmd);
		if (full_path)
			return (free(paths[0]), free(paths), full_path);
	}
	return (free(paths[0]), free(paths), NULL);
}

int	is_path_complete(char *path)
{
	if (!path)
		return (0);
	if (ft_strchr(path, '/'))
		return (1);
	return (0);
}

static char	*get_path(char *prefix, char *suffix)
{
	char	*tmp;
	char	*full_path;

	if (!prefix[0])
		tmp = ft_strdup("./");
	else
		tmp = ft_strjoin(prefix, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, suffix);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
