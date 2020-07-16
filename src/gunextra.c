/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gunextra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:34:23 by tbergkul          #+#    #+#             */
/*   Updated: 2020/07/16 16:56:44 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_ammo(t_doom *wlf)
{
	//SDL_RenderCopy(wlf->rend, wlf->nbrsTexture, &wlf->nbrsRect, &wlf->screennbrsRect);
}

void	draw_crosshair(t_doom *wlf)
{
	SDL_RenderCopy(wlf->rend, wlf->CHTexture, &wlf->CHRect, &wlf->screenCHRect);
}

void	reloading_gun(t_doom *wlf)
{
	wlf->frm++;
	if (wlf->ani == 2 && wlf->frm == 1)
		Mix_PlayChannel(-1, wlf->reload, 0);
	if ((wlf->frm / 3) > 2)
	{
		if (wlf->ani < 5)
			wlf->ani++;
		else
		{
			wlf->ani = 0;
			wlf->reloading = 0;
			wlf->magazine = 10;
		}
		wlf->frm = 0;
	}
}
