/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:38:41 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 18:43:12 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"
#include <stdio.h>

void	recv_pos(t_server *srv)
{
	t_bulk	data;
	int		i;
	int		len;

	i = -1;
	while (++i < srv->id)
	{
		len = SDLNet_TCP_Recv(srv->client[i], &data, sizeof(t_bulk));
		//printf("Recv %d out of %d\n", len, sizeof(t_bulk));
		if (len != sizeof(t_bulk))
			ft_putendl("Waring RECV: Missing data");
		else
			srv->data.plr[i] = data;
		printf("Player %d\nPos: %f %f %f\nDir: %f %f %f\nMis: %d %d\n-----\n",
			i,
			srv->data.plr[i].pos.z, srv->data.plr[i].pos.y, srv->data.plr[i].pos.x,
			srv->data.plr[i].dir.z, srv->data.plr[i].dir.y, srv->data.plr[i].dir.x,
			srv->data.plr[i].hp, srv->data.plr[i].gfx);
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
			ft_putendl("Waring SEND: Missing data");
	}
}

int		main(int ac, char **av)
{
	t_server	srv;

	printf("Starting server...\n");
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
			send_chunck(&srv);
			recv_pos(&srv);
			SDL_Delay(70);
		}
		if (srv.id < 5)
		{
			srv.client[srv.id] = SDLNet_TCP_Accept(srv.server);
			if (!srv.client[srv.id])
			{
				SDL_Delay(100);
				continue;
			}
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
			srv.id++;
		}
	}
	SDLNet_Quit();
}