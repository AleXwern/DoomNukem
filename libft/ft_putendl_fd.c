/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 11:33:47 by anystrom          #+#    #+#             */
/*   Updated: 2019/11/02 12:06:59 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(const char *s, int fd)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (s[i] != '\0')
	{
		c = (unsigned char)s[i];
		write(fd, &c, 1);
		i++;
	}
	write(fd, "\n", 1);
}
