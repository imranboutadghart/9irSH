/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:19:47 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	size_t	size;
	size_t	index;
	char	*dst;

	index = 0;
	size = ft_strlen(str);
	dst = malloc ((size + 1) * sizeof(char));
	if (!dst)
		return (return_error(malloc_fail));
	while (str[index])
	{
		dst[index] = str[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}
