/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_coll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:29:03 by anystrom          #+#    #+#             */
/*   Updated: 2021/01/04 14:06:03 by vkeinane         ###   ########.fr       */
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

int		dircheck(t_block blk, t_doom *dm, char dir)
{
	if (dir == 'y')
	{
		if ((int)(dm->pos.y + dm->gravity.y) - (int)(dm->pos.y) == 0)
			return (1);
		if (blk.pt == 11 && dm->gravity.y < 0)
			return (1);
		if (blk.pt == 12 && dm->gravity.y > 0)
			return (1);
	}
	else if (dir == 'x')
	{
		if ((int)(dm->pos.x + dm->gravity.x) - (int)(dm->pos.x) == 0)
			return (1);
		if (blk.pt == 13 && dm->gravity.x < 0)
			return (1);
		if (blk.pt == 14 && dm->gravity.x > 0)
			return (1);
	}
	return (0);
}

int		zy_slope(t_block blk, t_doom *dm, double hgt, char dir)
{
	hgt = 0;
	if (blk.pt == 11 && dir == 'y')
		hgt = ((dm->pos.y + dm->gravity.y) - (int)(dm->pos.y)) -
			(dm->pos.y - (int)dm->pos.y);
	else if (blk.pt == 12 && dir == 'y')
		hgt = (((dm->truez + dm->gravity.y) - (int)(dm->truez)) -
			(dm->truez - (int)dm->truez)) * -1;
	else if (blk.pt == 13 && dir == 'x')
		hgt = ((dm->pos.x + dm->gravity.x) - (int)(dm->pos.x)) -
			(dm->pos.x - (int)dm->pos.x);
	else if (blk.pt == 14 && dir == 'x')
		hgt = (((dm->truez + dm->gravity.x) - (int)(dm->truez)) -
			(dm->truez - (int)dm->truez)) * -1;
	if (hgt < 0.45 && hgt > -0.45 && dircheck(blk, dm, dir))
	{
		if (hgt < 0)
			hgt -= 0.02;
		dm->pos.z += hgt;
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
