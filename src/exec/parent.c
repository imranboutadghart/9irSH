/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:53 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:22:50 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_status(int status);

int	get_child_exit(int pid)
{
	int	status;
	int	ret;

	waitpid(pid, &status, 0);
	ret = get_status(status);
	return (ret);
}

int	get_children_exit(int pid)
{
	int	ret;
	int	status;

	ret = wait(&status);
	if (ret == pid)
		g_root.exit_status = get_status(status);
	if (ret <= 0)
		return (g_root.exit_status = EXIT_SUCCESS, EXIT_SUCCESS);
	while (ret > 0)
	{
		if (ret == pid)
			g_root.exit_status = get_status(status);
		ret = wait(&status);
	}
	return (EXIT_SUCCESS);
}

static int	get_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) + 128 == 131)
				write(2, "Quit (core dumped)\n", \
				ft_strlen("Quit (core dumped)\n"));
		return (WTERMSIG(status) + 128);
	}
	return (0);
}
