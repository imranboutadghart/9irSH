/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:19:56 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	size_t	max;
	void	*allocated;

	max = 4294967295;
	total_size = size * nmemb;
	if (nmemb * size == 0)
		return (malloc(0));
	if (total_size > max || nmemb > max || size > max)
		return (0);
	allocated = (void *)malloc(total_size);
	if (!allocated)
		return (return_error(malloc_fail));
	ft_bzero(allocated, total_size);
	return (allocated);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	index;

	index = 0;
	str = (char *)s;
	while (index < n)
	{
		str[index] = 0;
		index++;
	}
}
