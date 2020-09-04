/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:02:20 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/06 19:02:20 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

double	get_coll_down(t_block blk)
{
	if (blk.pt <= 1)
		return (0);
	else if (blk.pt == 2)
		return (1 - blk.pln / 15.0);
	return (0);
}

int		check_ver_coll(t_block blk, t_doom *dm)
{
	double	hgt;

	if (blk.b <= 1)
		return (1);
	else if (blk.pt == 2)
	{
		hgt = (int)(dm->pos.z + 0.6) + (1 - blk.pln / 15.0) - 0.598;
		if (hgt > dm->pos.z + dm->gravity.z)
			return (1);
		return (0);
	}
	return (0);
}

void	gravity(t_doom* dm)
{
	/*if (!dm->airbrn)
	{
		if (dm->pos.z - (int)dm->pos.z > 0.4)
			dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)(dm->pos.z + 0.6)][(int)(dm->pos.y)][(int)dm->pos.x]) + 0.4;
		else
			dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)(dm->pos.z)][(int)(dm->pos.y)][(int)dm->pos.x]) - 0.6;
	}*/
	if (dm->key.two || dm->isgravity || dm->ismenu || !dm->airbrn)
		return;
	if (dm->gravity.z >= 1.0 || dm->gravity.z <= -1.0)
		dm->gravity.z /= fabs(dm->gravity.z);
	if (dm->gravity.z < 0)
	{
		if (dm->area[(int)(dm->pos.z + dm->gravity.z - 0.1)][(int)(dm->pos.y)][(int)dm->pos.x].b <= 1 ||
			dm->area[(int)(dm->pos.z + dm->gravity.z - 0.1)][(int)(dm->pos.y)][(int)dm->pos.x].pt == 2)
			dm->pos.z += dm->gravity.z;
	}
	else if (check_ver_coll(dm->area[(int)(dm->pos.z + 0.6)][(int)(dm->pos.y)][(int)dm->pos.x], dm))
		dm->pos.z += dm->gravity.z;
	else
	{
		dm->airbrn = 0;
		dm->gravity.z = 0;
		if (dm->pos.z - (int)dm->pos.z > 0.4 && dm->area[(int)(dm->pos.z + 0.6)][(int)(dm->pos.y)][(int)dm->pos.x].pt == 2)
			dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)(dm->pos.z + 0.6)][(int)(dm->pos.y)][(int)dm->pos.x]) + 0.4;
		else if (dm->area[(int)(dm->pos.z)][(int)(dm->pos.y)][(int)dm->pos.x].pt == 2)
			dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)(dm->pos.z)][(int)(dm->pos.y)][(int)dm->pos.x]) - 0.6;
		else
			dm->pos.z = (int)dm->pos.z + 0.4;
		
	}
	dm->gravity.z += dm->fallsp.z;
	if (dm->gravity.z > 0.2 * (30.0 / dm->buffer / dm->prefps))
		dm->gravity.z = 0.2 * (30.0 / dm->buffer / dm->prefps);
}
