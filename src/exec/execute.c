/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:42 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/28 20:45:37 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	exec_cmd(char **cmd, int is_piped, t_fds fds, int *pid);
static int	very_ugly_norm_function(t_fds *fds, int	*i, int *p, t_cmd *cmd);
static void	files_failed(t_cmd **cmd, int *pid);

int	execute(t_cmd *cmd)
{
	t_fds	fds;
	int		is_piped;
	int		input;
	int		pid;

	if (very_ugly_norm_function(&fds, &input, &is_piped, cmd))
		return (FAIL);
	while (cmd)
	{
		if (is_piped && handle_pipe(cmd, &fds, &input) == FAIL)
			return (FAIL);
		if (cmd->files && handle_files(cmd->files) == FAIL)
		{
			files_failed(&cmd, &pid);
			continue ;
		}
		if (cmd->words && exec_cmd(cmd->words, is_piped, fds, &pid) == FAIL)
			return (FAIL);
		cmd = cmd->next;
	}
	restore_fds(fds.og_fds);
	if (is_piped)
		get_children_exit(pid);
	return (EXIT_SUCCESS);
}

static int	exec_cmd(char **words, int is_piped, t_fds fds, int *pid)
{
	*pid = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (is_builtin(words[0]))
		g_root.exit_status = execute_builtin(words, is_piped, fds, pid);
	else
		g_root.exit_status = execute_regular(words, is_piped, fds, pid);
	return (EXIT_SUCCESS);
}

static int	very_ugly_norm_function(t_fds *fds, int	*i, int *p, t_cmd *cmd)
{
	*fds = (t_fds){{-1, -1}, {-1, -1}};
	*i = STDIN_FILENO;
	*p = !!(cmd && cmd->next);
	g_root.exit_status = 0;
	if (save_fds(fds->og_fds))
		return (FAIL);
	return (SUCCESS);
}

static void	files_failed(t_cmd **cmd, int *pid)
{
	g_root.exit_status = 1;
	*cmd = (*cmd)->next;
	*pid = 0;
}
