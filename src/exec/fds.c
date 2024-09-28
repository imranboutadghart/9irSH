/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:44 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/16 03:24:19 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	save_fds(int fds[2])
{
	fds[0] = dup(0);
	if (fds[0] == -1)
		return (internal_error(NULL, ERR_DUP));
	fds[1] = dup(1);
	if (fds[1] == -1)
		return (close(fds[0]), internal_error(NULL, ERR_DUP));
	return (EXIT_SUCCESS);
}

int	restore_fds(int fds[2])
{
	if (dup2(fds[0], 0) == -1 || dup2(fds[1], 1) == -1)
		return (internal_error(NULL, ERR_DUP));
	close(fds[0]);
	close(fds[1]);
	return (EXIT_SUCCESS);
}
