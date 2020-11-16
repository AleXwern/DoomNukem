/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:08:53 by tbergkul          #+#    #+#             */
/*   Updated: 2020/11/13 13:01:43 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	shift_door(t_doom *dm, double shift, t_block blk, int side)
{
	if (blk.pt == 1)
		dm->texy += 128 * (1 - blk.pln / 15.0);
	else if (blk.pt == 2)
		dm->texy += 128 * (blk.pln / 15.0);
	else if ((blk.pt == 3 && side == 0) || (blk.pt == 4 && side == 3) ||
			(blk.pt == 6 && side == 1) || (blk.pt == 5 && side == 4))
		dm->texx += 128 * (blk.pln / 15.0);
	else if ((blk.pt == 3 && side == 3) || (blk.pt == 4 && side == 0) ||
			(blk.pt == 5 && side == 1) || (blk.pt == 6 && side == 4))
		dm->texx += 128 * (1 - blk.pln / 15.0);
	dm->col = color_shift(dm->gfx[dm->texnum].data[((dm->texy + (int)shift) %
		128) * 128 + dm->texx % 128], dm->walldist + fabs((double)(dm->x -
		dm->winw / 2) / dm->winw), dm, 0);
}

void	layer_draw(t_doom *dm, double shift, int layer)
{
	if (dm->gfx[layer].data[((dm->texy + (int)shift) % 128)
		* 128 + dm->texx % 128] != 0xffff00ff)
	{
		dm->col = color_shift(dm->gfx[layer].data[((dm->texy + (int)shift)
		% 128) * 128 + dm->texx % 128], dm->walldist
		+ fabs((double)(dm->x - dm->winw / 2) / dm->winw), dm, 0);
	}
	else
	{
		dm->col = color_shift(dm->gfx[dm->texnum].data[((dm->texy
		+ (int)shift) % 128) * 128 + dm->texx % 128], dm->walldist
		+ fabs((double)(dm->x - dm->winw / 2) / dm->winw), dm, 0);
	}
}

/*
**	Paintings.meta: 1 = west, 2 = north, 3 = east, 4 = south
**	pt: 3n 4s 5w 6e		side: 1w 2n 3e 4s
*/

void	check_layer(t_doom *dm, double shift)
{
	if ((dm->side < 2 && dm->blk.meta == (dm->side + 1)) || (dm->side > 2 &&
			dm->blk.meta == dm->side))
		layer_draw(dm, shift, 38);
	else if (dm->blk.meta == 5 && ((dm->side == 3 && dm->blk.pt == 3) ||
		(dm->side == 0 && dm->blk.pt == 4) || (dm->side == 1 && dm->blk.pt == 5)
		|| (dm->side == 4 && dm->blk.pt == 6)))
		layer_draw(dm, shift, 39);
	else if (dm->blk.meta == 5 && ((dm->side == 0 && dm->blk.pt == 3) ||
		(dm->side == 3 && dm->blk.pt == 4) || (dm->side == 1 && dm->blk.pt == 6)
		|| (dm->side == 4 && dm->blk.pt == 5)))
		layer_draw(dm, shift, 40);
	else if (dm->blk.meta == 6 && ((dm->side == 3 && dm->blk.pt == 3) ||
		(dm->side == 0 && dm->blk.pt == 4) || (dm->side == 1 && dm->blk.pt == 5)
		|| (dm->side == 4 && dm->blk.pt == 6)))
		layer_draw(dm, shift, 41);
	else if (dm->blk.meta == 6 && ((dm->side == 0 && dm->blk.pt == 3) ||
		(dm->side == 3 && dm->blk.pt == 4) || (dm->side == 1 && dm->blk.pt == 6)
		|| (dm->side == 4 && dm->blk.pt == 5)))
		layer_draw(dm, shift, 42);
	else
		dm->col = color_shift(dm->gfx[dm->texnum].data[((dm->texy +
		(int)shift) % 128) * 128 + dm->texx % 128], dm->walldist +
		fabs((double)(dm->x - dm->winw / 2) / dm->winw), dm, 0);
}

void	draw_stripe(t_doom *dm)
{
	double	shift;

	if (dm->texbool)
	{
		shift = (dm->pos.z - floor(dm->pos.z));
		shift = ((shift - 0.5) * 128);
		if (shift < 0)
			shift = 128 + shift;
		dm->texy = (int)((((dm->y * 256 - dm->winh * 128 * dm->camshift -
			dm->lineh * 128) * 128) / dm->lineh) / 256) % 128;
		if (dm->texy < 0)
			dm->texy += 128;
		if (dm->blk.b == 5)
			shift_door(dm, shift, dm->blk, dm->side);
		check_layer(dm, shift);
		dm->lgt = light_map(dm->map, dm->side, dm->area);
		dm->col = rl_color(dm->lgt, dm->col);
	}
	if (dm->side > 2)
		dm->col = (dm->col >> 1) & DARKEN;
	dm->img.data[dm->winw * dm->y + dm->x] = dm->col;
}

void	wall_stripe(t_doom *dm)
{
	if (dm->texbool)
	{
		//if (dm->side == 0 || dm->side == 1)
			dm->texnum = dm->area[(int)(dm->map.z)][(int)(dm->map.y)]
				[(int)(dm->map.x)].b;
		//else
		//	dm->texnum = dm->area[(int)ceil(dm->map.z)]
		//		[(int)ceil(dm->map.y)][(int)ceil(dm->map.x)].b;
		if (dm->side % 3 == 0)
			dm->wallx = (dm->pos.y + dm->walldist * dm->rayd.y);
		else
			dm->wallx = (dm->pos.x + dm->walldist * dm->rayd.x);
		dm->wallx -= floor(dm->wallx);
		dm->texx = (int)(dm->wallx * 128.0);
		if (dm->side == 0)
			dm->texx = 128 - dm->texx - 1;
		else if (dm->side == 4)
			dm->texx = 128 - dm->texx - 1;
	}
	else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b != 2)
		dm->col = 0xff22a800;
	draw_stripe(dm);
	if (dm->wincol)
		ext_ray(dm);
}
