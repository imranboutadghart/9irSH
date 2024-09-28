/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_tmp_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:54:36 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_dev_random(void);
ssize_t	read_from_file(int fd, char *buffer, ssize_t len);

char	*get_random_tmp_filename(void)
{
	char	buffer[67];
	int		fd;
	ssize_t	read_len;
	ssize_t	index;

	index = 0;
	fd = open_dev_random();
	if (fd < 0)
		return (NULL);
	read_len = read_from_file(fd, buffer, 64);
	if (read_len < 0)
		return (NULL);
	while (index < read_len)
	{
		buffer[index] = ('a' + (unsigned char)buffer[index] % 26);
		index++;
	}
	close(fd);
	return (ft_strjoin("/tmp/minishell-herdoc-", buffer));
}

int	open_dev_random(void)
{
	int	fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		perror("OPEN() Error :");
		g_root.error->code = cant_open_file;
	}
	return (fd);
}

ssize_t	read_from_file(int fd, char *buffer, ssize_t len)
{
	ssize_t	read_len;

	read_len = read(fd, buffer, len);
	if (read_len < 0)
	{
		perror("READ() Error :");
		g_root.error->code = cant_read_from_file;
	}
	else
		buffer[read_len] = '\0';
	return (read_len);
}
