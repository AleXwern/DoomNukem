/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:09:19 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/23 15:28:57 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		check_part_walls2(char dir, t_block tblk, t_doom *dm)
{
	if (tblk.pt == 6 && dir == 'x')
	{
		if (dm->pos.x + dm->gravity.x < (int)(dm->pos.x + dm->gravity.x)
			+ (1 - tblk.pln / 15.0))
			return (1);
	}
	else if ((dir == 'x' && tblk.pt < 5 && check_yx('x', tblk, dm)) ||
			(dir == 'y' && tblk.pt > 4 && check_yx('y', tblk, dm)))
		return (1);
	return (0);
}

int		check_part_walls(char dir, t_block tblk, t_doom *dm)
{
	if (tblk.pt < 3 || tblk.pt > 6)
		return (0);
	if (tblk.pt == 3 && dir == 'y')
	{
		if (dm->pos.y + dm->gravity.y > (int)(dm->pos.y + dm->gravity.y)
			+ tblk.pln / 15.0)
			return (1);
	}
	else if (tblk.pt == 4 && dir == 'y')
	{
		if (dm->pos.y + dm->gravity.y < (int)(dm->pos.y + dm->gravity.y)
			+ (1 - tblk.pln / 15.0))
			return (1);
	}
	else if (tblk.pt == 5 && dir == 'x')
	{
		if (dm->pos.x + dm->gravity.x > (int)(dm->pos.x + dm->gravity.x)
			+ tblk.pln / 15.0)
			return (1);
	}
	if (check_part_walls2(dir, tblk, dm))
		return (1);
	return (0);
}

int		check_hor_coll2(t_block blk, t_doom *dm, double hgt, int plnd)
{
	hgt = ((int)dm->pos.z + (1 - blk.pln / 15.0) - dm->plrhight) - dm->pos.z;
	plnd = blk.pln;
	blk = dm->area[(int)(dm->pos.z - 0.15)][(int)(dm->pos.y)]
		[(int)(dm->pos.x)];
	plnd = abs(blk.pln - plnd);
	if (hgt < 0.4 && hgt > -0.4)
	{
		plnd = abs(blk.pln - plnd);
		if ((blk.b > 1 && blk.pt == 0) || (blk.pt == 1 && plnd > 11))
			return (0);
		if (!dm->airbrn)
			dm->pos.z += hgt;
		return (1);
	}
	else if (hgt >= 0 && hgt < 0.4)
	{
		if (!dm->airbrn)
			dm->pos.z += hgt;
		return (1);
	}
	return (0);
}

int		check_hor_coll(t_block blk, t_doom *dm, char dir)
{
	if (blk.b <= 1 || (blk.pt == 1 && blk.pln < 6))
		return (1);
	else if (!blk.pt)
		return (0);
	else if (blk.pt == 2)
		return (check_hor_coll2(blk, dm, 0, 0));
	else if (blk.pt < 7)
		return (check_part_walls(dir, blk, dm));
	else
		return (slope_coll(blk, dm, dir));
	return (0);
}

void	move_fb(t_doom *dm)
{
	double	mov;

	mov = dm->movsp * ((30.0 / dm->buffer) / dm->prefps);
	if (mov > 1.0 || mov < -1.0)
		mov /= fabs(mov) * 2;
	if (dm->key.w)
	{
		dm->gravity.x = dm->dir.x * mov;
		dm->gravity.y = dm->dir.y * mov;
	}
	if (dm->key.s)
	{
		dm->gravity.x = -dm->dir.x * mov;
		dm->gravity.y = -dm->dir.y * mov;
	}
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y +
		dm->gravity.y)][(int)dm->pos.x], dm, 'y'))
		dm->pos.y += dm->gravity.y;
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y]
		[(int)(dm->pos.x + dm->gravity.x)], dm, 'x'))
		dm->pos.x += dm->gravity.x;
	check_sprite_dist(dm, mov, -1);
	dm->airbrn = 1;
}
