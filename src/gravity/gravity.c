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

int		collision_check(t_block area, t_vector gravity, t_vector pos)
{
	pos.z = pos.z + gravity.z - 0.1;
	printf("Gravity\npos %f %f %f\nblock %hhu %hhu %f\n", pos.z, pos.y, pos.x, area.b, area.pt, area.pln / 15.0);
	if (area.b <= 1)
		return (1);
	else if (!area.pt)
		return (0);
	//else if (area.pt == 1 && area.b > 1 && (pos.z - floor(pos.z)) < (area.pln / 15.0))
	//	return (0);
	return (0);
}

void	gravity(t_doom* dm)
{
	if (dm->key.two || dm->isgravity || dm->ismenu || !dm->airbrn)
		return;
	if (dm->gravity.z >= 1.0 || dm->gravity.z <= -1.0)
		dm->gravity.z /= fabs(dm->gravity.z);
	//dm->gravity.z += dm->fallsp.z;
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
	}
	dm->gravity.z += dm->fallsp.z;
	if (dm->gravity.z > 0.2 * (30.0 / dm->buffer / dm->prefps))
		dm->gravity.z = 0.2 * (30.0 / dm->buffer / dm->prefps);
	//if (dm->area[(int)(dm->pos.z + 0.5)][(int)(dm->pos.y)][(int)dm->pos.x].b > 1)
	//	dm->pos.z -= 0.1;
}
