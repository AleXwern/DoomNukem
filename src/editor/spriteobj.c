/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteobj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:29:33 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/28 12:51:41 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	dim_sprite(t_doom *dm, int x, int y, int res)
{
	int		xmax;
	int		ymax;

	xmax = x + res;
	ymax = y + res;
	while (x < xmax)
	{
		while (y < ymax)
		{
			dm->img.data[dm->winw * y + x] =
				(dm->img.data[dm->winw * y + x] >> 1) & DARKEN;
			y++;
		}
		y -= res;
		x++;
	}
}

void	draw_objselect(t_doom *dm, t_editor *le, int x, int i)
{
	le->ylev = 486;
	while (++i < OBJ)
	{
		dm->gfx[dm->obj[i].gfx].y = 0;
		dm->gfx[dm->obj[i].gfx].x = 0;
		dm->gfx[10].x = 57 * get_objsmallsprite(dm->obj[i].gfx);
		draw_pgfx_sc(dm, dm->gfx[10],
			(int[6]){le->ylev, x, 57, 57, 0, 0}, 1);
		if (le->spr - 11 != i)
			dim_sprite(dm, x, le->ylev, 57);
		x += 57;
	}
}

void	draw_sprselect(t_doom *dm, t_editor *le, int x, int i)
{
	le->ylev = 378;
	while (++i < SPR)
	{
		dm->gfx[dm->spr[i].gfx].y = 0;
		dm->gfx[dm->spr[i].gfx].x = 0;
		draw_pgfx_sc(dm, dm->gfx[dm->spr[i].gfx],
			(int[6]){le->ylev, x, 26, 26, 0, 0}, 4);
		if (le->spr != i)
			dim_sprite(dm, x, le->ylev, 104);
		x += 104;
	}
	draw_objselect(dm, le, 750, -1);
}

void	draw_layerobj(t_doom *dm, t_editor *le, int x, int y)
{
	int	i;

	i = -1;
	while (++i < OBJ)
	{
		if ((int)dm->obj[i].pos.z == le->options[0])
		{
			dm->gfx[dm->obj[i].gfx].y = 0;
			dm->gfx[dm->obj[i].gfx].x = 0;
			x = (dm->obj[i].pos.x / 25 * 750) - 13;
			y = (dm->obj[i].pos.y / 25 * 750) - 17;
			dm->gfx[10].x = 57 * get_objsmallsprite(dm->obj[i].gfx);
			draw_pgfx_sc(dm, dm->gfx[10], (int[6]){y, x, 57, 57, 0, 0}, 0.5);
		}
	}
}

void	draw_layerspr(t_doom *dm, t_editor *le, int x, int y)
{
	int	i;

	i = 3;
	while (++i < SPR)
	{
		if ((int)dm->spr[i].pos.z == le->options[0])
		{
			dm->gfx[dm->spr[i].gfx].y = 0;
			dm->gfx[dm->spr[i].gfx].x = 0;
			x = (dm->spr[i].pos.x / 25 * 750) - 13;
			y = (dm->spr[i].pos.y / 25 * 750) - 17;
			draw_pgfx_sc(dm, dm->gfx[dm->spr[i].gfx], (int[6]){y, x, 34, 27, 0, 0}, 1);
		}
	}
	draw_layerobj(dm, le, x, y);
}
