/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_coll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:29:03 by anystrom          #+#    #+#             */
/*   Updated: 2020/11/13 15:37:17 by anystrom         ###   ########.fr       */
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

int		xy_slope(t_block blk, t_doom *dm, double pos, char dir)
{
	t_vector	npos;

	if (dir == 'x')
	{
		npos.x = (dm->pos.x + dm->gravity.x) - (int)(dm->pos.x + dm->gravity.x);
		npos.y = dm->pos.y - (int)dm->pos.y;
	}
	else
	{
		npos.x = dm->pos.x - (int)dm->pos.x;
		npos.y = (dm->pos.y + dm->gravity.y) - (int)(dm->pos.y + dm->gravity.y);
	}
	if (blk.pt == 15)
		if (npos.x + npos.y > 1)
			return (1);
	if (blk.pt == 17)
		if (npos.x + npos.y < 1)
			return (1);
	if (blk.pt == 16)
		if (npos.x > npos.y)
			return (1);
	if (blk.pt == 18)
		if (npos.x < npos.y)
			return (1);
	return (0);
}

int		zy_slope(t_block blk, t_doom *dm, double hgt, char dir)
{
	//printf("blk.b = %d  blk.pt = %d  dir = %c\n", blk.b, blk.pt, dir);
	if (blk.pt == 11)
		hgt = 1 - ((dm->pos.y + dm->gravity.y) -
			(int)(dm->pos.y + dm->gravity.y));
	else if (blk.pt == 12)
		hgt = (((dm->pos.y + dm->gravity.y) -
			(int)(dm->pos.y + dm->gravity.y)));
	else if (blk.pt == 13)
		hgt = (1 - ((dm->pos.x + dm->gravity.x) -
			(int)(dm->pos.x + dm->gravity.x)));
	else if (blk.pt == 14)
    	hgt = (((dm->pos.x + dm->gravity.x) -
			(int)(dm->pos.x + dm->gravity.x)));
	printf("hgt %f\n", (dm->pos.y - (int)dm->pos.y) - ((dm->pos.y + dm->gravity.y) - (int)(dm->pos.y + dm->gravity.y)));
	//if (hgt < 0.45 && hgt > -0.45)
	{
		//if (!dm->airbrn)
		//	dm->pos.z -= hgt;
		dm->pos.z -= dm->pos.y - (int)dm->pos.y;
		dm->pos.z += (dm->pos.y + dm->gravity.y) - (int)(dm->pos.y + dm->gravity.y);
		return (1);
	}
	return (0);
}

int		slope_coll(t_block blk, t_doom *dm, char dir)
{
	if (blk.pt < 11)
		return (0);
	if (blk.pt >= 11 && blk.pt <= 14)
		return (zy_slope(blk, dm, 0, dir));
	else if (blk.pt >= 15)
		return (xy_slope(blk, dm, 0, dir));
	return (0);
}
