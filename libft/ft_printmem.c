/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:00:08 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/24 14:27:26 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		gethex(t_uint8 num)
{
	char		c;

	c = '0';
	num = num & 0xf;
	while (num > 0)
	{
		num--;
		c++;
		if (c == ':')
			c = 'a';
	}
	return (c);
}

char			*make_str(char *str, t_uint8 *cpy, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		t;

	i = 0;
	j = 0;
	while (i < len)
	{
		t = 0;
		while (t < 16)
		{
			str[i + t] = gethex(cpy[j] >> 4);
			str[i + t + 1] = gethex(cpy[j]);
			j++;
			t += 2;
			if (t % 16 == 0)
				str[i + t] = '\n';
			if ((t + 8) % 16 == 0)
				str[i + t] = ' ';
			if (t % 16 == 0 || (t + 8) % 16 == 0)
				i++;
		}
		i += 16;
	}
	return (str);
}

void			ft_printmem(void *mem, size_t len)
{
	char		*str;
	t_uint8		*cpy;
	size_t		lbk;

	lbk = len / 8;
	str = (char*)ft_memalloc(sizeof(char) * len * 2 + lbk * 2 + 1);
	cpy = (t_uint8*)mem;
	str = make_str(str, cpy, len + lbk);
	str[len * 2 + lbk * 2] = '\0';
	ft_putstr("Printing out ");
	ft_putnbr(len);
	ft_putendl(" bytes of memory.");
	write(1, str, len * 2 + lbk * 2);
	free(str);
}
