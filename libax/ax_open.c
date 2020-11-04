/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ax_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:57:00 by AleXwern          #+#    #+#             */
/*   Updated: 2020/11/04 14:28:41 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libax.h"

void					*ax_close(t_socket *sock)
{
	if (sock)
	{
		if (sock->channel != INVALID_SOCKET)
			closesocket(sock->channel);
		free(sock);
		sock = NULL;
	}
	return (NULL);
}

t_socket				*ax_open(t_ip *ip, t_libax *ax)
{
	t_socket			*sock;
	struct sockaddr_in	addr;

	if (!(sock = (t_socket*)ft_memalloc(sizeof(t_socket))))
		return (NULL);
	ft_bzero(&addr, sizeof(addr));
	sock->channel = socket(AF_INET, SOCK_STREAM, 0);
	if (sock->channel == INVALID_SOCKET)
		return (ax_close(sock));
	if ((ip->host != INADDR_ANY) && (ip->host != INADDR_NONE)) //remote
	{
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = ip->host;
		addr.sin_port = ip->port;
		if (connect(sock->channel, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
			return (ax_close(sock));
	}
	else //local
	{
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = ip->port;
#ifndef WIN32
        setsockopt(sock->channel, SOL_SOCKET, SO_REUSEADDR, (char*)&ax->dm, sizeof(int));
#endif
		if (bind(sock->channel, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
			return (ax_close(sock));
		if (listen(sock->channel, 5) == SOCKET_ERROR)
			return (ax_close(sock));
#ifdef WIN32
		ax->mode = 1;
		ioctlsocket(sock->channel, FIONBIO, &ax->mode);
#elif O_NONBLOCK
		fcntl(sock->channel, F_SETFL, O_NONBLOCK);
#endif
		sock->server = 1;
	}
	if (TCP_NODELAY)
		setsockopt(sock->channel, IPPROTO_TCP, TCP_NODELAY, &ax->dm, sizeof(int));
	else
		return (ax_close(sock));
	sock->remote.host = addr.sin_addr.s_addr;
	sock->remote.port = addr.sin_port;
	return (sock);
}

t_socket				*ax_accept(t_socket *srv, t_libax *ax)
{
	t_socket			*sock;
	struct sockaddr_in	addr;
	socklen_t			socklen;

	if (!srv->server)
		return (NULL);
	if (!(sock = (t_socket*)ft_memalloc(sizeof(t_socket))))
		return (NULL);
	socklen = sizeof(addr);
	sock->channel = accept(srv->channel, (struct sockaddr*)&addr, &socklen);
	if (sock->channel == INVALID_SOCKET)
		return (ax_close(sock));
#ifdef WIN32
	ax->mode = 0;
	ioctlsocket(sock->channel, FIONBIO, &ax->mode);
#elif O_NONBLOCK
	ax->flag = fcntl(sock->channel, F_GETFL, 0);
	fcntl(sock->channel, F_SETFL, ax->flag & ~O_NONBLOCK);
#endif
	ax->accepted++;
	sock->remote.host = addr.sin_addr.s_addr;
    sock->remote.port = addr.sin_port;
	return (sock);
}
