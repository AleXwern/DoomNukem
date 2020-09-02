/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:04:11 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/06 19:04:11 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	pickupitem(t_doom* dm)
{
	int			obj;

	obj = dm->area[(int)(dm->pos.z + 0.5)][(int)dm->pos.y][(int)dm->pos.x].b;
	if (obj == 8)//this will be used when we have sprites.
	{
		dm->keycard = 1;
	}
	else if (obj == 5)
	{
		dm->area[(int)(dm->pos.z + 0.5)][(int)dm->pos.y][(int)dm->pos.x].b = 0;
		dm->keycard = 1;
	}
}
