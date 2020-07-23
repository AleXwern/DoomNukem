/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:43 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:32:22 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_blk_select(t_doom* dm, t_editor *le, int x, int y)
{
	int		tx;

	tx = 0;
	while (x < dm->winw - 750)
	{
		y = 0;
		while (y <= 107)
		{
			if (x % 107 == 0 || y % 107 == 0)
				dm->img.data[dm->winw * (y + 375) + (x + 750)] = 0xfffcba03;
			else if (x >= ((le->blk - 1) * 107) && x < (le->blk * 107))
				dm->img.data[dm->winw * (y + 375) + (x + 750)] = dm->gfx[le->blk].data[(int)(dm->gfx[le->blk].wid * y + tx)];
			else
				dm->img.data[dm->winw * (y + 375) + (x + 750)] = 0xff000000;
			y++;
		}
		x++;
		if (x >= ((le->blk - 1) * 107) && x < (le->blk * 107))
			tx++;
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
			//dm->img.data[dm->winw * gy + gx] = gfx.data[gfx.wid * y + x];
			dm->img.data[dm->winw * gy + gx] = 0xff000000;
		}
	}
}

void	draw_block(t_doom *dm, t_gfx blk, double x, double y)
{
	double		gx;
	double		gy;
	int			ckflr;

	gy = -1;
	ckflr = dm->flr + 1;
	if (ckflr >= dm->mxflr)
		ckflr = dm->mxflr - 1;
	while (++gy < dm->winh / dm->height)
	{
		gx = -1;
		while (++gx < dm->winw / dm->width * 0.5)
		{
			if (dm->flr == dm->mxflr - 1 && dm->area[dm->flr][dm->y][dm->x] == 1)
				dm->img.data[(int)(dm->winw * (y + gy) + (x + gx))] = 0xff696969;
			else if (dm->area[ckflr][dm->y][dm->x] == 1 && dm->area[dm->flr][dm->y][dm->x] == 1)
				dm->img.data[(int)(dm->winw * (y + gy) + (x + gx))] = 0xff696969;
			else
				dm->img.data[(int)(dm->winw * (y + gy) + (x + gx))] = blk.data[(int)(blk.wid * (gy * (blk.hgt / (dm->winh / dm->height))) + gx * (blk.wid / (dm->winw / dm->width * 0.5)))];
		}
	}
}

void	draw_level_screen(t_doom *dm, t_editor *le, double x, double y)
{
	dm->y = 0;
	dm->flr = le->options[3];
	while (dm->y < dm->height)
	{
		dm->x = 0;
		x = 0;
		while (dm->x < dm->width)
		{
			if (dm->area[le->options[3]][dm->y][dm->x] == 7)
				dm->area[le->options[3]][dm->y][dm->x] = 1;
			if (dm->area[le->options[3]][dm->y][dm->x] > 6 || dm->area[le->options[3]][dm->y][dm->x] < 1)
				dm->area[le->options[3]][dm->y][dm->x] = 2;
			draw_block(dm, dm->gfx[dm->area[dm->flr][dm->y][dm->x]], x, y);
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
			while (++x < dm->winw / 2 * (le->options[i] / le->maxval[i]) && x < dm->winw)
			{
				if (0xffffcd38 + x > 0xffffcdff)
					color = 0xffffcdff;
				else
					color = 0xffffcd38 + x;
				dm->img.data[dm->winw * (y + sy) + (x + sx)] = color;
			}
			while (++x < dm->winw / 2)
			{
				if (x < (0xff * 2))
					black = 0xff000000 + (x / 2 * 0x00010000) + (x / 2 * 0x00000100) + (x / 2);
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