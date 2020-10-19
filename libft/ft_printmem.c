/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:00:08 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/19 16:04:14 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gethex(unsigned int num)
{
	char	c;

	c = '0';
	if (num > 15)
	{
		ft_puthex(num / 16);
		num = num % 16;
	}
	while (num > 0)
	{
		num--;
		c++;
		if (c == ':')
			c = 'a';
	}
	write(1, &c, 1);
}

void		ft_printmem(void *mem, size_t len)
{
	char	*str;
	int		i;

	str = (char*)malloc(sizeof(char) * len * 2);

}
