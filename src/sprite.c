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
	if (dm->spr[5].dist < 1.1)//keycard
	{
		dm->keycard = 1;
		ft_bzero(&dm->spr[5], sizeof(t_sprite));
	}
	else if (dm->spr[6].dist < 1.1)//pistol
	{
		dm->gun = 1;
		ft_bzero(&dm->spr[6], sizeof(t_sprite));
	}
	else if (dm->spr[7].dist < 2.5 && !dm->chestopened)//chest
	{
		printf("Chest opened\n");
		dm->chestopened = 1;
	}
}
