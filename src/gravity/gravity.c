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

int		collision_down(t_doom *dm, t_vector gravity, t_vector pos)
{
	if (dm->area[(int)pos.z][(int)pos.y][(int)pos.x].b > 1 &&
		!dm->area[(int)pos.z][(int)pos.y][(int)pos.x].pt)
		return (0);
	if (dm->area[(int)pos.z][(int)pos.y][(int)pos.x].b < 2)
		return (1);
	return (0);
}

void	gravity(t_doom* dm)
{
	if (!dm->airbrn)
	{
		if (dm->pos.z - (int)dm->pos.z > 0.4)
			dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)(dm->pos.z + 0.6)][(int)(dm->pos.y)][(int)dm->pos.x]) + 0.4;
		else
			dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)(dm->pos.z)][(int)(dm->pos.y)][(int)dm->pos.x]) - 0.6;
	}
	if (dm->key.two || dm->isgravity || dm->ismenu || !dm->airbrn)
		return;
	if (dm->gravity.z >= 1.0 || dm->gravity.z <= -1.0)
		dm->gravity.z /= fabs(dm->gravity.z);
	if (dm->gravity.z < 0)
	{
		if (dm->area[(int)(dm->pos.z + dm->gravity.z - 0.1)][(int)(dm->pos.y)][(int)dm->pos.x].b <= 1)
			dm->pos.z += dm->gravity.z;
	}
	else if (dm->area[(int)(dm->pos.z + 0.6)][(int)(dm->pos.y)][(int)dm->pos.x].b <= 1)
		dm->pos.z += dm->gravity.z;
	else
	{
		dm->airbrn = 0;
		dm->gravity.z = 0;
		if (dm->pos.z - (int)dm->pos.z > 0.4)
			dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)(dm->pos.z + 0.6)][(int)(dm->pos.y)][(int)dm->pos.x]) + 0.4;
		else
			dm->pos.z = (int)dm->pos.z + get_coll_down(dm->area[(int)(dm->pos.z)][(int)(dm->pos.y)][(int)dm->pos.x]);// - 0.6;
	}
	dm->gravity.z += dm->fallsp.z;
	if (dm->gravity.z > 0.2 * (30.0 / dm->buffer / dm->prefps))
		dm->gravity.z = 0.2 * (30.0 / dm->buffer / dm->prefps);
	//if (dm->area[(int)(dm->pos.z + 0.5)][(int)(dm->pos.y)][(int)dm->pos.x].b > 1)
	//	dm->pos.z -= 0.1;
}
