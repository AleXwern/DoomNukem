/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ax_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:46:30 by AleXwern          #+#    #+#             */
/*   Updated: 2020/10/24 13:46:30 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libax.h"

int			ax_send(t_socket *sock, const void *data, int len)
{
	t_uint8	*letter;
	int		sent;
	int		left;

	if (sock->flag)
		return (-1);
	letter = (t_uint8*)data;
	left = len;
	sent = 0;
	while (left > 0 && len > 0)
	{
		len = send(sock->channel, letter, left, 0);
		if (len > 0)
		{
			sent += len;
			left -= len;
			letter += len;
		}
	}
	ft_putnbrln(sent);
	return (sent);
}

int			ax_recv(t_socket *sock, void *data, int max, size_t maxattempt)
{
	int		len;
	size_t	attempt;

	if (sock->flag)
		return (-1);
	attempt = 0;
	WSASetLastError(EINTR);
	len = 0;
	if (maxattempt > 0)
	{
		while (WSAGetLastError() == EINTR && attempt++ < maxattempt)
			len = recv(sock->channel, (char*)data, max, 0);
	}
	else
	{
		while (WSAGetLastError() == EINTR)
		{
			len = recv(sock->channel, (char*)data, max, 0);
		}
		//ft_putnbrln(len);
	}
	sock->ready = 0;
	return (len);
}