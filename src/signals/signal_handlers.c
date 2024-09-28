/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:49:52 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_herdoc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_root.exit_status = 130;
		g_root.error->code = child_proc_interepted_sigint;
		reset_prompt();
		free_env(g_root.env);
		rl_clear_history();
		free(g_root.error);
		exit(10);
	}
}

void	sig_handler_parent(int signal)
{
	if (signal == SIGINT)
	{
		g_root.exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
