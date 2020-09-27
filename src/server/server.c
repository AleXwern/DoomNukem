/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:38:41 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/26 14:15:28 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"
#include <stdio.h>

void	check_alive(t_server* srv)
{
	int		i;
	int		d;

	i = -1;
	while (++i < srv->id && i < MAXPLAYER)
	{
		if (!srv->alive[i])
		{
			ft_putendl("Player MIA -> Killing connection!");
			ft_putstr("Connections left: ");
			ft_putnbrln(srv->id - 1);
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

void	recv_pos(t_server *srv)
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
		//printf("Recv %d out of %d\n", len, sizeof(t_bulk));
		if (len != sizeof(t_bulk))
		{
			ft_putendl("Warning RECV: Missing data");
			srv->timeout[i]++;
		}
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
		printf("Player %d\nPos: %f %f %f\nDir: %f %f %f\nMis: %d %d %d\n-----\n",
			i,
			srv->data.plr[i].pos.z, srv->data.plr[i].pos.y, srv->data.plr[i].pos.x,
			srv->data.plr[i].dir.z, srv->data.plr[i].dir.y, srv->data.plr[i].dir.x,
			srv->data.plr[i].hp, srv->data.plr[i].gfx, srv->timeout[i]);
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
		//printf("Sent %d out of %d\n", len, sizeof(t_chunk));
		if (len != sizeof(t_chunk))
		{
			ft_putendl("Warning SEND: Missing data");
			srv->timeout[i]++;
		}
		else
			srv->timeout[i] = 0;
		if (srv->timeout[i] > 690 / (srv->id + 1))
		{
			srv->timeout[i] = 0;
			srv->alive[i] = 0;
		}
	}
}

void	kill_extra(t_server* srv)
{
	TCPsocket	ksock;
	IPaddress	*kip;

	ksock = SDLNet_TCP_Accept(srv->server);
	if (!ksock)
	{
		ft_putendl("No sockets to kill");
		return;
	}
	kip = SDLNet_TCP_GetPeerAddress(srv->client);
	if (!kip)
	{
		ft_putendl("No IPs to kill");
		return;
	}
	SDLNet_TCP_Close(ksock);
	Uint32 ipaddr = SDL_SwapBE32(kip->host);
	printf("Killed connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
		(ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
		kip->port);
}

int		main(int ac, char **av)
{
	t_server	srv;

	ft_putendl("Starting server...");
	ft_bzero(&srv, sizeof(t_server));
	SDLNet_Init();
	if (SDLNet_ResolveHost(&srv.ip, NULL, 9999) == -1)
	{
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}
	srv.server = SDLNet_TCP_Open(&srv.ip);
	if (!srv.server)
	{
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
	while (!srv.stop)
	{
		if (srv.id > 0)
		{
			check_alive(&srv);
			send_chunck(&srv);
			recv_pos(&srv);
		}
		if (srv.id < MAXPLAYER)
		{
			srv.client[srv.id] = SDLNet_TCP_Accept(srv.server);
			if (!srv.client[srv.id])
				continue;
			srv.remoteip[srv.id] = SDLNet_TCP_GetPeerAddress(srv.client);
			if (!srv.remoteip[srv.id])
			{
				printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
				continue;
			}
			Uint32 ipaddr = SDL_SwapBE32(srv.remoteip[srv.id]->host);
			printf("Accepted a connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
				(ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
				srv.remoteip[srv.id]->port);
			srv.alive[srv.id] = 1;
			srv.id++;
		}
		else
			kill_extra(&srv);
	}
	SDLNet_Quit();
}