/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteobj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:29:33 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/23 15:42:10 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	dim_sprite(t_doom *dm, int x, int y)
{
	int		xmax;
	int		ymax;

	xmax = x + 104;
	ymax = y + 104;
	while (x < xmax)
	{
		while (y < ymax)
		{
			dm->img.data[dm->winw * y + x] =
				(dm->img.data[dm->winw * y + x] >> 1) & DARKEN;
			y++;
		}
		y -= 104;
		x++;
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
			dim_sprite(dm, x, le->ylev);
		x += 104;
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
}