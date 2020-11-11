/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:24:42 by tbergkul          #+#    #+#             */
/*   Updated: 2020/11/11 15:59:01 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		check_sprite_dist(t_doom *dm, double mov, int i)
{
	t_vector	npos;

	npos = dm->pos;
	while (++i < 9)
	{
		if (!dm->spr[i].gfx)
			dm->spr[i].dist = 0;
		if (dm->spr[i].dist < 0.9 && fabs(dm->pos.z - dm->spr[i].pos.z) < 1)
		{
			npos.x -= dm->spr[i].dir.x * mov;
			npos.y -= dm->spr[i].dir.y * mov;
			if (check_hor_coll(dm->area[(int)npos.z][(int)(npos.y)]
				[(int)npos.x], dm, 'x'))
				dm->pos.x = npos.x;
			if (check_hor_coll(dm->area[(int)npos.z][(int)(npos.y)]
				[(int)npos.x], dm, 'y'))
				dm->pos.y = npos.y;
		}
	}
	return (1);
}

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

void	strafe2(t_doom *dm, double mov)
{
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y +
		dm->gravity.y)][(int)dm->pos.x], dm, 'y'))
		dm->pos.y += dm->gravity.y;
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y]
		[(int)(dm->pos.x + dm->gravity.x)], dm, 'x'))
		dm->pos.x += dm->gravity.x;
	check_sprite_dist(dm, mov, 3);
	dm->airbrn = 1;
}

void	strafe(t_doom *dm)
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
	strafe2(dm, mov);
}
