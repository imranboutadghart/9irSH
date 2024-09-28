/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:18:54 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_word(t_var *values);
void	copy_words(t_var *lst, char **words, size_t word, int flag);
size_t	get_word_len(t_var *values, size_t index);
int		copy_char(char *word, size_t *idx_word, int *mask, size_t idx);

char	**form_content(t_var *values)
{
	char	**words;
	size_t	count;

	words = NULL;
	count = count_word(values);
	if (count == 0)
		return (NULL);
	words = (char **)malloc((1 + count) * sizeof(char *));
	if (!words)
		return (return_error(malloc_fail));
	words[count] = NULL;
	copy_words(values, words, 0, 0);
	return (words);
}

void	copy_words(t_var *lst, char **words, size_t word, int flag)
{
	size_t	idx_word;
	size_t	idx;

	while (lst)
	{
		idx = 0;
		while (lst->mask && lst->mask[idx])
		{
			if (lst->mask[idx] == whitespace)
				flag = 0;
			else
			{
				if (flag == 0)
				{
					idx_word = 0;
					words[word] = (char *)ft_calloc(get_word_len(lst, idx), 1);
					if (!words[word++])
						return ;
				}
				flag = copy_char(words[word - 1], &idx_word, lst->mask, idx);
			}
			idx++;
		}
		lst = lst->next;
	}
}

size_t	count_word(t_var *values)
{
	size_t	count;
	size_t	index;
	int		flag;

	flag = 0;
	count = 0;
	while (values)
	{
		index = 0;
		while (values->mask && values->mask[index])
		{
			if (values->mask[index] == whitespace)
				flag = 0;
			else if (flag == 0)
			{
				count++;
				flag = 1;
			}
			index++;
		}
		values = values->next;
	}
	return (count);
}

size_t	get_word_len(t_var *values, size_t index)
{
	size_t	len;

	len = 0;
	while (values)
	{
		while (values->mask && values->mask[index])
		{
			if (values->mask[index] == whitespace)
				return ((len + 1) * sizeof(char));
			len++;
			index++;
		}
		index = 0;
		values = values->next;
	}
	return ((len + 1) * sizeof(char));
}

int	copy_char(char *word, size_t *idx_word, int *mask, size_t idx)
{
	int	flag;

	flag = 1;
	if (mask[idx] != 7001 && mask[idx] != 7000)
	{
		word[*idx_word] = (char)mask[idx];
		*idx_word += 1;
	}
	return (flag);
}
