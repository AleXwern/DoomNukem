/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 12:48:37 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/04 15:12:59 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

t_vector	light_map(t_vector map, int side)
{
	if (side == 0)
		map.x--;
	else if (side == 1)
		map.y--;
	else if (side == 2)
		map.z--;
	else if (side == 3)
		map.x++;
	else if (side == 4)
		map.y++;
	else if (side == 5)
		map.z++;
	return (map);
}

Uint32	rl_color(t_block blk, Uint32 col)
{
	double	mod;
	Uint8	r;
	Uint8	g;
	Uint8	b;

	mod = blk.lgt / 15.0;
	r = R(col) * mod;
	g = G(col) * mod;
	b = B(col) * mod;
	col = ARGB(r, g, b);
	return (col);
}

Uint32	color_shift(Uint32 color, double shift, t_doom *dm, Uint32 ret)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;

	ret = (int)(shift * dm->shift);
	if (ret > 10 * dm->shift)
		ret = 10 * dm->shift;
	if (ret < 1)
		return (color);
	r = R(color) / ret;
	g = G(color) / ret;
	b = B(color) / ret;
	ret = ARGB(r, g, b);
	return (ret);
}

Uint32	avg_color(Uint32 rcol, Uint32 col)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;

	r = R(col) * (R(rcol) / 255.0);
	g = G(col) * (G(rcol) / 255.0);
	b = B(col) * (B(rcol) / 255.0);
	col = ARGB(r, g, b);
	return (col);
}
