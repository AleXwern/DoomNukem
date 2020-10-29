/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:51:22 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/28 15:37:53 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	plr_dir(t_doom *dm, t_sprite *spr, double spra)
{
	dm->gfx[spr->gfx].x = (spr->frame / 8) * 28;
	spra = (atan2(spr->dir.y, spr->dir.x) - atan2(spr->face.y, spr->face.x))
		* 180 / M_PI;
	if (spra >= 180)
		spra -= 360;
	else if (spra <= -180)
		spra += 360;
	if (spra < 45 && spra > -45)
		dm->gfx[spr->gfx].y = BACKS;
	else if (spra > 135 || spra < -135)
		dm->gfx[spr->gfx].y = FRONTS;
	else if (spra >= 45)
		dm->gfx[spr->gfx].y = LEFTS;
	else
		dm->gfx[spr->gfx].y = RIGHTS;
}

void	plr_status(t_doom *dm, t_sprite *spr, int *yx, int i)
{
	double	dist;

	spr->frame++;
	if (spr->frame >= 32)
		spr->frame = 0;
	plr_dir(dm, &dm->spr[i], 0);
	dist = spr->dist;
	//if (yx[1] >= 0 && yx[1] < dm->winw)
	//dist *= 1.0 - ((fabs(dm->winw / 2.0 - yx[1]) / (dm->winw / 2)) / 4);
	//if (i < 2)
	//	printf("%d dist %f mod %f\n", i, dist, (1.0 - ((fabs(dm->winw / 2.0 - yx[1]) / (dm->winw / 2)) / 4)));
	draw_sprite_gfx(dm, dm->gfx[spr->gfx],
		(int[7]){yx[0], yx[1], 37, 28, 0, 0, i}, SPRSIZE / spr->dist);
}
