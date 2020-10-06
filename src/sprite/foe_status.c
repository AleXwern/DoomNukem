/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:06:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/06 14:36:19 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	's' -shooting
**	'x' -stand still
**	'a' -alerted
**	'm' -moving/passive
*/

int		foe_ismoving(t_sprite *spr)
{
	if (spr->dist >= 8)
		spr->move = 'm';
	if (spr->move != 'a' && spr->move != 's')
	{
		if (spr->mov.z != 0 || spr->mov.y != 0 || spr->mov.x != 0)
			spr->move = 'm';
		else
			spr->move = 'x';
	}
	if (spr->move == 'x')
		return (0);
	return (1);
}
