/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:28 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_existence(char *filename, int print)
{
	if (!filename || access(filename, F_OK) != 0)
	{
		if (print)
			internal_error(filename, ERR_EXIST);
		return (FAIL);
	}
	return (EXIT_SUCCESS);
}

int	get_read_access(char *filename)
{
	if (!filename || access(filename, R_OK) != 0)
	{
		internal_error(filename, ERR_PERM);
		return (FAIL);
	}
	return (EXIT_SUCCESS);
}

int	get_write_access(char *filename)
{
	if (!filename || access(filename, W_OK) != 0)
	{
		internal_error(filename, ERR_PERM);
		return (FAIL);
	}
	return (EXIT_SUCCESS);
}

int	get_exec_access(char *filename)
{
	if (!filename || access(filename, X_OK) != 0)
	{
		internal_error(filename, ERR_PERM);
		return (FAIL);
	}
	return (EXIT_SUCCESS);
}

int	is_dir(char *dir)
{
	struct stat	info;

	if (stat(dir, &info) == -1)
		return (error(NULL, "could not read file stats\n"), 1);
	return ((!!S_ISDIR(info.st_mode)) * -1);
}
