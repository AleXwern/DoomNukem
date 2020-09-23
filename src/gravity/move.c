/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 14:35:04 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/23 13:38:53 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		check_yx(char dir, t_block tblk, t_doom *dm)
{
	if (tblk.pt == 3 && dir == 'x')
	{
		if (dm->pos.y > (int)dm->pos.y + tblk.pln / 15.0)
			return (1);
	}
	else if (tblk.pt == 4 && dir == 'x')
	{
		if (dm->pos.y < (int)dm->pos.y + (1 - tblk.pln / 15.0))
			return (1);
	}
	else if (tblk.pt == 5 && dir == 'y')
	{
		if (dm->pos.x > (int)dm->pos.x + tblk.pln / 15.0)
			return (1);
	}
	else if (tblk.pt == 6 && dir == 'y')
	{
		if (dm->pos.x < (int)dm->pos.x + (1 - tblk.pln / 15.0))
			return (1);
	}
	return (0);
}

int		check_part_walls(char dir, t_block tblk, t_doom *dm, double mov)
{
	if (tblk.pt < 3 || tblk.pt > 6)
		return (0);
	if (tblk.pt == 3 && dir == 'y')
	{
		if (dm->pos.y + dm->gravity.y > (int)(dm->pos.y + dm->gravity.y) + tblk.pln / 15.0)
			return (1);
	}
	else if (tblk.pt == 4 && dir == 'y')
	{
		if (dm->pos.y + dm->gravity.y < (int)(dm->pos.y + dm->gravity.y) + (1 - tblk.pln / 15.0))
			return (1);
	}
	else if (tblk.pt == 5 && dir == 'x')
	{
		if (dm->pos.x + dm->gravity.x > (int)(dm->pos.x + dm->gravity.x) + tblk.pln / 15.0)
			return (1);
	}
	else if (tblk.pt == 6 && dir == 'x')
	{
		if (dm->pos.x + dm->gravity.x < (int)(dm->pos.x + dm->gravity.x) + (1 - tblk.pln / 15.0))
			return (1);
	}
	else if ((dir == 'x' && tblk.pt < 5 && check_yx('x', tblk, dm)) || 
			(dir == 'y' && tblk.pt > 4 && check_yx('y', tblk, dm)))
		return (1);
	return (0);
}

int		check_hor_coll(t_block blk, t_doom *dm, double mov, char dir)
{
	double	hgt;
	int		plnd;

	if (blk.b <= 1 || (blk.pt == 1 && blk.pln < 6))
		return (1);
	else if (!blk.pt)
		return (0);
	else if (blk.pt == 2)
	{
		hgt = ((int)dm->pos.z + (1 - blk.pln / 15.0) - 0.6) - dm->pos.z;
		plnd = blk.pln;
		//printf("blk %d %d %d\n", blk.b, blk.pt, blk.pln);
		blk = dm->area[(int)(dm->pos.z - 0.15)][(int)(dm->pos.y)][(int)(dm->pos.x)];
		plnd = abs(blk.pln - plnd);
		//printf("hgt %f blk %d %d %d - %d\n", hgt, blk.b, blk.pt, blk.pln, plnd);
		if (hgt < 0.4 && hgt > -0.4)
		{
			plnd = abs(blk.pln - plnd);
			//blk = dm->area[(int)(dm->pos.z + hgt - 0.15)][(int)(dm->pos.y)][(int)(dm->pos.x)];
			//printf("%d %d\n", (blk.b > 1 && blk.pt == 0), plnd < 11);
			if ((blk.b > 1 && blk.pt == 0) || (blk.pt == 1 && plnd < 11))
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
		return (check_part_walls(dir, blk, dm, mov));
}

int		check_sprite_dist(t_doom *dm, double mov, int i)
{
	t_vector	npos;

	npos = dm->pos;
	while (++i < 9)
	{
		if (dm->spr[i].dist < 1.2 && fabs(dm->pos.z - dm->spr[i].pos.z) < 1)
		{
			npos.x -= dm->spr[i].dir.x * mov;
			npos.y -= dm->spr[i].dir.y * mov;
			if (check_hor_coll(dm->area[(int)npos.z][(int)(npos.y)][(int)npos.x],
				dm, mov, 'x'))
				dm->pos.x = npos.x;
			if (check_hor_coll(dm->area[(int)npos.z][(int)(npos.y)][(int)npos.x],
				dm, mov, 'y'))
				dm->pos.y = npos.y;
		}
	}
	return (1);
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
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->gravity.y)][(int)dm->pos.x],
		dm, mov, 'y'))
		dm->pos.y += dm->gravity.y;
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->gravity.x)],
		dm, mov, 'x'))
		dm->pos.x += dm->gravity.x;
	check_sprite_dist(dm, mov, -1);
	dm->airbrn = 1;
}

void	strafe(t_doom *dm, double dirxtemp, double dirytemp)
{
	double		mov;
	t_vector	dir;

	mov = dm->movsp * ((30.0 / dm->buffer) / dm->prefps);
	if (mov > 1.0)
		mov = 0.99;
	if (dm->key.a)
	{
		dir.x = dm->dir.y;
		dir.y = dm->dir.x * -1;
		dm->gravity.x = dir.x * mov;
		dm->gravity.y = dir.y * mov;
	}
	if (dm->key.d)
	{
		dir.x = dm->dir.y * -1;
		dir.y = dm->dir.x;
		dm->gravity.x = dir.x * mov;
		dm->gravity.y = dir.y * mov;
	}
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y + dm->gravity.y)][(int)dm->pos.x],
		dm, mov, 'y'))
		dm->pos.y += dm->gravity.y;
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->gravity.x)],
		dm, mov, 'x'))
		dm->pos.x += dm->gravity.x;
	check_sprite_dist(dm, mov, -1);
	dm->airbrn = 1;
}
