/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_editor2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:05:33 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/16 14:14:42 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_blk_select2(t_doom *dm, t_editor *le, int x, int y)
{
	if (x % 107 == 0 || y % 107 == 0)
		dm->img.data[dm->winw * (y + 375) + (x + 750)] = 0xfffcba03;
	else if (le->blk == dm->selectedblk)
		dm->img.data[dm->winw * (y + 375) + (x + 750)] =
			dm->gfx[dm->selectedblk].data[dm->gfx[dm->selectedblk].wid
				* y + dm->blktx];
	else
		dm->img.data[dm->winw * (y + 375) + (x + 750)] =
			((dm->gfx[dm->selectedblk].data[dm->gfx[dm->selectedblk].wid
			* y + dm->blktx]) >> 2) & DARKEN2;
}

void	draw_blk_select(t_doom *dm, t_editor *le, int x, int y)
{
	dm->blktx = 0;
	dm->selectedblk = 0;
	while (x < dm->winw - 750)
	{
		y = -1;
		while (++y <= 107)
			draw_blk_select2(dm, le, x, y);
		x++;
		dm->blktx++;
		if (dm->blktx >= 107)
		{
			dm->blktx = 0;
			dm->selectedblk++;
		}
	}
}

void	draw_sliders2(t_doom *dm, int x, int y)
{
	Uint32	black;

	while ((++x + dm->sldrx) < dm->winw)
	{
		if (x < (0xff * 2))
			black = 0xff000000 + (x / 2 * 0x00010000) +
				(x / 2 * 0x00000100) + (x / 2);
		else
			black = 0xffffffff;
		dm->img.data[dm->winw * (y + dm->sldry) + (x + dm->sldrx - 1)] = black;
	}
}

void	draw_sliders(t_doom *dm, t_editor *le, int x, int y)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		dm->sldry = (i * (dm->winh / 10) + 2);
		dm->sldrx = dm->winw / 2 + 2;
		y = 0;
		while (++y < (dm->winh / 10) - 2)
		{
			x = -1;
			le->options[i] = le->options[i] & 0x7f;
			while (++x < dm->winw / 2 * (le->options[i] / le->maxval[i]) &&
				(x + dm->sldrx) < dm->winw)
			{
				if (0xffffcd38 + x > 0xffffcdff)
					dm->sldrcol = 0xffffcdff;
				else
					dm->sldrcol = 0xffffcd38 + x;
				dm->img.data[dm->winw * (y + dm->sldry) + (x + dm->sldrx)] =
					dm->sldrcol;
			}
			draw_sliders2(dm, x, y);
		}
	}
}
