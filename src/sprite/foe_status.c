/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:06:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/01 14:08:15 by anystrom         ###   ########.fr       */
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
	if (spr->move != 'a' && spr->move != 's')
	{
		if (spr->mov.z != 0 && spr->mov.y != 0 && spr->mov.x != 0)
			spr->move = 'm';
		else
			spr->move = 'x';
	}
	if (spr->move = 'x')
		return (0);
	return (1);
}