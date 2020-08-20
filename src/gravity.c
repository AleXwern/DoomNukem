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

#include "../includes/doom.h"
#include "../includes/value.h"

void	gravity(t_doom* dm)
{
	if (dm->key.two || dm->isgravity || dm->ismenu)
		return;
	if (dm->gravity.z >= 1.0 || dm->gravity.z <= -1.0)
		dm->gravity.z /= fabs(dm->gravity.z);
	//dm->gravity.z += dm->fallsp.z;
	if (dm->gravity.z < 0)
	{
		if (dm->area[(int)(dm->pos.z + dm->gravity.z - 0.1)][(int)(dm->pos.y)][(int)dm->pos.x].b <= 1)
			dm->pos.z += dm->gravity.z;
	}
	else if (dm->area[(int)(dm->pos.z + 1)][(int)(dm->pos.y)][(int)dm->pos.x].b <= 1)
		dm->pos.z += dm->gravity.z;
	else
	{
		dm->airbrn = 0;
		dm->gravity.z = 0;
		dm->pos.z = floor(dm->pos.z) + 0.5;
	}
	dm->gravity.z += dm->fallsp.z;
	if (dm->gravity.z > 0.2 * (30.0 / dm->buffer / dm->prefps))
		dm->gravity.z = 0.2 * (30.0 / dm->buffer / dm->prefps);
	if (dm->area[(int)(dm->pos.z + 0.5)][(int)(dm->pos.y)][(int)dm->pos.x].b > 1)
		dm->pos.z -= 0.1;
}