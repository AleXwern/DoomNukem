/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:43 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/08 16:22:39 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_bg(t_doom *wlf, t_gfx gfx)
{
	int		gy;
	int		gx;
	int		x;
	int		y;

	gy = -1;
	while (++gy < wlf->winh)
	{
		y = gy * (gfx.hgt / (double)wlf->winh);
		gx = -1;
		while (++gx < wlf->winw)
		{
			x = gx * (gfx.wid / ((double)wlf->winw));
			//wlf->img.data[wlf->winw * gy + gx] = gfx.data[gfx.wid * y + x];
			wlf->img.data[wlf->winw * gy + gx] = 0xff000000;
		}
	}
}

void	draw_block(t_doom *dm, t_gfx blk, int x, int y)
{
	int		gx;
	int		gy;

	gy = -1;
	while (++gy < dm->winh / dm->height)
	{
		gx = -1;
		while (++gx < dm->winw / dm->width * 0.66)
		{
			dm->img.data[dm->winw * (y + gy) + (x + gx)] = blk.data[blk.wid * gy * (blk.wid / (dm->winh / dm->height)) + gx * (blk.wid / (int)(dm->winw / dm->width * 0.66))];
		}
	}
}

void	draw_level_screen(t_doom *wlf, t_editor *le, int x, int y)
{
	int		gx;
	int		gy;

	gy = 0;
	while (gy < wlf->height)
	{
		gx = 0;
		x = 0;
		while (gx < wlf->width)
		{
			//printf("%d %d\n%d %d\n\n", gx, gy, x, y);
			draw_block(wlf, wlf->gfx[wlf->map[2][gy][gx]], x, y);
			x += wlf->winw / wlf->width * 0.66;
			gx++;
			//printf("af%d %d\n%d %d\n\n", gx, gy, x, y);
		}
		y += wlf->winh / wlf->height;
		gy++;
	}
}

/*
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
		sy = (i * (dm->winh / 10));
		sx = wlf->winw / 2;
		y = 0;
		while (++y < wlf->winh / 10 - 1)
		{
			x = -1;
			*wlf->options[pc] = abs(*wlf->options[pc]);
			while (++x < wlf->winw / 2 * (*wlf->options[pc] / wlf->maxvalue[pc]) && x < wlf->winw)
			{
				if (0xffffcd38 + x > 0xffffcdff)
					color = 0xffffcdff;
				else
					color = 0xffffcd38 + x;
				wlf->img.data[wlf->winw * (y + sy) + (x + sx)] = color;
			}
			while (++x < wlf->winw / 2 + 1)
			{
				if (x < (0xff * 2))
					black = 0xff000000 + (x / 2 * 0x00010000) + (x / 2 * 0x00000100) + (x / 2);
				else
					black = 0xffffffff;
				wlf->img.data[wlf->winw * (y + sy) + (x + sx - 1)] = black;
			}
		}
	}
}*/