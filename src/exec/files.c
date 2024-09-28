/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:47 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_input(t_file *src);
static int	handle_output(t_file *src);
static int	do_direct(int fd, int dest);
static int	specific_is_dir(char *str);

int	handle_files(t_file *src)
{
	if (!src)
		return (EXIT_SUCCESS);
	while (src)
	{
		if (!src->filename)
		{
			internal_error(src->original, ERR_AMBIG);
			return (FAIL);
		}
		if (src->type == INPUT || src->type == HERDOC)
			if (handle_input(src) == FAIL)
				return (FAIL);
		if (src->type == OUTPUT || src->type == APPEND)
			if (handle_output(src) == FAIL)
				return (FAIL);
		src = src->next;
	}
	return (EXIT_SUCCESS);
}

static int	handle_input(t_file *src)
{
	int	fd;

	if (get_existence(src->filename, 1) || get_read_access(src->filename))
		return (FAIL);
	fd = open(src->filename, O_RDONLY);
	if (src->type == HERDOC)
		unlink(src->filename);
	if (fd == -1)
		return (internal_error(src->filename, ERR_OPEN));
	if (do_direct(fd, STDIN_FILENO))
		return (FAIL);
	return (EXIT_SUCCESS);
}

static int	handle_output(t_file *src)
{
	int	fd;

	fd = -1;
	if (!get_existence(src->filename, 0) && \
		(specific_is_dir(src->filename) || get_write_access(src->filename)))
		return (FAIL);
	if (src->type == APPEND)
		fd = open(src->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(src->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (internal_error(src->filename, ERR_OPEN));
	if (do_direct(fd, STDOUT_FILENO))
		return (FAIL);
	return (EXIT_SUCCESS);
}

static int	do_direct(int fd, int dest)
{
	if (dup2(fd, dest) == -1)
	{
		if (fd != dest)
			close(fd);
		return (internal_error(NULL, ERR_DUP));
	}
	if (fd != dest)
		close(fd);
	return (EXIT_SUCCESS);
}

static int	specific_is_dir(char *str)
{
	if (is_dir(str))
	{
		internal_error(str, ERR_ISDIR);
		return (FAIL);
	}
	return (EXIT_SUCCESS);
}
