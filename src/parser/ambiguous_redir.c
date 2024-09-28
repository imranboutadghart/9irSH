/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:13:34 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	original_filename(t_token *tok);
void	free_words(t_token *tok);

size_t	check_ambiguous_redirs(t_token *tok)
{
	int	flag;

	flag = 0;
	while (g_root.error->code == 0 && tok)
	{
		if (flag && (!tok->content || tok->content[1]))
		{
			free_words(tok);
			original_filename(tok);
			if (g_root.error->code != 0)
				return (FAILURE);
		}
		else if (flag == 0 && tok->type == WORD)
		{
			if (tok->content == NULL)
				tok->type = SKIP;
		}
		flag = (tok->type == HERDOC || tok->type == INPUT);
		flag |= (tok->type == APPEND || tok->type == OUTPUT);
		tok = tok->next;
	}
	return (SUCCESS);
}
/*
This function does three(3) things:
	1. it frees the words when there is a redirection
	   and the expantion is splitted to multiple words
	2. it stores the original string the user typed in case
	   of ambiguous redirection. why? to print it in the error.
	3. it checks if the type is word and is of no value (0 words)
	   then it marks it as a SKIP
*/

size_t	original_filename(t_token *tok)
{
	char	*filename;
	size_t	index;

	index = 0;
	filename = (char *)malloc(tok->len + 1);
	if (!filename)
		return ((size_t)return_error(malloc_fail));
	while (index < tok->len)
	{
		filename[index] = (char)tok->start[index];
		if (tok->start[index] == variable)
			filename[index] = '$';
		else if (tok->start[index] == exit_status)
			filename[index] = '$';
		else if (tok->start[index] == double_quote)
			filename[index] = '"';
		else if (tok->start[index] == single_quote)
			filename[index] = '\'';
		index++;
	}
	filename[index] = '\0';
	tok->original = filename;
	return (SUCCESS);
}

void	free_words(t_token *tok)
{
	size_t	index;

	index = 0;
	while (tok->content && tok->content[index])
	{
		free(tok->content[index]);
		index++;
	}
	free(tok->content);
	tok->content = NULL;
}
