/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:57 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/29 00:27:40 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	internal_error(char *input, char *error)
{
	write(2, NAME": ", strlen(NAME": "));
	if (input)
	{
		write(2, input, strlen(input));
		write(2, ": ", 2);
	}
	if (error)
	{
		write(2, error, strlen(error));
	}
	return (FAIL);
}

int	error(char *input, char *error)
{
	if (input)
	{
		write(2, input, strlen(input));
		write(2, ": ", 2);
	}
	if (error)
		write(2, error, strlen(error));
	return (FAIL);
}
