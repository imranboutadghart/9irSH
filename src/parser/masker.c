/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:12:35 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		mask_specials(int *bytes, int flag);
int		*copy_line_to_ints(char *line);
void	mask_line(int *bytes);

int	*masker(char *line)
{
	int	*bytes;

	bytes = copy_line_to_ints(line);
	if (g_root.error->code)
		return (bytes);
	mask_line(bytes);
	if (g_root.error->code)
		return (bytes);
	return (bytes);
}

void	mask_line(int *bytes)
{
	size_t	index;
	int		flag;

	index = 0;
	flag = 0;
	while (bytes[index])
	{
		if ((!flag || flag & 1) && bytes[index] == '\'')
		{
			bytes[index] = single_quote;
			flag ^= 1;
		}
		else if ((!flag || flag & 2) && bytes[index] == '"')
		{
			bytes[index] = double_quote;
			flag ^= 2;
		}
		else
			bytes[index] = mask_specials(bytes + index, flag);
		index++;
	}
	if ((flag & 1) && !bytes[index])
		g_root.error->code = single_quote_err;
	else if ((flag & 2) && !bytes[index])
		g_root.error->code = single_quote_err;
}

int	mask_specials(int *bytes, int flag)
{
	if ((!flag || flag & 2) && *bytes == '$')
	{
		if (ft_isalnum((char)*(bytes + 1)) || *(bytes + 1) == '_')
			return (variable);
		if (*(bytes + 1) == '?')
			return (exit_status);
		return ('$');
	}
	if (!flag && *bytes == '|')
		return (pipe_mask);
	if (!flag && *bytes == '<' && *(bytes + 1) == '<')
		return (herdoc);
	if (!flag && *bytes == '>' && *(bytes + 1) == '>')
		return (append);
	if (!flag && *bytes == '<')
		return (input);
	if (!flag && *bytes == '>')
		return (output);
	if (!flag && is_whitespace(*bytes))
		return (whitespace);
	return (*bytes);
}

int	*copy_line_to_ints(char *line)
{
	size_t	index;
	int		*bytes;

	index = 0;
	bytes = (int *)malloc(sizeof(int) * (ft_strlen(line) + 1));
	if (bytes)
	{
		while (line[index])
		{
			bytes[index] = (int)line[index];
			index++;
		}
		bytes[index] = 0;
		return (bytes);
	}
	g_root.error->code = malloc_fail;
	return (FAILURE);
}
