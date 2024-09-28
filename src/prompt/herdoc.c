/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:32:43 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	open_herdocs(void);
char	*get_random_tmp_filename(void);
char	*herdoc_prompt(char *delimiter, int expandable, char **herdoc_buffer);
void	fork_for_herdocs(void);
void	write_to_herdoc_file(void);

void	handle_herdocs(void)
{
	t_file	*file;
	t_cmd	*cmd;
	size_t	count;

	count = 0;
	if (g_root.error->code)
		return ;
	cmd = g_root.cmds;
	while (g_root.error->code == 0 && cmd)
	{
		file = cmd->files;
		while (file)
		{
			if (file->type == HERDOC)
			{
				count++;
				file->original = file->filename;
				file->filename = get_random_tmp_filename();
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
	if (count)
		fork_for_herdocs();
}

size_t	open_herdocs(void)
{
	t_cmd	*cmd;
	t_file	*file;

	cmd = g_root.cmds;
	while (g_root.error->code == 0 && cmd)
	{
		file = cmd->files;
		while (g_root.error->code == 0 && file)
		{
			if (file->type == HERDOC)
				herdoc_prompt(file->original, file->expandable, &file->buffer);
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	herdoc_wrapper(void)
{
	signal(SIGINT, sig_handler_herdoc);
	signal(SIGQUIT, SIG_IGN);
	open_herdocs();
	if (g_root.error->code == 0)
		write_to_herdoc_file();
	clean_exit();
}

void	fork_for_herdocs(void)
{
	pid_t	proc_pid;
	int		status;

	proc_pid = fork();
	if (proc_pid == 0)
	{
		herdoc_wrapper();
		exit(SUCCESS);
	}
	else if (proc_pid < 0)
		return_error(fork_failure);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(proc_pid, &status, 0);
		signal(SIGINT, sig_handler_parent);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 10)
				g_root.error->code = child_proc_interepted_sigint;
			if (WEXITSTATUS(status) == 10)
				g_root.exit_status = 130;
		}
	}
}

void	write_to_herdoc_file(void)
{
	t_cmd	*cmd;
	t_file	*file;
	int		fd;

	cmd = g_root.cmds;
	while (g_root.error->code == 0 && cmd)
	{
		file = cmd->files;
		while (g_root.error->code == 0 && file)
		{
			if (file->type == HERDOC)
			{
				fd = open(file->filename, O_CREAT | O_WRONLY | O_TRUNC, 777);
				if (file->buffer)
					write(fd, file->buffer, ft_strlen(file->buffer));
				free(file->buffer);
				file->buffer = NULL;
				close(fd);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
}
