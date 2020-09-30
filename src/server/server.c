/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:38:41 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/30 11:46:53 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void	check_alive(t_server *srv, int i)
{
	int		d;

	while (++i < srv->id && i < MAXPLAYER)
	{
		if (!srv->alive[i])
		{
			ft_putendl("Player MIA -> Killing connection!");
			SDLNet_TCP_Close(srv->client[i]);
			d = i - 1;
			while (++d < 3)
			{
				srv->client[d] = srv->client[d + 1];
				srv->alive[d] = srv->alive[d + 1];
				srv->data.plr[d] = srv->data.plr[d + 1];
				srv->remoteip[d] = srv->remoteip[d + 1];
				srv->timeout[d] = srv->timeout[d + 1];
			}
			srv->alive[d] = 0;
			ft_bzero(&srv->data.plr[d], sizeof(t_bulk));
			srv->timeout[d] = 0;
			srv->id--;
			i--;
		}
	}
}

void	recv_data(t_server *srv)
{
	t_bulk	data;
	int		i;
	int		len;

	i = -1;
	while (++i < srv->id)
	{
		if (srv->timeout[i])
			continue;
		len = SDLNet_TCP_Recv(srv->client[i], &data, sizeof(t_bulk));
		if (len != sizeof(t_bulk))
			srv->timeout[i]++;
		else
		{
			srv->data.plr[i] = data;
			srv->timeout[i] = 0;
		}
		if (srv->timeout[i] > 690 / (srv->id + 1))
		{
			srv->timeout[i] = 0;
			srv->alive[i] = 0;
		}
	}
}

void	send_chunck(t_server *srv)
{
	int		i;
	int		len;

	i = -1;
	while (++i < srv->id)
	{
		srv->data.id = i;
		len = SDLNet_TCP_Send(srv->client[i], &srv->data, sizeof(t_chunk));
		if (len != sizeof(t_chunk))
			srv->timeout[i]++;
		else
			srv->timeout[i] = 0;
		if (srv->timeout[i] > 690 / (srv->id + 1))
		{
			srv->timeout[i] = 0;
			srv->alive[i] = 0;
		}
	}
}

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

int		main(int ac, char **av)
{
	t_server	srv;

	ft_bzero(&srv, sizeof(t_server));
	SDLNet_Init();
	if (SDLNet_ResolveHost(&srv.ip, NULL, 9999) == -1)
		exit(1);
	if (!(srv.server = SDLNet_TCP_Open(&srv.ip)))
		exit(2);
	while (!srv.stop)
	{
		if (srv.id > 0)
		{
			check_alive(&srv, -1);
			send_chunck(&srv);
			recv_data(&srv);
		}
		if (srv.id < MAXPLAYER)
		{
			if (!(srv.client[srv.id] = SDLNet_TCP_Accept(srv.server)))
				continue;
			if (!(srv.remoteip[srv.id] = SDLNet_TCP_GetPeerAddress(srv.client[srv.id])))
				continue;
			srv.alive[srv.id] = 1;
			srv.id++;
		}
		else
			kill_extra(&srv);
	}
	SDLNet_Quit();
}
