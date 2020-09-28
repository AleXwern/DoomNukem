/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 12:48:37 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/28 13:59:44 by AleXwern         ###   ########.fr       */
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
	r = ((col >> 16) & 0xff) * mod;
	g = ((col >> 8) & 0xff) * mod;
	b = (col & 0xff) * mod;
	col = (0xff000000 | (r << 16) | (b << 8) | g);
	return (col);
}

Uint32	color_shift(Uint32 color, double shift, t_doom *dm, Uint32 ret)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;

	if (dm->shift > 15 || dm->shift < 0)
		dm->shift = 15;
	ret = (int)(shift * (15 - dm->shift) * 10);
	if (ret > 255)
		ret = 255;
	ret = 255 - ret;
	r = ((color >> 16) & 0xff) * ret / 255.0;
	g = ((color >> 8) & 0xff) * ret / 255.0;
	b = (color & 0xff) * ret / 255.0;
	ret = (0xff000000 | (r << 16) | (b << 8) | g);
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
