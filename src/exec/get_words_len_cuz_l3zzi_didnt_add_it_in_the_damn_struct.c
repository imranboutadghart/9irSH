/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words_len_cuz_l3zzi_w9_didnt_add_it_in_        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:09:51 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/16 03:17:42 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_words_len(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}
