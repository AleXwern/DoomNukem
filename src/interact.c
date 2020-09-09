/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 14:03:32 by AleXwern          #+#    #+#             */
/*   Updated: 2020/09/09 14:31:36 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>//remove when done

int		get_warpdest(t_doom* dm, t_vector pos, t_vector warp)
{
	t_vector	relative;

	relative.x = round(pos.x - warp.x);
	relative.y = round(pos.y - warp.y);
	if (relative.y != 0 && relative.x != 0)
		return (0);
	warp.x = dm->pos.x + (-relative.x * 2.0);
	warp.y = dm->pos.y + (-relative.y * 2.0);
	warp.z = dm->pos.z;
	if (dm->area[(int)warp.z][(int)warp.y][(int)warp.x].b == 1)
	{
		curt_down(dm);
		dm->pos = warp;
		curt_up(dm);
	}
	return (1);
}

int		get_stairdest(t_doom* dm, int obj, t_vector pos, t_vector stair)
{
	t_vector	relative;

	relative.x = round(pos.x - stair.x);
	relative.y = round(pos.y - stair.y);
	if (relative.y != 0 && relative.x != 0)
		return (0);
	stair.x = dm->pos.x + (-relative.x * 2.0);
	stair.y = dm->pos.y + (-relative.y * 2.0);
	stair.z = dm->pos.z + obj;
	if (dm->area[(int)stair.z][(int)stair.y][(int)stair.x].b == 1)
	{
		Mix_PlayChannel(-1, dm->teleport, 0);
		curt_down(dm);
		dm->pos = stair;
		curt_up(dm);
	}
	return (1);
}

void	lab_move(t_doom *dm, int obj, t_vector stair)
{
	if (!get_stairdest(dm, (obj - 3.5) * 2, dm->pos, stair))
		return;
	if ((int)dm->pos.z == dm->mxflr - 1 && (int)dm->pos.z == 0)
		error_out(LAB_OUT, dm);
}

int		interact(t_doom *dm)
{
	t_vector	tarpos;
	int			obj;

	tarpos.x = dm->pos.x + dm->dir.x * 0.9;
	tarpos.y = dm->pos.y + dm->dir.y * 0.9;
	obj = dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x].b;
	if (dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x].meta == 1)
		error_out(VOID_OVER, dm);
	else if (dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x].meta == 2)
		dm->hp = 100;
	if (obj == 3 || obj == 4)
		lab_move(dm, obj, tarpos);
	else if (obj == 5 && dm->keycard)
	{
		Mix_PlayChannel(-1, dm->doorsound, 0);
		dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x].b = 0;
	}
	else if (obj == 5 && !dm->keycard)
		Mix_PlayChannel(-1, dm->doorknob, 0);
	else if (obj == 0)
	{
		Mix_PlayChannel(-1, dm->doorsound, 0);
		dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x].b = 5;
	}
	else if (obj == 6)
	{
		Mix_PlayChannel(-1, dm->teleport, 0);
		get_warpdest(dm, dm->pos, tarpos);
	}
	if (obj == 5 || obj == 0)
		dm->cycle(dm);
	return (0);
}
