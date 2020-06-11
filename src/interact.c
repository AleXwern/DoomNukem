/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 14:03:32 by AleXwern          #+#    #+#             */
/*   Updated: 2020/06/11 17:03:12 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

void	lab_move(t_wolf *wlf, int obj)
{
	if (obj == 3 && wlf->map[(int)wlf->posz -
			1][(int)wlf->posy][(int)wlf->posx] == 1)
	{
		printf("stairs\n");
		wlf->posz -= 1;
		wlf->posy += wlf->diry * 0.5;
		wlf->posx += wlf->dirx * 0.5;
	}
	else if (obj == 4 && (int)wlf->posz > 0 && wlf->map[(int)wlf->posz -
			1][(int)wlf->posy][(int)wlf->posx] == 1)
		wlf->posz += 0.5;
	else if ((obj == 3 && (int)wlf->posz == wlf->mxflr) ||
			(obj == 4 && wlf->flr == 0))
		error_out(LAB_OUT, wlf);
	wlf->dirx *= -1.0;
	wlf->diry *= -1.0;
	wlf->planex *= -1.0;
	wlf->planey *= -1.0;
	wlf->cycle(wlf);
	mlx_put_image_to_window(wlf->mlx, wlf->win, wlf->gfx[obj + 4].img, 0, 0);
}

int		interact(t_wolf *wlf)
{
	double	tarposx;
	double	tarposy;
	int		obj;

	tarposx = wlf->posx + wlf->dirx * 0.9;
	tarposy = wlf->posy + wlf->diry * 0.9;
	obj = wlf->map[(int)wlf->posz][(int)tarposy][(int)tarposx];
	if (obj == 3 || obj == 4)
		lab_move(wlf, obj);
	else if (obj == 5)
		wlf->map[(int)wlf->posz][(int)tarposy][(int)tarposx] = 0;
	else if (obj == 0)
		wlf->map[(int)wlf->posz][(int)tarposy][(int)tarposx] = 5;
	if (obj == 5 || obj == 0)
		wlf->cycle(wlf);
	return (0);
}
