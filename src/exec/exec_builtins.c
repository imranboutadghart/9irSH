/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:33 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char *command)
{
	return (!(ft_strcmp(command, "echo") && ft_strcmp(command, "cd") && \
		ft_strcmp(command, "env") && ft_strcmp(command, "unset") && \
		ft_strcmp(command, "pwd") && ft_strcmp(command, "exit") && \
		ft_strcmp(command, "export")));
}

static int	(*get_builtin(char **words))(int argc, char **argv)
{
	(void)words;
	if (!ft_strcmp(words[0], "echo"))
		return (echo);
	if (!ft_strcmp(words[0], "cd"))
		return (cd);
	if (!ft_strcmp(words[0], "env"))
		return (env);
	if (!ft_strcmp(words[0], "unset"))
		return (unset_env);
	if (!ft_strcmp(words[0], "pwd"))
		return (pwd);
	if (!ft_strcmp(words[0], "exit"))
		return (ft_exit);
	if (!ft_strcmp(words[0], "export"))
		return (export);
	return (NULL);
}

static void	close_if_exit(int (*f_ptr)(int, char **), t_fds fds, int len)
{
	if (f_ptr != ft_exit || len > 1)
		return ;
	close(fds.og_fds[0]);
	close(fds.og_fds[1]);
}

int	execute_builtin(char **words, int is_piped, t_fds fds, int *pid)
{
	int	(*f_ptr)(int, char **);
	int	ret;

	f_ptr = get_builtin(words);
	if (!f_ptr)
		return (FAIL);
	if (!is_piped)
	{
		close_if_exit(f_ptr, fds, get_words_len(words));
		return (f_ptr(get_words_len(words), words));
	}
	*pid = fork();
	if (!*pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fds.og_fds[0]);
		close(fds.og_fds[1]);
		if (fds.pipes[0] >= 0)
			close(fds.pipes[0]);
		ret = f_ptr(get_words_len(words), words);
		clean_exit();
		exit(ret);
	}
	return (EXIT_SUCCESS);
}
