/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:23:22 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 02:06:06 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_root;

void	shlvl_bs(void);

int	main(void)
{
	char	*line;

	shlvl_bs();
	while (1)
	{
		reset_prompt();
		if (!isatty(STDIN_FILENO))
			line = readline("");
		else
			line = readline(GREEN"󱞪 "RESET);
		if (!line)
			break ;
		g_root.cmds = parser(line);
		handle_herdocs();
		if (g_root.error->code)
			g_root.error->handler(g_root.error->data, g_root.error->code);
		else
			execute(g_root.cmds);
		manage_history(line);
	}
	destructor();
	return (EXIT_SUCCESS);
}

void	shlvl_bs(void)
{
	char	*str;
	char	*out;
	int		shlvl;

	str = get_env("SHLVL");
	out = NULL;
	shlvl = 0;
	if (str)
		shlvl = ft_atoi(str);
	if (str && shlvl > 0 && shlvl < 1000)
	{
		shlvl = ft_atoi(str);
		(void)shlvl;
		out = ft_itoa(shlvl + 1);
		set_env("SHLVL", out);
	}
	else
	{
		if (shlvl > 999)
			error(NULL, NAME": warning: SHLVL too high, resetting to 1\n");
		out = ft_itoa(1);
		set_env("SHLVL", out);
	}
	free(out);
}
