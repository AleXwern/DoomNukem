/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 12:15:27 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/30 15:27:54 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_scaled_gfx(t_doom *wlf, t_gfx gfx, int x, int y) //DO NO USE
{
	t_vector	g;
	t_vector	i;

	g.y = 0;
	i.y = 1;
	while (g.y < gfx.hgt && (y + g.y) < wlf->winh)
	{
		i.y = 0;
		g.x = 1;
		while (g.x < gfx.wid && (x + g.x) < wlf->winw)
		{
			if (gfx.data[(int)(gfx.wid * g.y + g.x)] != -65281)
				wlf->img.data[(int)(wlf->winw * (y + g.y) + (x + g.x))] = gfx.data[(int)(gfx.wid *
					g.y + g.x)];
			g.x += g.x * (gfx.wid / wlf->winw);
			g.x++;
		}
		g.y += g.y * (gfx.hgt / wlf->winh);
		g.y++;
	}
}

void	draw_menu(t_doom *wlf, int x, int y)
{
	int		gy;
	int		gx;

	gy = 0;
	while (gy < wlf->gfx[9].hgt && (y + gy) < wlf->winh)
	{
		gx = 0;
		while (gx < wlf->gfx[9].wid && (x + gx) < wlf->winw)
		{
			if (gy > (wlf->cur * wlf->winh / 10) && gy < ((wlf->cur + 1) * wlf->winh / 10))
				wlf->img.data[WINX * (y + gy) + (x + gx)] =
						0xffff00ff;
			else
				wlf->img.data[WINX * (y + gy) + (x + gx)] =
						wlf->gfx[9].data[wlf->gfx[9].wid * gy + gx];
			gx++;
		}
		gy++;
	}
}

void	draw_gfx(t_doom *wlf, t_gfx gfx, int x, int y)
{
	int	gx;
	int	gy;

	gy = 0;
	while (gy < gfx.hgt && (y + gy) < wlf->winh)
	{
		gx = 0;
		while (gx < gfx.wid && (x + gx) < wlf->winw)
		{
			if (gfx.data[gfx.wid * gy + gx] != 0xffff00ff)
				wlf->img.data[wlf->winw * (y + gy) + (x + gx)] = gfx.data[gfx.wid *
					gy + gx];
			gx++;
		}
		gy++;
	}
}