/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:20:02 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	constructor(void)
{
	rl_change_environment = 0;
	g_root.env_count = 0;
	g_root.env_size = 0;
	g_root.exit_status = 0;
	g_root.error = (t_error *)malloc(sizeof(t_error));
	if (!g_root.error)
	{
		write(2, "FATAL MALLOC FAIL! Exiting...\n", 30);
		return (exit(FAIL));
	}
	g_root.env = realloc_env(__environ, 0);
	if (isatty(STDIN_FILENO))
	{
		write(1, "  ,-~~-.___.\n", 14);
		write(1, " / |  '     /\\         Damn boy this minishell", 47);
		write(1, " aint fun....\n", 15);
		write(1, "(  )         0              \n", 29);
		write(1, " \\_/-, ,----'            \n", 26);
		write(1, "    ====           //                     \n", 43);
		write(1, "   /  \\-'~;    /~~~(O)\n", 23);
		write(1, "  /  __/~|   /       |     \n", 28);
		write(1, "=(  _____| (_________|   W<\n", 28);
		write(1, "\n\n", 3);
	}
}

void	clean_exit(void)
{
	reset_prompt();
	free_env(g_root.env);
	rl_clear_history();
	free(g_root.error);
}

void	destructor(void)
{
	clean_exit();
	if (isatty(STDIN_FILENO))
	{
		write(1, "     _____              .---...-.\n", 34);
		write(1, "   ,'  -. `.          ,' _____...'\n", 35);
		write(1, "  /   - _ - \\        : .' _   _ \\\\\n", 35);
		write(1, " :    ' _)'  :       | :-(_).(_)::\n", 35);
		write(1, "(_           ;)      | |    -'  ||\n", 35);
		write(1, "  \\     _   /        ; |    _   ||\n", 35);
		write(1, "   `..___..'         `-'..____.'`'\n", 35);
		write(1, "      ;._:               _; :_\n", 31);
		write(1, "     /    \\ SSt        ,'  `' `. SSt\n", 37);
	}
}
