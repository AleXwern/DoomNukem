/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:14:39 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/29 11:44:49 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void	kill_extra(t_server *srv)
{
	//TCPsocket	ksock;
	//IPaddress	*kip;
	t_socket	*ksock;
	//t_ip		kip;

	/*if (!(ksock = SDLNet_TCP_Accept(srv->server)))
		return ;
	if (!(kip = SDLNet_TCP_GetPeerAddress(ksock)))
		return ;*/
	if (!(ksock = ax_accept(srv->server, srv->ax)))
		return;
	//if (!(kip = SDLNet_TCP_GetPeerAddress(ksock)))
	//	return;
	ft_putendl("Killed extra connection");
	//SDLNet_TCP_Close(ksock);
	ax_close(ksock);
}

void	check_args(t_server *srv, char *av)
{
	int		idle;

	idle = ft_atoi(av);
	if (idle > 0)
		srv->maxidle = idle;
}
