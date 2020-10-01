/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe_ai.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:50:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/01 14:16:04 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	's' -shooting
**	'a' -alerted
**	Passive
**	'x' -stand still
**	'm' -moving/passive
*/

void	foe_dir(t_doom *dm, t_sprite *spr, double spra)
{
	if (spr->move == 'x')
		dm->gfx[spr->gfx].x = (spr->frame / 8) * 28;
	else
		dm->gfx[spr->gfx].x = (spr->frame < 16 ? 0 : 56);
	spra = atan2(spr->dir.y, spr->dir.x) * 180 / M_PI
		- atan2(spr->face.y, spr->face.x) * 180 / M_PI;
	//spra = spra - spra;
	if (spra >= 180)
		spra -= 360;
	else if (spra <= -180)
		spra += 360;
	if (spra < 45 && spra > -45)
		dm->gfx[spr->gfx].y = 111;
	else if (spra > 135 || spra < -135)
		dm->gfx[spr->gfx].y = 0;
	else if (spra >= 45)
		dm->gfx[spr->gfx].y = 74;
	else
		dm->gfx[spr->gfx].y = 37;
}

void	foe_ai(t_doom *dm, t_sprite *s)
{
	
}