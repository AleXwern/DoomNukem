/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ax_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:26:52 by AleXwern          #+#    #+#             */
/*   Updated: 2020/11/04 14:06:26 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libax.h"

static int		arrlen(const char *host, int len)
{
	int			i;
	int			ret;

	i = 0;
	ret = 1;
	while (i < len)
	{
		if (host[i] == '.')
			ret++;
		i++;
	}
	return (ret);
}

static t_uint32	get_addr(const char *host, t_uint32 ip, int i)
{
	char		**arr;
	int			len;

	arr = ft_strsplit(host, '.');
	len = arrlen(host, ft_strlen(host));
	if (len == 4)
	{
		while (++i < 4)
		{
			ip = (ip << 8) | (ft_atoi(arr[3 - i]) & 0xff);
		}
	}
	i = -1;
	while (++i < len)
		free(arr[i]);
	free(arr);
	if (len != 4)
		return (INADDR_NONE);
	return (ip);
}

int				ax_resolvehost(t_ip *ip, const char *host, t_uint16 port)
{
	int			err;

	err = 0;
	if (host == NULL)
		ip->host = INADDR_ANY;
	else
	{
		ip->host = get_addr(host, 0, -1);
		if (ip->host == INADDR_NONE)
			err = -1;
	}
	ip->port = (port << 8) | (port >> 8);
	return (err);
}
