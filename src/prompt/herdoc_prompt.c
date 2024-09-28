/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:32:35 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_newline_terminated_line(char *line);
char	*expand_line(char *line);

char	*herdoc_prompt(char *match, int expandable, char **herdoc_buffer)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (g_root.error->code == 0)
	{
		line = readline("herdoc> ");
		if (!line || g_root.error->code != 0 || ft_strcmp(match, line) == 0)
			break ;
		if (expandable == HERDOC_EXPANDABLE)
			line = expand_line(line);
		else
			line = get_newline_terminated_line(line);
		if (!line || g_root.error->code != 0 || ft_strcmp(match, line) == 0)
			break ;
		tmp = *herdoc_buffer;
		*herdoc_buffer = ft_strjoin(*herdoc_buffer, line);
		free(tmp);
		free(line);
	}
	if (!line)
		printf("warning: herdoc delimited by EOF, (wanted `%s`)\n", match);
	if (g_root.error->code != 0)
		return (free(line), NULL);
	return (free(line), *herdoc_buffer);
}

char	*get_newline_terminated_line(char *line)
{
	char	*tmp;

	tmp = ft_strjoin(line, "\n\0");
	free(line);
	return (tmp);
}

/*

1. read until NULL or ft_strcmp(line, delimiter) is hit
2. if herdoc is expandable:
	2.1 count actual line length with expanded variables
	2.2 form the actual line and end it with \n\0
   else
	2.1 ft_strjoin(line, "\n")
3. join the line with the BUFFER

details:
2.1 count actual line length with expanded variables:
	2.1.1 if line[index] is $, then check next char if its alpha or underscore
		the length of the value and add it to the len
	2.1.2 if $ is not followed by alpha or underscore but is followed by ?
		get the length of the exit_status via ft_itoa
	2.1.3 if line[index] is neither len++
2.2 repeat the same process in 2.1 but instead of counting length, copy variable
	value into the line.


*/