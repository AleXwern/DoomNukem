/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:52:14 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/28 16:16:25 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	int YX values
**	0 = Y start point on screen
**	1 = X start point on screen
**	2 = Y end point in relative to start point gfx.y (1 equals 1 towards Y dir)
**	3 = X end point in relative to start point gfx.x
**	4 = pass 0
**	5 = pass 0
**	pass point like (int[6]){1, 1, 1000, 1000, 0, 0}
*/
void	draw_sprite_gfx(t_doom *dm, t_gfx gfx, int *yx, double size)
{
	int		gy;
	int		gx;

	gy = 0;
	while (gy < gfx.hgt * size && (yx[0] + gy) < dm->winh && gy < yx[2] * size)
	{
		yx[4] = gy * (gfx.hgt / (gfx.hgt * size));
		gx = 0;
		while (gx < gfx.wid * size && (yx[1] + gx) < dm->winw && gx < yx[3] * size)
		{
			yx[5] = gx * (gfx.wid / (gfx.wid * size));
			if (gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)] != 0xffff00ff &&
				dm->spr.dist < dm->wallarr[dm->winw * (yx[0] + gy) + (yx[1] + gx)] &&
				yx[4] + gfx.y < gfx.hgt && yx[5] + gfx.x < gfx.wid)
				dm->img.data[dm->winw * (yx[0] + gy) + (yx[1] + gx)] = gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)];
			gx++;
		}
		gy++;
	}
}