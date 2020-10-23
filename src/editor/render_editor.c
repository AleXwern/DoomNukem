/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:43 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/19 15:13:05 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_bg(t_doom *dm, t_gfx gfx)
{
	int	gy;
	int	gx;
	int	x;
	int	y;

	gy = -1;
	while (++gy < dm->winh)
	{
		y = gy * (gfx.hgt / (double)dm->winh);
		gx = -1;
		while (++gx < dm->winw)
		{
			x = gx * (gfx.wid / ((double)dm->winw));
			dm->img.data[dm->winw * gy + gx] = 0xff000000;
		}
	}
}

void	draw_block2(t_doom *dm, t_gfx blk, double gy, double gx)
{
	dm->blkcol = blk.data[(int)(blk.wid * (gy * (blk.hgt / (dm->winh
		/ dm->height))) + gx * (blk.wid / (dm->winw / dm->width * 0.5)))];
	if (dm->flr == dm->mxflr - 1 && dm->area[dm->flr][dm->y][dm->x].b == 1)
		dm->img.data[(int)(dm->winw * (dm->tmpy + gy) + (dm->tmpx + gx))] =
			(dm->blkcol >> 1) & DARKEN;
	else if (dm->area[dm->ckflr][dm->y][dm->x].b == 1 &&
		dm->area[dm->flr][dm->y][dm->x].b == 1)
		dm->img.data[(int)(dm->winw * (dm->tmpy + gy)
			+ (dm->tmpx + gx))] = (dm->blkcol >> 1) & DARKEN;
	else
		dm->img.data[(int)(dm->winw * (dm->tmpy + gy)
			+ (dm->tmpx + gx))] = dm->blkcol;
}

void	draw_block(t_doom *dm, t_gfx blk)
{
	double	gx;
	double	gy;

	gy = -1;
	dm->ckflr = dm->flr + 1;
	if (dm->ckflr >= dm->mxflr)
		dm->ckflr = dm->mxflr - 1;
	while (++gy < dm->winh / dm->height)
	{
		gx = -1;
		while (++gx < dm->winw / dm->width * 0.5)
			draw_block2(dm, blk, gy, gx);
	}
}

void	draw_level_screen(t_doom *dm, t_editor *le, double x, double y)
{
	int	blk;

	dm->y = 0;
	dm->flr = le->options[0];
	while (dm->y < dm->height)
	{
		dm->x = 0;
		x = 0;
		while (dm->x < dm->width)
		{
			blk = dm->area[dm->flr][dm->y][dm->x].b;
			if (dm->area[dm->flr][dm->y][dm->x].b < 0)
				dm->area[dm->flr][dm->y][dm->x].b = 2;
			if (dm->area[dm->flr][dm->y][dm->x].b > BLK)
				dm->area[dm->flr][dm->y][dm->x].b = 2;
			dm->tmpx = x;
			dm->tmpy = y;
			draw_block(dm, dm->gfx[blk]);
			x += dm->winw / dm->width * 0.5;
			dm->x++;
		}
		y += dm->winh / dm->height;
		dm->y++;
	}
}

void	draw_editor_cursor(t_doom *dm, t_editor *le, int x, int y)
{
	int	sy;
	int	sx;

	sy = (le->cur * (dm->winh / 10));
	sx = dm->winw / 2;
	y = -1;
	while (++y < (dm->winh / 10) + 3)
	{
		x = 0;
		while ((x + sx) < dm->winw)
		{
			dm->img.data[dm->winw * (y + sy) + (x + sx)] = 0xffdb0000;
			x++;
		}
	}
}
