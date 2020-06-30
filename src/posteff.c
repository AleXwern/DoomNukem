/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posteff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:26:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/30 16:37:17 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	post_effects(t_doom *wlf)
{
	while (++wlf->y < wlf->winh)
	{
		wlf->x = -1;
		while (++wlf->x < wlf->winw)
		{
			if (tex_check(wlf) && wlf->isoutline)
				wlf->img.data[wlf->winw * wlf->y + wlf->x] = 0xff000000;
			//if (wlf->shift)
			//	wlf->img.data[wlf->winw * wlf->y + wlf->x] = color_shift(wlf->img.data[wlf->winw * wlf->y + wlf->x], 
			//			wlf->wallarr[wlf->winw * wlf->y + wlf->x] + fabs((double)(wlf->x - wlf->winw / 2) / wlf->winw), 
			//			wlf, 0);
		}
	}
}