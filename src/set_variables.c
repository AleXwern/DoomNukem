/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:28:48 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/19 15:45:00 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	set_variables(t_doom *dm)
{
	dm->chestopened = 0;
	dm->drawgunandkeycard = 0;
	dm->gun = 1;
	dm->shooting = 0;
	dm->reloading = 0;
	dm->ani = 0;
	dm->frm = 0;
	dm->keycard = 1;
	dm->slidedoor = 'x';
	dm->doorani = 0;
	dm->doorfrm = 0;
	dm->uncrouch = 0;
	dm->plrhight = 0.6;
	dm->money = 0;
	dm->gamestarted = 0;
	dm->gamewon = 0;
	dm->victoryplayed = 0;
	dm->moneytext = NULL;
}

void	dev_status(t_doom *dm, char *av)
{
	if (ft_strncmp("-debug", av, 6))
		return ;
	dm->dev = 1;
	dm->invincible = 4;
	dm->isgravity = 1;
}
