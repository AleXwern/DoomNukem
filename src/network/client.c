/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:59:39 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/28 14:36:14 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		connect_server(t_doom *dm)
{
	if (dm->netstat)
		return (1);
	dm->person = 10;
	ft_putendl("Starting client...");
	if (SDLNet_ResolveHost(&dm->ip, IP, 9999) == -1)
		return (0);
	if (!(dm->sock = SDLNet_TCP_Open(&dm->ip)))
		return (0);
	ft_putendl("Client started successfully!");
	return (1);
}

int		send_pos(t_doom *dm)
{
	t_bulk	data;
	int		sent;

	data = (t_bulk){.dir = dm->dir, .pos = dm->pos, .hp = dm->hp,
					.gfx = dm->person};
	sent = SDLNet_TCP_Send(dm->sock, &data, sizeof(t_bulk));
	if (sent < sizeof(t_bulk))
	{
		ft_putendl(CON_ERROR);
		dm->netstat = 0;
		SDLNet_TCP_Close(dm->sock);
		return (0);
	}
	return (1);
}

void	recv_pos(t_doom *dm)
{
	t_chunk	data;
	int		recv;
	int		i;

	recv = SDLNet_TCP_Recv(dm->sock, &data, sizeof(t_chunk));
	i = -1;
	if (data.id > 3 || data.id < 0)
		return ;
	dm->id = data.id;
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
