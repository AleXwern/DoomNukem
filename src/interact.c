/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 14:03:32 by AleXwern          #+#    #+#             */
/*   Updated: 2020/09/30 12:48:46 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

int		get_warpdest(t_doom *dm, t_vector pos, t_vector warp)
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

int		get_stairdest(t_doom *dm, int obj, t_vector pos, t_vector stair)
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

void	get_doortype(t_doom *dm, t_vector pos, t_vector door, t_block blk)
{
	t_vector	relative;

	if (blk.pt || blk.b != 5)
		return ;
	relative.x = round(pos.x - door.x);
	relative.y = round(pos.y - door.y);
	if (relative.y != 0 && relative.x != 0)
		return ;
	if (relative.y != 0)
		dm->area[(int)dm->pos.z][(int)door.y][(int)door.x].pt = 5;
	else
		dm->area[(int)dm->pos.z][(int)door.y][(int)door.x].pt = 3;
}

void	lab_move(t_doom *dm, int obj, t_vector stair)
{
	if (!get_stairdest(dm, (obj - 3.5) * 2, dm->pos, stair))
		return ;
	if ((int)dm->pos.z == dm->mxflr - 1 && (int)dm->pos.z == 0)
		error_out(LAB_OUT, dm);
}

void	slide_door(t_doom *dm)
{
	if (dm->slidedoor == 'o')
	{
		dm->slideblock->pln = dm->doorani;
		dm->doorfrm++;
		if (dm->doorfrm == 4)
		{
			dm->doorani--;
			dm->doorfrm = 0;
		}
		if (dm->doorani == 1)
			dm->slidedoor = 'x';
	}
	else if (dm->slidedoor == 'c')
	{
		dm->slideblock->pln = dm->doorani;
		dm->doorfrm++;
		if (dm->doorfrm == 4)
		{
			dm->doorani++;
			dm->doorfrm = 0;
		}
		if (dm->doorani == 16)
			dm->slidedoor = 'x';
	}
}

int		interact(t_doom *dm)
{
	t_vector	tarpos;
	t_block		*blk;

	tarpos.x = dm->pos.x + dm->dir.x * 0.9;
	tarpos.y = dm->pos.y + dm->dir.y * 0.9;
	if ((int)dm->pos.x == (int)tarpos.x &&
		(int)dm->pos.y == (int)tarpos.y)
		return (0);
	blk = &dm->area[(int)dm->pos.z][(int)tarpos.y][(int)tarpos.x];
	if (blk->meta == 8)
		error_out(VOID_OVER, dm);
	else if (blk->meta == 7)
		dm->hp = 5;
	get_doortype(dm, dm->pos, tarpos, *blk);
	if (blk->b == 3 || blk->b == 4)
		lab_move(dm, blk->b, tarpos);
	else if (blk->b == 5 && blk->pln == 15
		&& dm->keycard && dm->slidedoor == 'x')
	{
		dm->slidedoor = 'o';
		dm->slideblock = blk;
		dm->doorani = 15;
		blk->meta = 6;
		Mix_PlayChannel(-1, dm->doorsliding, 0);
	}
	else if (blk->b == 5 && !dm->keycard)
		Mix_PlayChannel(-1, dm->doorknob, 0);
	else if (blk->b == 5 && blk->pln <= 2
		&& dm->keycard && dm->slidedoor == 'x')
	{
		dm->slidedoor = 'c';
		dm->slideblock = blk;
		dm->doorani = 2;
		blk->meta = 5;
		Mix_PlayChannel(-1, dm->doorsliding, 0);
	}
	else if (blk->b == 6)
	{
		Mix_PlayChannel(-1, dm->teleport, 0);
		get_warpdest(dm, dm->pos, tarpos);
	}
	if (blk->b == 5 || blk->b == 0)
		dm->cycle(dm);
	return (0);
}
