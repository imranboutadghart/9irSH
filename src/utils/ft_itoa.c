/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:19:51 by l3zii             #+#    #+#             */
/*   Updated: 2024/09/29 00:46:32 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	digit_counter(long n);	

int	*ft_custom_itoa(int n)
{
	int		*str;
	int		sign;
	long	num;
	size_t	index;

	sign = 0;
	num = n;
	if (num < 0)
	{
		sign = 1;
		num *= -1;
	}
	index = digit_counter(num);
	str = (int *)malloc((sign + index + 1) * sizeof(int));
	if (!str)
		return (return_error(malloc_fail));
	if (sign)
		str[0] = '-';
	str[sign + index] = '\0';
	while (index)
	{
		str[sign - 1 + index--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

static int	digit_counter(long n)
{
	int	counter;

	counter = 1;
	while (n / 10 > 0)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	long	num;
	size_t	index;

	sign = 0;
	num = n;
	if (num < 0)
	{
		sign = 1;
		num *= -1;
	}
	index = digit_counter(num);
	str = (char *)malloc((sign + index +1) * sizeof(char));
	if (!str)
		return (return_error(malloc_fail));
	if (sign)
		str[0] = '-';
	str[sign + index] = '\0';
	while (index)
	{
		str[sign - 1 + index--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
