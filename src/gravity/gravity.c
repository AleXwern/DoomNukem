/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:18:33 by anystrom          #+#    #+#             */
/*   Updated: 2021/01/04 15:26:26 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		check_ver_slp(t_block blk, t_doom *dm, double hgt)
{
	if (blk.pt == 11)
		hgt = (int)(dm->pos.z + dm->plrhight + 0.02) +
			((dm->pos.y - (int)dm->pos.y)) - dm->plrhight;
	else if (blk.pt == 12)
		hgt = (int)(dm->pos.z + dm->plrhight + 0.02) +
			(1 - (dm->pos.y - (int)dm->pos.y)) - dm->plrhight;
	else if (blk.pt == 13)
		hgt = (int)(dm->pos.z + dm->plrhight + 0.02) +
			((dm->pos.x - (int)dm->pos.x)) - dm->plrhight;
	else
		hgt = (int)(dm->pos.z + dm->plrhight + 0.02) +
			(1 - (dm->pos.x - (int)dm->pos.x)) - dm->plrhight;
	if (hgt > dm->pos.z + dm->gravity.z)
		return (1);
	return (0);
}

int		check_ver_coll(t_block blk, t_doom *dm)
{
	double	hgt;

	if (blk.b <= 1)
		return (1);
	else if (blk.pt == 2)
	{
		hgt = (int)(dm->pos.z + dm->plrhight + 0.02) +
			(1 - blk.pln / 15.0) - dm->plrhight;
		if (hgt > dm->pos.z + dm->gravity.z)
			return (1);
		return (0);
	}
	else if (blk.pt >= 11 && blk.pt < 15)
		return (check_ver_slp(blk, dm, 0));
	else
		return (ver_move(blk, dm));
}

int		check_ver_ucoll(t_block blk, t_doom *dm)
{
	double	hgt;

	if (blk.b <= 1)
		return (1);
	else if (blk.pt == 1)
	{
		hgt = (int)(dm->pos.z + dm->gravity.z) + blk.pln / 15.0;
		if (hgt < dm->pos.z + dm->gravity.z)
			return (1);
		return (0);
	}
	else if (blk.pt == 2)
	{
		hgt = (int)(dm->pos.z + dm->gravity.z) + (1 - blk.pln / 15.0);
		if (hgt > dm->pos.z)
			return (1);
		return (0);
	}
	else
		return (ver_move(blk, dm));
}

void	gravity2(t_doom *dm)
{
	dm->airbrn = 0;
	dm->gravity.z = 0;
	if (dm->pos.z - (int)dm->pos.z > (1 - dm->plrhight) &&
			dm->area[(int)(dm->pos.z + dm->plrhight)][(int)(dm->pos.y)]
			[(int)dm->pos.x].pt == 2)
		dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)
			(dm->pos.z + dm->plrhight)][(int)(dm->pos.y)]
			[(int)dm->pos.x], dm->pos) + (1 - dm->plrhight);
	else if (dm->area[(int)(dm->pos.z)][(int)(dm->pos.y)]
			[(int)dm->pos.x].pt == 2)
		dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)
			(dm->pos.z)][(int)(dm->pos.y)][(int)dm->pos.x],
			dm->pos) - dm->plrhight;
}

void	gravity(t_doom *dm)
{
	if (dm->key.two || dm->isgravity || dm->ismenu)
		return ;
	if (dm->gravity.z >= 1.0 || dm->gravity.z <= -1.0)
		dm->gravity.z /= fabs(dm->gravity.z);
	if (dm->pos.z + dm->gravity.z < 0)
		error_out(VOID_OVER, dm);
	if (!gravity_slope(dm))
		return ;
	if (dm->gravity.z < 0)
	{
		if (check_ver_ucoll(dm->area[(int)(dm->pos.z + dm->gravity.z)]
				[(int)(dm->pos.y)][(int)dm->pos.x], dm))
			dm->pos.z += dm->gravity.z;
	}
	else if (check_ver_coll(dm->area[(int)(dm->pos.z + dm->plrhight +
		dm->gravity.z)][(int)(dm->pos.y)][(int)dm->pos.x], dm))
		dm->pos.z += dm->gravity.z;
	else
		gravity2(dm);
	dm->gravity.z += dm->fallsp.z;
	if (dm->gravity.z > 0.17 * (30.0 / dm->buffer / dm->prefps))
		dm->gravity.z = 0.17 * (30.0 / dm->buffer / dm->prefps);
}
