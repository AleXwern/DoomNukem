/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 19:42:54 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/24 19:42:54 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_replace(char* str, char s, char r, size_t max)
{
	size_t	i;

	i = 0;
	while (i < max)
	{
		if (str[i] == s)
			str[i] = r;
		i++;
	}
	return (str);
}