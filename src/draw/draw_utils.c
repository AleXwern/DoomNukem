/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 12:48:37 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/09 12:47:32 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		light_map(t_vector map, int side, t_block ***area)
{
	int		lgt;

	if (side == 0)
		lgt = area[(int)map.z][(int)map.y][(int)map.x - 1].lgt;
	else if (side == 1)
		lgt = area[(int)map.z][(int)map.y - 1][(int)map.x].lgt;
	else if (side == 2)
		lgt = area[(int)map.z - 1][(int)map.y][(int)map.x].lgt;
	else if (side == 3)
		lgt = area[(int)map.z][(int)map.y][(int)map.x + 1].lgt;
	else if (side == 4)
		lgt = area[(int)map.z][(int)map.y + 1][(int)map.x].lgt;
	else
		lgt = area[(int)map.z + 1][(int)map.y][(int)map.x].lgt;
	return (lgt);
}

Uint32	rl_color(int lgt, Uint32 col)
{
	double	mod;
	Uint8	r;
	Uint8	g;
	Uint8	b;

	mod = lgt / 15.0;
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

	if (dm->shift > 15 || dm->shift < 0)
		dm->shift = 15;
	ret = (int)(shift * (15 - dm->shift) * 4);
	if (ret > 255)
		ret = 255;
	ret = 255 - ret;
	r = R(color) * ret / 255.0;
	g = G(color) * ret / 255.0;
	b = B(color) * ret / 255.0;
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
