/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:19:36 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files(t_file *files);
void	reset_errors(void);

void	reset_prompt(void)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	size_t	index;

	signal(SIGINT, sig_handler_parent);
	signal(SIGQUIT, SIG_IGN);
	reset_errors();
	if (!g_root.cmds)
		return ;
	cmd = g_root.cmds;
	while (cmd)
	{
		index = 0;
		while (cmd->words && cmd->words[index])
		{
			free(cmd->words[index]);
			index++;
		}
		free(cmd->words);
		tmp = cmd->next;
		free_files(cmd->files);
		free(cmd);
		cmd = tmp;
	}
	g_root.cmds = NULL;
}

void	free_files(t_file *files)
{
	t_file	*tmp;

	while (files)
	{
		tmp = files->next;
		free(files->filename);
		free(files->original);
		free(files->buffer);
		free(files);
		files = tmp;
	}
}

void	reset_errors(void)
{
	g_root.error->code = 0;
	g_root.error->data = NULL;
	g_root.error->handler = parser_handler;
}
