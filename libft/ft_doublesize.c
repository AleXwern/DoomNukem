/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublesize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 22:00:44 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/06 22:00:44 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_doublesize(double num)
{
	size_t	len;
	int i = 0;

	while (++i < 12)
	{
		printf("%f %d\n", num, (int)num);
		num -= (int)num;
		if (num - (int)num != 0)
			num *= 10;
		else
			break;
			
	}
	len = ft_intsize((int)num) + 1;
	return (len);
}