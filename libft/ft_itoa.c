/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:43:13 by anystrom          #+#    #+#             */
/*   Updated: 2019/11/02 14:42:25 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_itoabuilder(char *num, long n, int i)
{
	int		min;

	min = 0;
	if (n < 0)
	{
		num[0] = '-';
		min++;
		n = -1 * n;
	}
	while (i >= min)
	{
		num[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*num;

	if (!(num = (char*)malloc(sizeof(char) * (ft_intsize(n) + 1))))
		return (NULL);
	if (n == INT_MIN - 1)
	{
		ft_strcpy(num, "-2147483648");
		return (num);
	}
	ft_itoabuilder(num, (long)n, ft_intsize(n));
	num[ft_intsize(n) + 1] = '\0';
	return (&num[0]);
}
