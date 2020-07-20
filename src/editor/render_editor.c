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

	gy = -1;
	while (++gy < dm->winh / dm->height)
	{
		gx = -1;
		while (++gx < dm->winw / dm->width * 0.5)
		{
			dm->img.data[(int)(dm->winw * (y + gy) + (x + gx))] = blk.data[(int)(blk.wid * (gy * (blk.hgt / (dm->winh / dm->height))) + gx * (blk.wid / (dm->winw / dm->width * 0.5)))];
		}
	}
}

void	draw_level_screen(t_doom *dm, t_editor *le, double x, double y)
{
	int		gx;
	int		gy;

	gy = 0;
	while (gy < dm->height)
	{
		gx = 0;
		x = 0;
		while (gx < dm->width)
		{
			if (dm->area[le->options[3]][gy][gx] == 7)
				dm->area[le->options[3]][gy][gx] = 1;
			if (dm->area[le->options[3]][gy][gx] > 6 || dm->area[le->options[3]][gy][gx] < 1)
				dm->area[le->options[3]][gy][gx] = 2;
			draw_block(dm, dm->gfx[dm->area[le->options[3]][gy][gx]], x, y);
			x += dm->winw / dm->width * 0.5;
			gx++;
		}
		y += dm->winh / dm->height;
		gy++;
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