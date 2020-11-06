/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:59:39 by anystrom          #+#    #+#             */
/*   Updated: 2020/11/05 12:23:38 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		connect_server(t_doom *dm)
{
	if (dm->netstat)
		return (1);
	ft_putendl("Starting client...");
	if (ax_resolvehost(&dm->ip, IP, 9999) == -1)
		return (0);
	if (!(dm->sock = ax_open(&dm->ip, dm->ax)))
		return (0);
	ft_putendl("Client started successfully!");
	return (1);
}

int		send_pos(t_doom *dm)
{
	t_bulk		data;
	int			sent;
	static int	buffer;

	data = (t_bulk){.dir = dm->dir, .pos = dm->pos,
		.dead = dm->prj[dm->id].dead, .gfx = dm->person + 16,
		.prj = dm->prj[dm->id].pos};
	sent = ax_send(dm->sock, &data, sizeof(t_bulk));
	if (sent < (int)sizeof(t_bulk))
		buffer++;
	else
		buffer = 0;
	if (buffer > TIMEOUT)
	{
		ft_putendl(CON_ERROR);
		dm->netstat = 0;
		ft_bzero(dm->spr, 4 * sizeof(t_sprite));
		buffer = 0;
		ax_close(dm->sock);
		return (0);
	}
	return (1);
}

void	recv_pos(t_doom *dm)
{
	t_chunk	data;
	int		recv;
	int		i;

	recv = ax_recv(dm->sock, &data, sizeof(t_chunk));
	i = -1;
	if (data.id > 3 || data.id < 0 || recv != (int)sizeof(t_chunk))
		return ;
	dm->id = data.id;
	while (++i < 4)
	{
		if (i != data.id)
		{
			dm->spr[i].pos = data.plr[i].pos;
			dm->spr[i].face = data.plr[i].dir;
			dm->spr[i].gfx = data.plr[i].gfx;
			dm->prj[i].dead = data.plr[i].dead;
			dm->prj[i].pos = data.plr[i].prj;
			dm->spr[i].size = 17;
		}
	}
}
