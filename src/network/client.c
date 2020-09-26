/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:59:39 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 15:38:31 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		connect_server(t_doom *dm)
{
	dm->person = 10;
	printf("Starting client...\n");
	if (SDLNet_ResolveHost(&dm->ip, IP, 9999) == -1)
	{
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return (0);
	}
	dm->sock = SDLNet_TCP_Open(&dm->ip);
	if (!dm->sock)
	{
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		return (0);
	}
	return (1);
}

void	send_pos(t_doom *dm)
{
	t_bulk	data;
	int		sent;

	data = (t_bulk){.dir = dm->dir, .pos = dm->pos, .hp = dm->hp, .gfx = dm->person};
	sent = SDLNet_TCP_Send(dm->sock, &data, sizeof(t_bulk));
	printf("Sent %d out of %d\n", sent, sizeof(t_bulk));
	if (sent < sizeof(t_bulk))
		printf("Missing bytes SEND: %s\n", SDLNet_GetError());
}

void	recv_pos(t_doom *dm)
{
	t_chunk	data;
	int		recv;
	int		i;

	recv = SDLNet_TCP_Recv(dm->sock, &data, sizeof(t_chunk));
	printf("Recv %d out of %d\n", recv, sizeof(t_chunk));
	i = -1;
	if (recv <= 0)
	{
		dm->srv = SDLNet_TCP_Accept(dm->sock);
		if (!dm->srv)
			ft_putendl("Accept error");
	}
	while (++i < 5)
	{
		if (i != data.id)
		{
			dm->spr[i].pos = data.plr[i].pos;
			dm->spr[i].face = data.plr[i].dir;
			dm->spr[i].gfx = data.plr[i].gfx;
			dm->spr[i].hp = data.plr[i].hp;
			dm->prj[i].pos = data.plr[i].prj;
		}
	}
}

void	network_test(t_doom *dm) // THIS IS FOR TESTING PURPOSES
{
	int		done = 0;
	char	*argv;

	if (1)
		argv = "server";
	else
		argv = "client";
	if (strcmp(argv, "server") == 0)
	{
		printf("Starting server...\n");
		TCPsocket server, client;
		IPaddress ip;
		if (SDLNet_ResolveHost(&ip, NULL, 9999) == -1)
		{
			printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
			exit(1);
		}
		server = SDLNet_TCP_Open(&ip);
		if (!server)
		{
			printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
			exit(2);
		}
		while (!done)
		{
			/* try to accept a connection */
			client = SDLNet_TCP_Accept(server);
			if (!client)
			{ /* no connection accepted */
				/*printf("SDLNet_TCP_Accept: %s\n",SDLNet_GetError()); */
				SDL_Delay(100); /*sleep 1/10th of a second */
				continue;
			}

			/* get the clients IP and port number */
			IPaddress *remoteip;
			remoteip = SDLNet_TCP_GetPeerAddress(client);
			if (!remoteip)
			{
				printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
				continue;
			}

			/* print out the clients IP and port number */
			Uint32 ipaddr;
			ipaddr = SDL_SwapBE32(remoteip->host);
			printf("Accepted a connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
					(ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
					remoteip->port);

			while (1)
			{
				/* read the buffer from client */
				char message[1024];
				int len = SDLNet_TCP_Recv(client, message, 1024);
				if (!len)
				{
					printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
					break;
				}
				/* print out the message */
				printf("Received: %.*s\n", len, message);
				if (message[0] == 'q')
				{
					printf("Disconecting on a q\n");
					break;
				}
				if (message[0] == 'Q')
				{
					printf("Closing server on a Q.\n");
					done = 1;
					break;
				}
			}
			SDLNet_TCP_Close(client);
		}
	}
	else if (strcmp(argv, "client") == 0)
	{
		printf("Starting client...\n");
		IPaddress ip;
		TCPsocket tcpsock;

		if (SDLNet_ResolveHost(&ip, IP, 9999) == -1)
		{
			printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
			exit(1);
		}

		tcpsock = SDLNet_TCP_Open(&ip);
		if (!tcpsock)
		{
			printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
			exit(2);
		}

		while (1)
		{
			printf("message: ");
			char message[1024];
			fgets(message, 1024, 0);
			int len = strlen(message);

			/* strip the newline */
			message[len - 1] = '\0';

			if (len)
			{
				int result;

				/* print out the message */
				printf("Sending: %.*s\n", len, message);

				result =
					SDLNet_TCP_Send(tcpsock, message, len); /* add 1 for the NULL */
				if (result < len)
				printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
			}

			if (len == 2 && tolower(message[0]) == 'q') {
				break;
			}
		}

		SDLNet_TCP_Close(tcpsock);
	} else
	{
		printf("Choose server or client\n");
	}
	SDLNet_Quit();
	SDL_Quit();
}