/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:55 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	do_pipes(int input, int output);

int	handle_pipe(t_cmd *cmd, t_fds *fds, int *input)
{
	if (cmd->next)
	{
		if (pipe(fds->pipes))
			return (internal_error(NULL, ERR_PIPE));
	}
	else
		fds->pipes[1] = dup(fds->og_fds[1]);
	if (do_pipes(*input, fds->pipes[1]))
	{
		if (fds->pipes[0] > 0)
			close(fds->pipes[0]);
		if (fds->pipes[1] == 0 || fds->pipes[1] > 1)
			close(fds->pipes[1]);
		return (FAIL);
	}
	*input = fds->pipes[0];
	return (EXIT_SUCCESS);
}

static int	do_pipes(int input, int output)
{
	if (input != -1)
	{
		if (dup2(input, 0) < 0)
			return (internal_error(NULL, ERR_DUP));
		if (input > 0)
			close(input);
	}
	if (output != -1)
	{
		if (dup2(output, 1) < 0)
			return (internal_error(NULL, ERR_DUP));
		if (output > 1 || output == 0)
			close(output);
	}
	return (EXIT_SUCCESS);
}
