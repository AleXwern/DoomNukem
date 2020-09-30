/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:43 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/28 15:15:15 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_blk_select(t_doom *dm, t_editor *le, int x, int y)
{
	int		tx;
	int		blk;

	tx = 0;
	blk = 1;
	while (x < dm->winw - 750)
	{
		y = 0;
		while (y <= 107)
		{
			if (x % 107 == 0 || y % 107 == 0)
				dm->img.data[dm->winw * (y + 375) + (x + 750)] = 0xfffcba03;
			else if (le->blk == blk)
				dm->img.data[dm->winw * (y + 375) + (x + 750)] =
					dm->gfx[blk].data[dm->gfx[blk].wid * y + tx];
			else
				dm->img.data[dm->winw * (y + 375) + (x + 750)] =
					((dm->gfx[blk].data[dm->gfx[blk].wid * y + tx]) >> 2)
					& DARKEN2;
			y++;
		}
		x++;
		tx++;
		if (tx >= 107)
		{
			tx = 0;
			blk++;
		}
	}
}

void	draw_bg(t_doom *dm, t_gfx gfx)
{
	int		gy;
	int		gx;
	int		x;
	int		y;

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

void	draw_block(t_doom *dm, t_gfx blk, double x, double y)
{
	double		gx;
	double		gy;
	int			ckflr;
	Uint32		color;

	gy = -1;
	ckflr = dm->flr + 1;
	if (ckflr >= dm->mxflr)
		ckflr = dm->mxflr - 1;
	while (++gy < dm->winh / dm->height)
	{
		gx = -1;
		while (++gx < dm->winw / dm->width * 0.5)
		{
			color = blk.data[(int)(blk.wid * (gy * (blk.hgt / (dm->winh
				/ dm->height))) + gx * (blk.wid / (dm->winw / dm->width
				* 0.5)))];
			if (dm->flr == dm->mxflr - 1 && dm->area[dm->flr][dm->y]
					[dm->x].b == 1)
				dm->img.data[(int)(dm->winw * (y + gy) + (x + gx))] =
					(color >> 1) & DARKEN;
			else if (dm->area[ckflr][dm->y][dm->x].b == 1 &&
					dm->area[dm->flr][dm->y][dm->x].b == 1)
				dm->img.data[(int)(dm->winw * (y + gy) + (x + gx))] =
					(color >> 1) & DARKEN;
			else
				dm->img.data[(int)(dm->winw * (y + gy) + (x + gx))] = color;
		}
	}
}

void	draw_level_screen(t_doom *dm, t_editor *le, double x, double y)
{
	int		blk;

	dm->y = 0;
	dm->flr = le->options[0];
	while (dm->y < dm->height)
	{
		dm->x = 0;
		x = 0;
		while (dm->x < dm->width)
		{
			blk = dm->area[dm->flr][dm->y][dm->x].b;
			if (dm->area[dm->flr][dm->y][dm->x].b < 1)
				dm->area[dm->flr][dm->y][dm->x].b = 5;
			if (dm->area[dm->flr][dm->y][dm->x].b > 7)
				dm->area[dm->flr][dm->y][dm->x].b = 2;
			draw_block(dm, dm->gfx[blk], x, y);
			x += dm->winw / dm->width * 0.5;
			dm->x++;
		}
		y += dm->winh / dm->height;
		dm->y++;
	}
}

void	draw_sliders(t_doom *dm, t_editor *le, int x, int y)
{
	int		i;
	int		sy;
	int		sx;
	Uint32	color;
	Uint32	black;

	i = -1;
	while (++i < 5)
	{
		sy = (i * (dm->winh / 10) + 2);
		sx = dm->winw / 2 + 2;
		y = 0;
		while (++y < (dm->winh / 10) - 2)
		{
			x = -1;
			le->options[i] = le->options[i] & 0x7f;
			while (++x < dm->winw / 2 * (le->options[i] / le->maxval[i]) &&
				(x + sx) < dm->winw)
			{
				if (0xffffcd38 + x > 0xffffcdff)
					color = 0xffffcdff;
				else
					color = 0xffffcd38 + x;
				dm->img.data[dm->winw * (y + sy) + (x + sx)] = color;
			}
			while ((++x + sx) < dm->winw)
			{
				if (x < (0xff * 2))
					black = 0xff000000 + (x / 2 * 0x00010000) +
						(x / 2 * 0x00000100) + (x / 2);
				else
					black = 0xffffffff;
				dm->img.data[dm->winw * (y + sy) + (x + sx - 1)] = black;
			}
		}
	}
}

void	draw_editor_cursor(t_doom *dm, t_editor *le, int x, int y)
{
	int		i;
	int		sy;
	int		sx;

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
