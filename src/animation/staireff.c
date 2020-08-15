/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staireff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:40:00 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/14 15:07:24 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	dummy_render(t_doom *dm)
{
	static int	x;

	if (dm->trx < 1)
		dm->trx = 1;
	while (x < dm->trx)
	{
		dm->data_r[x] = *dm;
		dm->data_r[x].x = x;
		dm->threads[x] = SDL_CreateThread(renthread, "Thread", (void*)&dm->data_r[x]);
		x++;
	}
	while (x > 0)
	{
		x--;
		if (dm->threads[x] == NULL)
			ft_putendl("Thread failure.");
		else
			SDL_WaitThread(dm->threads[x], NULL);
	}
	dm->fps++;
}

void	curt_down(t_doom *dm)
{
	int		y;
	int		ry;

	y = 0;
	while (y < dm->winh)
	{
		dummy_render(dm);
		ry = -1;
		while (++ry < dm->winh)
		{
			if (ry < y)
				ft_bzero(dm->img.data + (dm->winw * ry), sizeof(Uint32) * dm->winw);
			else
				ft_memcpy(dm->img.data + (dm->winw * ry), dm->img.data + (dm->winw * ry), sizeof(Uint32) * dm->winw);
		}
		y += 30;
		SDL_RenderPresent(dm->rend);
	}
}

void	curt_up(t_doom *dm)
{
	int		y;
	int		ry;

	y = dm->winh - 1;
	while (y >= 0)
	{
		dummy_render(dm);
		ry = -1;
		while (++ry < dm->winh)
		{
			if (ry < y)
				ft_bzero(dm->img.data + (dm->winw * ry), sizeof(Uint32) * dm->winw - 1);
			else
				ft_memcpy(dm->img.data + (dm->winw * ry), dm->img.data + (dm->winw * ry), sizeof(Uint32) * dm->winw - 1);
		}
		y -= 30;
		SDL_RenderPresent(dm->rend);
	}
}