/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:41:36 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	cd_is_dir(char *dir)
{
	struct stat	info;

	if (stat(dir, &info) == -1)
		return (error("cd", "could not read from dir"), 1);
	return ((!!S_ISDIR(info.st_mode)) * -1);
}

int	cd_error(char *dir, char *error)
{
	write(2, NAME": cd: ", ft_strlen(NAME": cd: "));
	if (dir)
	{
		write(2, dir, ft_strlen(dir));
		write(2, ": ", 2);
	}
	write(2, error, ft_strlen(error));
	return (FAIL);
}

int	change_directory(char *dest)
{
	char	owd[MAX_PATH_NAME];

	if (!dest)
		return (FAIL);
	getcwd(owd, MAX_PATH_NAME);
	if (access(dest, F_OK) == -1)
		return (cd_error(dest, "No such file or directory\n"), FAIL);
	if (!cd_is_dir(dest))
		return (cd_error(dest, "Not a directory\n"), FAIL);
	else if (cd_is_dir(dest) != -1)
		return (FAIL);
	if (access(dest, X_OK) == -1)
		return (cd_error(dest, "Permission denied\n"), FAIL);
	if (chdir(dest) == -1)
		return (cd_error(dest, "Could not change dir\n"), FAIL);
	getcwd(owd, MAX_PATH_NAME);
	set_env("PWD", owd);
	return (EXIT_SUCCESS);
}

int	cd(int ac, char **av)
{
	char	*home;

	if (ac > 2)
		return (cd_error(NULL, "too many arguments\n"), FAIL);
	if (ac == 1)
	{
		home = get_env("HOME");
		if (!home)
			return (cd_error(NULL, "HOME is not defined\n"));
		return (change_directory(home));
	}
	return (change_directory(av[1]));
}
