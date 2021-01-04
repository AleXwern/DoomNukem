/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:02:22 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/04 15:02:22 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		get_blockstack(t_doom *dm, t_block blk, char dir)
{
	int	pln;

	if (blk.pt != 2)
		pln = 15;
	else
		pln = blk.pln;
	if (dir == 'y' && dm->truez >= 1)
		blk = dm->area[(int)dm->truez - 1][(int)(dm->pos.y +
			dm->gravity.y)][(int)dm->pos.x];
	else if (dm->truez >= 1)
		blk = dm->area[(int)dm->truez - 1][(int)dm->pos.y][(int)(dm->pos.x +
			dm->gravity.x)];
	if (blk.b > 1 && pln > 10)
		pln = 15 + blk.pln;
	return (pln);
}

int		gravity_slope(t_doom *dm)
{
	t_block	blk;

	blk = dm->area[(int)(dm->truez + 1)][(int)(dm->pos.y)][(int)dm->pos.x];
	if ((blk.pt >= 11 && blk.pt <= 14) && !(dm->blk.pt >= 11 &&
		dm->blk.pt <= 14) && dm->blk.b != 2)
	{
		if (dm->blk.pt != 2)
			dm->pos.z += 0.1;
		return (0);
	}
	if (dm->blk.pt >= 11 && dm->blk.pt <= 14)
		return (0);
	return (1);
}

int		ver_movetwo(t_block blk, t_doom *dm)
{
	t_vector	npos;

	npos.y = dm->pos.y - (int)dm->pos.y;
	npos.x = dm->pos.x - (int)dm->pos.x;
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

int		ver_move(t_block blk, t_doom *dm)
{
	if (blk.pt >= 15)
		return (ver_movetwo(blk, dm));
	else if (blk.pt == 3)
	{
		if (dm->pos.y - (int)dm->pos.y > blk.pln / 15.0)
			return (1);
	}
	else if (blk.pt == 4)
	{
		if (dm->pos.y - (int)dm->pos.y < (1 - blk.pln / 15.0))
			return (1);
	}
	else if (blk.pt == 5)
	{
		if (dm->pos.x - (int)dm->pos.x > blk.pln / 15.0)
			return (1);
	}
	else if (blk.pt == 6)
	{
		if (dm->pos.x - (int)dm->pos.x < (1 - blk.pln / 15.0))
			return (1);
	}
	return (0);
}
