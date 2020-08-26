/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:16:16 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/24 18:16:16 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char* ft_strfjoin(char* s1, char* s2)
{
	char* array;
	int		i;
	int		a;

	a = 0;
	if (!(array = (char*)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		array[a] = (char)s1[i];
		a++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		array[a] = (char)s2[i];
		a++;
		i++;
	}
	array[a] = '\0';
	free(s2);
	return (array);
}
