/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:40 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/27 21:08:27 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	child_process(char *path, char **words, t_fds fds);

int	execute_regular(char **words, int is_piped, t_fds fds, int *pid)
{
	char	*path;
	int		ret;

	if (is_path_complete(words[0]))
		path = ft_strdup(words[0]);
	else
		path = get_cmd_path(words[0]);
	*pid = fork();
	if (*pid == -1)
		return (free(path), internal_error(NULL, ERR_FORK));
	if (!*pid)
	{
		ret = child_process(path, words, fds);
		free(path);
		clean_exit();
		exit(ret);
	}
	free(path);
	if (!is_piped)
		return (get_child_exit(*pid));
	return (EXIT_SUCCESS);
}

static int	child_process(char *path, char **words, t_fds fds)
{
	close(fds.og_fds[0]);
	close(fds.og_fds[1]);
	if (fds.pipes[0] >= 0)
		close(fds.pipes[0]);
	if (get_existence(path, 0))
		return (internal_error(words[0], ERR_NOT_FND), 127);
	if (is_dir(path))
		return (internal_error(words[0], ERR_ISDIR), 126);
	if (get_exec_access(path))
		return (126);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, words, g_root.env);
	return (EXIT_SUCCESS);
}
