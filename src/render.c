/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/08 15:17:24 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

void	dda_sys(t_wolf *wlf)
{
	wlf->hit = 0;
	while (wlf->hit == 0)
	{
		if (wlf->sidedx < wlf->sidedy && wlf->sidedx < wlf->sidedz)
		{
			wlf->sidedx += wlf->deltadx;
			wlf->mapx += wlf->stepx;
			wlf->side = 0;
		}
		else if (wlf->sidedy < wlf->sidedx && wlf->sidedy < wlf->sidedz)
		{
			wlf->sidedy += wlf->deltady;
			wlf->mapy += wlf->stepy;
			wlf->side = 1;
		}
		else
		{
			wlf->sidedz += wlf->deltadz;
			wlf->mapz += wlf->stepz;
			wlf->side = 2;
		}
		if (wlf->map[wlf->mapz][wlf->mapy][wlf->mapx] > 1)
			wlf->hit = 1;
	}
}

void	dda_prep(t_wolf *wlf)
{
	wlf->deltadx = fabs(1 / wlf->raydx);
	wlf->deltady = fabs(1 / wlf->raydy);
	wlf->deltadz = fabs(1 / wlf->raydz);
	if (wlf->raydx < 0)
	{
		wlf->stepx = -1;
		wlf->sidedx = (wlf->posx - wlf->mapx) * wlf->deltadx;
	}
	else
	{
		wlf->stepx = 1;
		wlf->sidedx = (wlf->mapx + 1.0 - wlf->posx) * wlf->deltadx;
	}
	if (wlf->raydy < 0)
	{
		wlf->stepy = -1;
		wlf->sidedy = (wlf->posy - wlf->mapy) * wlf->deltady;
	}
	else
	{
		wlf->stepy = 1;
		wlf->sidedy = (wlf->mapy + 1.0 - wlf->posy) * wlf->deltady;
	}
	if (wlf->raydz < 0)
	{
		wlf->stepz = -1;
		wlf->sidedz = (wlf->posz - wlf->mapz) * wlf->deltadz;
	}
	else
	{
		wlf->stepz = 1;
		wlf->sidedz = (wlf->mapz + 1.0 - wlf->posz) * wlf->deltadz;
	}
}

void	rc_init(t_wolf *wlf)
{
	wlf->camx = 2 * wlf->x / (double)(WINX) - 1.0;
	wlf->camy = 2 * wlf->y / (double)(WINY) - 1.0;
	wlf->raydx = wlf->dirx + wlf->planex * wlf->camx;
	wlf->raydy = wlf->diry + wlf->planey * wlf->camx;
	wlf->raydz = wlf->dirz + wlf->planez * wlf->camy;
	wlf->mapx = (int)wlf->posx;
	wlf->mapy = (int)wlf->posy;
	wlf->mapz = (int)wlf->posz;
	dda_prep(wlf);
	dda_sys(wlf);
	if (wlf->side == 0)
		wlf->walldist = (wlf->mapx - wlf->posx + (1 - wlf->stepx) / 2) /
				wlf->raydx;
	else if (wlf->side == 1)
		wlf->walldist = (wlf->mapy - wlf->posy + (1 - wlf->stepy) / 2) /
				wlf->raydy;
	else
		wlf->walldist = (wlf->mapz - wlf->posz + (1 - wlf->stepz) / 2) /
				wlf->raydz;
	if (wlf->walldist < 0.0001)
		wlf->walldist += 0.01;
}

void	render(t_wolf *wlf)
{
	wlf->img = init_image(wlf, WINX, WINY);
	wlf->x = -1;
	while (++wlf->x < WINX)
	{
		wlf->y = -1;
		while (++wlf->y < WINY)
		{
			rc_init(wlf);
			
			wlf->lineh = (int)(WINY / wlf->walldist);
			wlf->start = -wlf->lineh / 2 + WINY / 2;
			if (wlf->start < 0)
				wlf->start = 0;
			wlf->end = wlf->lineh / 2 + WINY / 2;
			if (wlf->end >= WINY)
				wlf->end = WINY - 1;
			
			if (wlf->side == 1)
				wlf->testcolor = 0x3679ff;
			else if (wlf->side == 2)
				wlf->testcolor = 0xb01cff;
			else
				wlf->testcolor = 0xF0330A;
			wall_stripe(wlf);
		}
	}
	mlx_put_image_to_window(wlf->mlx, wlf->win, wlf->img.img, 0, 0);
	mlx_destroy_image(wlf->mlx, wlf->img.img);
}
