/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:41:30 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	pwd(int ac, char **av)
{
	char	buff[MAX_PATH_NAME];

	(void)av;
	(void)ac;
	if (!getcwd(buff, MAX_PATH_NAME))
	{
		error(NULL, NAME": pwd: Could not get cwd\n");
		return (FAIL);
	}
	write(1, buff, strlen(buff));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
