/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:20:00 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*allocate(size_t size, void (*fn)(void *ptr, void *data), void *data)
{
	size_t	index;
	void	*ptr;
	char	*s;

	index = 0;
	ptr = malloc(size);
	if (ptr == NULL)
		return (return_error(malloc_fail));
	s = (char *)ptr;
	while (index < size)
	{
		s[index] = 0;
		index++;
	}
	if (fn)
		fn(ptr, data);
	return (ptr);
}
