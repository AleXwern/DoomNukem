/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 12:15:27 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/26 13:42:27 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_part_gfx(t_doom *dm, t_gfx gfx, int *max, int *xy)
{
	int	gx;
	int	gy;

	gy = gfx.y;
	while (gy < gfx.hgt && (xy[0] + gy) < dm->winh && gy < max[0])
	{
		gx = gfx.x;
		while (gx < gfx.wid && (xy[1] + gx) < dm->winw && gx < max[1])
		{
			if (gfx.data[gfx.wid * gy + gx] != 0xffff00ff)
				dm->img.data[dm->winw * (xy[0] + gy) + (xy[1] + gx)] =
						gfx.data[gfx.wid * gy + gx];
			gx++;
		}
		gy++;
	}
}

void	draw_scaled_gfx(t_doom *dm, t_gfx gfx, int x, int y) //DO NO USE
{
	t_ivector	g;
	t_ivector	i;

	g.y = 0;
	i.y = 1;
	while (g.y < gfx.hgt && (y + g.y) < dm->winh)
	{
		i.y = 0;
		g.x = 1;
		while (g.x < gfx.wid && (x + g.x) < dm->winw)
		{
			if (gfx.data[(int)(gfx.wid * g.y + g.x)] != -65281)
				dm->img.data[(int)(dm->winw * (y + g.y) + (x + g.x))] = gfx.data[(int)(gfx.wid *
					g.y + g.x)];
			g.x += g.x * (gfx.wid / dm->winw);
			g.x++;
		}
		g.y += g.y * (gfx.hgt / dm->winh);
		g.y++;
	}
}

void	draw_menu(t_doom *dm, int x, int y, int cur)
{
	int		gy;
	int		gx;

	gy = -1;
	while (++gy < dm->winh)
	{
		y = gy * (dm->gfx[9].hgt / (double)dm->winh);
		gx = -1;
		while (++gx < dm->winw / 2)
		{
			x = gx * (dm->gfx[9].wid / ((double)dm->winw / 2));
			if (gy > (cur * dm->winh / 10) && gy < ((cur + 1) * dm->winh / 10))
				dm->img.data[dm->winw * gy + gx] = dm->gfx[9].data[dm->gfx[9].wid * y + x] + 0x00252525;
			else
				dm->img.data[dm->winw * gy + gx] = dm->gfx[9].data[dm->gfx[9].wid * y + x];
		}
		while (++gx < dm->winw)
			dm->img.data[dm->winw * gy + gx] = 0xff1821ac;
	}
}

void	draw_gfx(t_doom *dm, t_gfx gfx, int x, int y)
{
	int	gx;
	int	gy;

	gy = 0;
	while (gy < gfx.hgt && (y + gy) < dm->winh)
	{
		gx = 0;
		while (gx < gfx.wid && (x + gx) < dm->winw)
		{
			if (gfx.data[gfx.wid * gy + gx] != 0xffff00ff)
				dm->img.data[dm->winw * (y + gy) + (x + gx)] = gfx.data[gfx.wid *
					gy + gx];
			gx++;
		}
		gy++;
	}
}