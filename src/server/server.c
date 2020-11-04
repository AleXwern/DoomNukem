/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:38:41 by anystrom          #+#    #+#             */
/*   Updated: 2020/11/04 14:33:32 by anystrom         ###   ########.fr       */
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
			ft_putstr("Player MIA -> Killing connection from: ");
			ax_printipln(srv->client[i]->remote);
			ax_close(srv->client[i]);
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
		len = ax_recv(srv->client[i], &data, sizeof(t_bulk));
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
		len = ax_send(srv->client[i], &srv->data, sizeof(t_chunk));
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

void	init_server(t_server *srv, int ac, char **av)
{
	ft_bzero(srv, sizeof(t_server));
	if (!(srv->ax = ax_init()))
		exit(0);
	if (ax_resolvehost(&srv->ip, NULL, 9999) == -1)
		exit(1);
	if (!(srv->server = ax_open(&srv->ip, srv->ax)))
		exit(2);
	srv->maxidle = 690;
	if (ac >= 2)
		check_args(srv, av[1]);
}

int		main(int ac, char **av)
{
	t_server	srv;

	init_server(&srv, ac, av);
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
			if (!(srv.client[srv.id] = ax_accept(srv.server, srv.ax)))
				continue;
			ft_putstr("Accepted connection from: ");
			ax_printipln(srv.client[srv.id]->remote);
			srv.alive[srv.id] = 1;
			srv.id++;
		}
		else
			kill_extra(&srv);
	}
	return (0);
}
