/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imbo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:40:56 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:23:34 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	count_words(char *tmp, char del)
{
	int	size;

	size = 1;
	while (*tmp)
	{
		if (*tmp == del)
			size += 1;
		++tmp;
	}
	return (size);
}

char	**imbo_split(char *string, char del)
{
	char	**strs;
	char	*tmp;
	int		size;
	int		i;

	if (!string)
		return (NULL);
	size = count_words(string, del);
	strs = malloc((size + 1) * sizeof(char *));
	if (!strs)
		return (return_error(malloc_fail));
	i = 0;
	0[strs] = string;
	tmp = string - 1;
	while (*(++tmp))
	{
		if (*tmp == del)
			(++i)[strs] = tmp + 1;
		if (*tmp == del)
			*tmp = '\0';
	}
	strs[++i] = 0;
	return (strs);
}
/* MASTER IN ACTION.*/
