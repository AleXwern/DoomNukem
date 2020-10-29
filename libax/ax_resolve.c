/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ax_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:26:52 by AleXwern          #+#    #+#             */
/*   Updated: 2020/10/23 21:26:52 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libax.h"

int			arrlen(char *host, int len)
{
	int		i;
	int		ret;

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

t_uint32	get_addr(const char *host, t_uint32 ip, int i)
{
	char	**arr;
	int		len;

	arr = ft_strsplit(host, '.');
	len = arrlen(host, ft_strlen(host));
	if (len == 4)
	{
		while (++i < 4)
		{
			ip = (ip << 8) | ft_atoi(arr[i]);
		}
	}
	i = -1;
	while (++i < len)
		free(arr[i]);
	free(arr);
	return (ip);
}

int			ax_resolvehost(t_ip *ip, const char *host, t_uint16 port)
{
	int		err;

	err = 0;
	if (host == NULL)
		ip->host = INADDR_ANY;
	else
	{
		//ip->host = get_addr(host, 0, -1);
		if (inet_pton(AF_INET, host, &ip->host) != 1)
			err = -1;
	}
	ip->port = (port << 8) | (port >> 8);
	//ip->port = port;
	printf("RESOLVE: %08x %d\nGiven IP %s %d\n", ip->host, ip->port, host, port);
	return (err);
}