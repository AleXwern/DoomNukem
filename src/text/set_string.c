/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 12:27:40 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/30 14:13:50 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_text(t_doom *dm, t_gfx gfx, int *yx, double size)
{
	int		gy;
	int		gx;

	gy = 0;
	while (gy < gfx.hgt * size && (yx[0] + gy) < dm->winh && gy < yx[2] * size)
	{
		yx[4] = gy * (gfx.hgt / (gfx.hgt * size));
		gx = 0;
		while (gx < gfx.wid * size && (yx[1] + gx) < dm->winw && gx < yx[3]
			* size)
		{
			yx[5] = gx * (gfx.wid / (gfx.wid * size));
			if (gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)]
					!= 0xffff00ff && gfx.data[gfx.wid * (yx[4] + gfx.y)
					+ (yx[5] + gfx.x)] != 0xff00ff)
				dm->img.data[dm->winw * (yx[0] + gy) + (yx[1] + gx)] = yx[6];
			gx++;
		}
		gy++;
	}
}

/*
**	int YX values
**	0 = Y start point on screen
**	1 = X start point on screen
**	2 = color hex value
**	pass point like (int[3]){1, 1, 0}
*/

void	set_text(t_doom *dm, char *str, int *xy, double size)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			dm->gfx[33].x = (str[i] - 97) * 27;
			draw_text(dm, dm->gfx[33], (int[7]){xy[0], xy[1], 26, 27,
				0, 0, xy[2]}, size);
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			dm->gfx[33].x = 727 + (str[i] - 48) * 27;
			draw_text(dm, dm->gfx[33], (int[7]){xy[0], xy[1], 26, 27,
				0, 0, xy[2]}, size);
		}
		else if (str[i] == '\n')
		{
			xy[0] += 28 * size;
			xy[1] -= 27 * (i + 1) * size;
		}
		xy[1] += 27 * size;
		i++;
	}
}

void	set_ftext(t_doom *dm, char *str, int *xy, double size)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			dm->gfx[33].x = (str[i] - 97) * 27;
			draw_text(dm, dm->gfx[33], (int[7]){xy[0], xy[1], 26, 27,
				0, 0, xy[2]}, size);
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			dm->gfx[33].x = 727 + (str[i] - 48) * 27;
			draw_text(dm, dm->gfx[33], (int[7]){xy[0], xy[1], 26, 27,
				0, 0, xy[2]}, size);
		}
		else if (str[i] == '\n')
		{
			xy[0] += 28 * size;
			xy[1] -= 27 * (i + 1) * size;
		}
		xy[1] += 27 * size;
	}
	free(str);
}
