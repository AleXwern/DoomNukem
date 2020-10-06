/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_in_game_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:50:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/06 15:57:00 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	These functions handle keys pressed in the in-game menu.
*/

void	menu_keys_hold_more(int key, t_doom *dm)
{
	if (dm->cur == 8)
	{
		if (dm->tile < 1)
			dm->tile = 1;
		destroy_gfx(dm, -1);
		comp_gfx(dm, 0);
	}
	else if (dm->cur == 9)
	{
		Mix_VolumeMusic(dm->volume);
		Mix_Volume(-1, dm->volume);
	}
}

void	menu_keys_hold(int key, t_doom *dm)
{
	if (key == RIGHT && dm->cur == 11)
		dm->netstat = connect_server(dm);
	else if (key == LEFT && dm->cur == 11)
	{
		SDLNet_TCP_Close(dm->sock);
		dm->netstat = 0;
	}
	else if (key == LEFT && dm->cur != 11)
	{
		(*dm->options[dm->cur])--;
		if ((*dm->options[dm->cur]) < 0)
			(*dm->options[dm->cur]) = 0;
	}
	else if (key == RIGHT && dm->cur != 11)
	{
		(*dm->options[dm->cur])++;
		if ((*dm->options[dm->cur]) > (int)dm->maxvalue[dm->cur])
			(*dm->options[dm->cur]) = (int)dm->maxvalue[dm->cur];
	}
	menu_keys_hold_more(key, dm);
}

void	menu_keys_more(int key, t_doom *dm)
{
	if (dm->cur == 8)
	{
		if (dm->tile < 1)
			dm->tile = 1;
		destroy_gfx(dm, -1);
		comp_gfx(dm, 0);
	}
	else if (dm->cur == 9)
	{
		Mix_VolumeMusic(dm->volume);
		Mix_Volume(-1, dm->volume);
	}
}

void	menu_keys(int key, t_doom *dm)
{
	if (key == DOWN)
		dm->cur++;
	else if (key == UP)
		dm->cur--;
	else if (key == SPACE && (*dm->options[dm->cur]) <
		(int)dm->maxvalue[dm->cur] && dm->cur != 11)
		(*dm->options[dm->cur]) = (int)dm->maxvalue[dm->cur];
	else if (key == SPACE && dm->cur != 11)
		(*dm->options[dm->cur]) = 0;
	if (dm->cur < 0)
		dm->cur = OP;
	if (dm->cur > OP)
		dm->cur = 0;
	if (dm->minopt > dm->cur)
		dm->minopt = 0;
	if (dm->cur - dm->minopt > 9)
		dm->minopt = dm->cur - 9;
	menu_keys_more(key, dm);
}
