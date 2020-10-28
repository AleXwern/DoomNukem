/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_editor_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:34:11 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/28 15:10:13 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		draw_screen_more(t_editor *le, t_doom *dm, int x, int y)
{
	if (y >= dm->height || x >= dm->width)
		return (1);
	if (y < 0 || x < 0)
		return (1);
	if (le->blk == 7)
	{
		dm->area[(int)dm->spw.z][(int)dm->spw.y][(int)dm->spw.x].b = 1;
		dm->spw.x = x + 0.51;
		dm->spw.y = y + 0.51;
		dm->spw.z = le->options[0] + 0.5;
	}
	if (dm->area[le->options[0]][y][x].b != 7)
	{
		dm->area[le->options[0]][y][x].b = le->blk;
		dm->area[le->options[0]][y][x].lgt = le->options[1];
		dm->area[le->options[0]][y][x].pt = le->options[2];
		if (le->blk == 1 || le->blk == 7)
			dm->area[le->options[0]][y][x].pt = 0;
		else
			dm->area[le->options[0]][y][x].pln = le->options[3];
		dm->area[le->options[0]][y][x].meta = le->options[4];
	}
	return (0);
}

void	set_sprite_tomap(t_editor *le, t_doom *dm, int x, int y)
{
	if (x < 20)
		x = 20;
	else if (x > 730)
		x = 730;
	if (y < 20)
		y = 20;
	else if (y > 730)
		y = 730;
	if (le->spr < 11)
	{
		dm->spr[le->spr].pos.z = le->options[0] + 0.5;
		dm->spr[le->spr].pos.y = (y / 750.0) * 25;
		dm->spr[le->spr].pos.x = (x / 750.0) * 25;
	}
	else
	{
		if (le->options[1] >= 3)
			dm->obj[le->spr - 11].pos.z = le->options[0] + 0.9;
		else
			dm->obj[le->spr - 11].pos.z = le->options[0] + 0.5;
		dm->obj[le->spr - 11].pos.y = (y / 750.0) * 25;
		dm->obj[le->spr - 11].pos.x = (x / 750.0) * 25;
	}
}

void	update_sprite(t_doom *dm, t_editor *le)
{
	if (le->spr < 11)
	{
		dm->spr[le->spr].gfx = le->options[1] + 16;
		dm->spr[le->spr].respawn = le->options[2] * TIMERMOD;
		dm->spr[le->spr].hp = le->options[3];
		dm->spr[le->spr].dead = le->options[4];
	}
	else
	{
		dm->obj[le->spr - 11].gfx = set_objsmallsprite(le->options[1]);
		dm->obj[le->spr - 11].dead = 0;
	}
}

void	grab_sprite(t_doom *dm, t_editor *le, int spr, int cury)
{
	if (cury < 483)
		spr = ((spr - 750) / 107) + 4;
	else
		spr = ((spr - 750) / 57) + 11;
	if (spr >= SPR + OBJ)
		spr = SPR + OBJ - 1;
	le->spr = spr;
	if (spr < 11)
	{
		le->options[1] = dm->spr[spr].gfx - 16;
		le->options[2] = dm->spr[spr].respawn / TIMERMOD;
		le->options[3] = dm->spr[spr].hp;
		le->options[4] = dm->spr[spr].dead;
	}
	else
		le->options[1] = get_objsmallsprite(dm->obj[le->spr - 11].gfx);
	
}

void	get_sprite(t_doom *dm, t_editor *le)
{
	if (le->spr < 11)
	{
		le->options[1] = dm->spr[le->spr].gfx - 16;
		le->options[2] = dm->spr[le->spr].respawn;
		le->options[3] = dm->spr[le->spr].hp;
		le->options[4] = dm->spr[le->spr].dead;
	}
	else
	{
		le->options[1] = get_objsmallsprite(dm->obj[le->spr - 11].gfx);
		le->options[2] = dm->obj[le->spr - 11].respawn;
		le->options[3] = dm->obj[le->spr - 11].hp;
		le->options[4] = dm->obj[le->spr - 11].dead;
	}
}
