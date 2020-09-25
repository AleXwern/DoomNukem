/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:38:41 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 16:16:36 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void	recv_pos(t_server *srv)
{
	t_net
	if (!len)
	{
		printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		break;
	}
	/* print out the message */
	if (message[0] == 'q')
	{
		printf("Disconecting on a q\n");
		break;
	}
	if (message[0] == 'Q')
	{
		printf("Closing server on a Q.\n");
		srv.stop = 1;
		break;
	}
}

void	send_chunck(t_server *srv)
{
	
}

int		main(void)
{
	t_server	srv;

	printf("Starting server...\n");
	ft_bzero(&srv, sizeof(t_server));
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
		if (srv.id < 5)
		{
			srv.client[srv->id] = SDLNet_TCP_Accept(srv.server);
			if (!srv.client[srv->id])
			{
				SDL_Delay(100);
				continue;
			}
			srv.remoteip[srv->id] = SDLNet_TCP_GetPeerAddress(srv.client);
			if (!srv.remoteip[srv->id])
			{
				printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
				continue;
			}
			SDLNet_TCP_Send(srv.client[srv->id], &srv.id, sizeof(int));
			srv.id++;
		}
		Uint32 ipaddr = SDL_SwapBE32(remoteip->host);
		printf("Accepted a connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
				(ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
				remoteip->port);

		//send receive
	}
}