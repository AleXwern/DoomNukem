/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 14:35:04 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/09 13:30:10 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		check_part_walls(t_block blk, t_block tblk, t_doom *dm, double mov)
{
	if (tblk.pt == 3)
	{
		if (dm->pos.y + dm->dir.y * mov > (int)(dm->pos.y + dm->dir.y * mov) + tblk.pln / 15.0)
			return (1);
	}
	if (tblk.pt == 4)
	{
		if (dm->pos.y + dm->dir.y * mov < (int)(dm->pos.y + dm->dir.y * mov) + (1 - tblk.pln / 15.0))
			return (1);
	}
	return (0);
}

int		check_hor_coll(t_block blk, t_doom *dm, double mov)
{
	double	hgt;

	if (blk.b <= 1 || (blk.pt == 1 && blk.pln < 6))
		return (1);
	else if (blk.pt == 2)
	{
		hgt = ((int)dm->pos.z + (1 - blk.pln / 15.0) - 0.6) - dm->pos.z;
		if (hgt < 0 && hgt > -0.4)
		{
			blk = dm->area[(int)(dm->pos.z + hgt - 0.15)][(int)(dm->pos.y)][(int)(dm->pos.x)];
			if (blk.b > 1 && blk.pt < 2)
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
	else
		return (check_part_walls(dm->area[(int)dm->pos.z][(int)(dm->pos.y)][(int)dm->pos.x], blk, dm, mov));
}

void	move_b(t_doom *dm, double mov)
{
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y - dm->dir.y * mov)][(int)dm->pos.x],
		dm, -mov))
		dm->pos.y -= dm->dir.y * mov;
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x - dm->dir.x * mov)],
		dm, -mov))
		dm->pos.x -= dm->dir.x * mov;
}

void	move_fb(t_doom *dm)
{
	double	mov;
	
	mov = dm->movsp * ((30.0 / dm->buffer) / dm->prefps);
	if (mov > 1.0 || mov < -1.0)
		mov /= fabs(mov) * 2;
	if (dm->key.up)
	{
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->dir.y * mov)][(int)dm->pos.x],
			dm, mov))
			dm->pos.y += dm->dir.y * mov;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->dir.x * mov)],
			dm, mov))
			dm->pos.x += dm->dir.x * mov;
	}
	if (dm->key.down)
		move_b(dm, mov);
	dm->airbrn = 1;
}

void	strafe(t_doom *dm, double dirxtemp, double dirytemp)
{
	double		mov;
	t_vector	dir;

	mov = dm->movsp * ((30.0 / dm->buffer) / dm->prefps);
	if (mov > 1.0)
		mov = 0.99;
	if (dm->key.left)
	{
		dir.x = dm->dir.y;
		dir.y = dm->dir.x * -1;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y + dir.y * mov)][(int)dm->pos.x],
			dm, mov))
			dm->pos.y += dir.y * mov;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dir.x * mov)],
			dm, mov))
			dm->pos.x += dir.x * mov;
	}
	if (dm->key.right)
	{
		dir.x = dm->dir.y * -1;
		dir.y = dm->dir.x;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y + dir.y * mov)][(int)dm->pos.x],
			dm, mov))
			dm->pos.y += dir.y * mov;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dir.x * mov)],
			dm, mov))
			dm->pos.x += dir.x * mov;
	}
	dm->airbrn = 1;
}