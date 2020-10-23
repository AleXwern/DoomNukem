/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_coll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:29:03 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/21 15:49:20 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"
/*
** 7  down	yz
** 8  down	-y-z
** 9  down	xz
** 10 down	-xz
** 11 up	y-z
** 12 up	-yz
** 13 up	x-z
** 14 up	-x-z
** 15		xy
** 16		x-y
** 17		-x-y
** 18		-xy
*/

int		zy_slope(t_block blk, t_doom *dm, double hgt, char dir)
{
	if (dir == 'y')
		hgt = (dm->pos.z + 1 - ((dm->pos.y + dm->gravity.y) - (int)(dm->pos.y + dm->gravity.y))) - dm->pos.z;
	else
		hgt = (dm->pos.z + 1 - (dm->pos.y - (int)dm->pos.y)) - dm->pos.z;
	printf("%f\n", hgt);
	if (hgt < 0.4 && hgt > -0.4)
	{
		if (!dm->airbrn)
			dm->pos.z -= hgt;
		return (1);
	}
	return (0);
}

int		slope_coll(t_block blk, t_doom *dm, char dir)
{
	if (blk.pt < 11)
		return (0);
	if (blk.pt == 11)
		return (zy_slope(blk, dm, 0, dir));
	return (0);
}