/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 14:03:32 by AleXwern          #+#    #+#             */
/*   Updated: 2020/07/07 14:10:12 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

void	lab_move(t_doom *wlf, int obj)
{
	if (obj == 3 && wlf->map[(int)wlf->posz -
			1][(int)wlf->posy][(int)wlf->posx] == 1)
	{
		printf("stairs\n");
		wlf->posz -= 1;
		wlf->posy += wlf->dir.y * 0.5;
		wlf->posx += wlf->dir.x * 0.5;
	}
	else if (obj == 4 && (int)wlf->posz > 0 && wlf->map[(int)wlf->posz -
			1][(int)wlf->posy][(int)wlf->posx] == 1)
		wlf->posz += 0.5;
	else if ((obj == 3 && (int)wlf->posz == wlf->mxflr) ||
			(obj == 4 && wlf->flr == 0))
		error_out(LAB_OUT, wlf);
	wlf->dir.x *= -1.0;
	wlf->dir.y *= -1.0;
	wlf->plane.x *= -1.0;
	wlf->plane.y *= -1.0;
	//wlf->cycle(wlf);
	//mlx_put_image_to_window(wlf->mlx, wlf->win, wlf->gfx[obj + 4].img, 0, 0);
}

int		interact(t_doom *wlf)
{
	t_vector	tarpos;
	int			obj;

	tarpos.x = wlf->posx + wlf->dir.x * 0.9;
	tarpos.y = wlf->posy + wlf->dir.y * 0.9;
	obj = wlf->map[(int)wlf->posz][(int)tarpos.y][(int)tarpos.x];
	if (obj == 3 || obj == 4)
		lab_move(wlf, obj);
	else if (obj == 5)
		wlf->map[(int)wlf->posz][(int)tarpos.y][(int)tarpos.x] = 0;
	else if (obj == 0)
		wlf->map[(int)wlf->posz][(int)tarpos.y][(int)tarpos.x] = 5;
	if (obj == 5 || obj == 0)
		wlf->cycle(wlf);
	return (0);
}
