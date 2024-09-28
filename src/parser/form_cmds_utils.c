/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:58:48 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*add_file(t_file **list, int type);

void	move_word(t_token *tok, char **words, int flag)
{
	size_t	index;
	size_t	word_index;

	word_index = 0;
	while (tok && tok->type != PIPE)
	{
		flag = (tok->type == INPUT || tok->type == HERDOC);
		flag |= (tok->type == OUTPUT || tok->type == APPEND);
		if (flag)
			tok = tok->next;
		else
		{
			index = 0;
			while (flag == 0 && tok->content && tok->content[index])
			{
				words[word_index] = tok->content[index];
				word_index += 1;
				index += 1;
			}
			words[word_index] = NULL;
		}
		tok = tok->next;
		flag = 0;
	}
}

char	**add_words(t_token *toks, size_t *count, size_t *word_count)
{
	char	**words;

	if (*count == 0)
		return (NULL);
	words = (char **)malloc((*count + 1) * sizeof(char *));
	if (!words)
		return (return_error(malloc_fail));
	move_word(toks, words, 0);
	*word_count = *count;
	*count = 0;
	return (words);
}

t_cmd	*add_cmd(t_cmd **list)
{
	t_cmd	*loop;
	t_cmd	*new;

	new = (t_cmd *)malloc(1 * sizeof(t_cmd));
	if (!new)
		return (return_error(malloc_fail));
	new->word_count = 0;
	new->words = NULL;
	new->files = NULL;
	new->next = NULL;
	loop = *list;
	if (loop == NULL)
		*list = new;
	else
	{
		while (loop->next)
			loop = loop->next;
		loop->next = new;
	}
	return (new);
}

t_file	*create_file(t_cmd *cmd, t_token *tok, int type)
{
	t_file	*file;

	file = add_file(&cmd->files, type);
	if (!file)
		return (return_error(malloc_fail));
	file->original = tok->original;
	file->expandable = tok->xpand;
	file->buffer = NULL;
	if (tok->content)
		file->filename = tok->content[0];
	return (file);
}

t_file	*add_file(t_file **list, int type)
{
	t_file	*loop;
	t_file	*new;

	new = (t_file *)malloc(1 * sizeof(t_file));
	if (!new)
		return (return_error(malloc_fail));
	new->type = type;
	new->next = NULL;
	new->original = NULL;
	new->filename = NULL;
	new->expandable = 0;
	new->fd = 0;
	loop = *list;
	if (loop == NULL)
		*list = new;
	else
	{
		while (loop->next)
			loop = loop->next;
		loop->next = new;
	}
	return (new);
}
