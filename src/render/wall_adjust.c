/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_adjust.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:55:22 by anystrom          #+#    #+#             */
/*   Updated: 2021/01/04 14:57:27 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		xy_wall_ppos(t_doom *dm, t_block blk, int bbool)
{
	double	dir;

	dir = atan2(dm->rayd.y, dm->rayd.x) / M_PI * 180 + 180;
	if (blk.pt == 15 && dir > 135 && dir < 315)
		bbool = 1;
	else if (blk.pt == 16 && dir > 45 && dir < 225)
		bbool = 1;
	else if (blk.pt == 17 && (dir < 135 || dir > 315))
		bbool = 1;
	else if (blk.pt == 18 && (dir < 45 || dir > 225))
		bbool = 1;
	if (!bbool)
	{
		dm->adj = 1;
		dm->map.x -= dm->stepx;
		dm->map.y -= dm->stepy;
		dm->sided.y -= dm->deltad.y;
		dm->sided.x -= dm->deltad.x;
	}
	single_loop_x(dm);
	dm->map = dm->tmap;
	dm->sided = dm->tsided;
}
