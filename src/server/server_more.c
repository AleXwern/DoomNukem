/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:14:39 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/06 15:17:49 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void	kill_extra(t_server *srv)
{
	TCPsocket	ksock;
	IPaddress	*kip;

	if (!(ksock = SDLNet_TCP_Accept(srv->server)))
		return ;
	if (!(kip = SDLNet_TCP_GetPeerAddress(ksock)))
		return ;
	ft_putendl("Killed extra connection");
	SDLNet_TCP_Close(ksock);
}
