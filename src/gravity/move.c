/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 14:35:04 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/03 16:32:36 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		check_hor_coll(t_block blk, t_doom *dm)
{
	double	hgt;

	if (blk.b <= 1)
		return (1);
	else if (blk.pt == 2)
	{
		hgt = (int)dm->pos.z + (1 - blk.pln / 15.0) - 0.6;
		if (fabs(hgt - dm->pos.z) < 0.4)
		{
			dm->pos.z += hgt - dm->pos.z;
			return (1);
		}
		return (0);
	}
	return (0);
}

void	move_b(t_doom *dm, double mov)
{
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y - dm->dir.y * mov)][(int)dm->pos.x],
		dm))
		dm->pos.y -= dm->dir.y * mov;
	if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x - dm->dir.x * mov)],
		dm))
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
			dm))
			dm->pos.y += dm->dir.y * mov;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dm->dir.x * mov)],
			dm))
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
			dm))
			dm->pos.y += dir.y * mov;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dir.x * mov)],
			dm))
			dm->pos.x += dir.x * mov;
	}
	if (dm->key.right)
	{
		dir.x = dm->dir.y * -1;
		dir.y = dm->dir.x;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)(dm->pos.y + dir.y * mov)][(int)dm->pos.x],
			dm))
			dm->pos.y += dir.y * mov;
		if (check_hor_coll(dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)(dm->pos.x + dir.x * mov)],
			dm))
			dm->pos.x += dir.x * mov;
	}
	dm->airbrn = 1;
}