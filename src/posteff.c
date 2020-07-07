/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posteff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:26:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/07 11:44:53 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

int		tex_check(t_doom *wlf)
{
	double	wdistdiff;
	
	if (wlf->x > 0)
	{
		if (wlf->maparr[wlf->winw * wlf->y + wlf->x - 1] != wlf->maparr[wlf->winw * wlf->y + wlf->x])
			return (1);
		wdistdiff = fabs(wlf->wallarr[wlf->winw * wlf->y + wlf->x - 1] - wlf->wallarr[wlf->winw * wlf->y + wlf->x]);
		if (wdistdiff > 0.8)
			return (1);
	}
	if (wlf->y > 0)
	{
		if (wlf->maparr[wlf->winw * (wlf->y - 1) + wlf->x] != wlf->maparr[wlf->winw * wlf->y + wlf->x])
			return (1);
		wdistdiff = fabs(wlf->wallarr[wlf->winw * (wlf->y - 1) + wlf->x] - wlf->wallarr[wlf->winw * wlf->y + wlf->x]);
		if (wdistdiff > 0.8)
			return (1);
	}
	return (0);
}

void	post_effects(t_doom *wlf)
{
	wlf->y = -1;
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