/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posteff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:26:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/07 13:18:40 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

int		tex_check(t_doom *dm)
{
	double	wdistdiff;

	if (dm->x > 0)
	{
		if (dm->maparr[dm->winw * dm->y + dm->x - 1] !=
			dm->maparr[dm->winw * dm->y + dm->x])
			return (1);
		wdistdiff = fabs(dm->wallarr[dm->winw * dm->y + dm->x - 1] -
			dm->wallarr[dm->winw * dm->y + dm->x]);
		if (wdistdiff > 0.8)
			return (1);
	}
	if (dm->y > 0)
	{
		if (dm->maparr[dm->winw * (dm->y - 1) + dm->x] !=
			dm->maparr[dm->winw * dm->y + dm->x])
			return (1);
		wdistdiff = fabs(dm->wallarr[dm->winw * (dm->y - 1) + dm->x] -
			dm->wallarr[dm->winw * dm->y + dm->x]);
		if (wdistdiff > 0.8)
			return (1);
	}
	return (0);
}

void	post_effects(t_doom *dm)
{
	dm->y = -1;
	while (++dm->y < dm->winh)
	{
		dm->x = -1;
		while (++dm->x < dm->winw)
			if (tex_check(dm) && dm->isoutline)
				dm->img.data[dm->winw * dm->y + dm->x] = 0xff000000;
	}
}
