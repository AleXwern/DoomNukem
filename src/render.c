/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/24 14:20:35 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>//

void	dda_sys(t_doom *wlf)
{
	//ft_putendl("dud");
	wlf->hit = 0;
	while (wlf->hit == 0)
	{
		//printf("--before--\nHit: %d\nMAP: %d %d %d\nSIDE: %f %f %f\n", wlf->hit, wlf->mapz, wlf->mapy, wlf->mapx, wlf->sidedz, wlf->sidedy, wlf->sidedx);
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
		//printf("--after--\nHit: %d\nMAP: %d %d %d\nSIDE: %f %f %f\n", wlf->hit, wlf->mapz, wlf->mapy, wlf->mapx, wlf->sidedz, wlf->sidedy, wlf->sidedx);
		if (wlf->map[wlf->mapz][wlf->mapy][wlf->mapx] > 1)
			wlf->hit = 1;
	}
	//ft_putendl("exit");
}

void	dda_prep(t_doom *wlf)
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

void	rc_init(t_doom *wlf)
{
	wlf->camx = 2.0 * wlf->x / (double)(wlf->winw) - 1.0;
	wlf->camy = 2.0 * wlf->y / (double)(wlf->winh) - 1.0;
	wlf->raydx = wlf->dir.x + wlf->plane.x * wlf->camx;
	wlf->raydy = wlf->dir.y + wlf->plane.y * wlf->camx;
	wlf->raydz = wlf->dir.z + wlf->plane.z * wlf->camy;
	wlf->mapx = (int)wlf->posx;
	wlf->mapy = (int)wlf->posy;
	wlf->mapz = (int)wlf->posz;
	//printf("Cam: %f %f\n RayD: %f %f %f\n Map: %d %d %d\n", wlf->camx, wlf->camy, wlf->raydz, wlf->raydy, wlf->raydx, wlf->mapz, wlf->mapy, wlf->mapx);
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

int		renthread(void *ptr)
{
	t_doom *wlf;

	wlf = (t_doom*)ptr;

	//wlf->tex = SDL_CreateTextureFromSurface(wlf->rend, wlf->gfx[0].tex);
	//wlf->x = 0;
	while (wlf->x < wlf->winw)
	{
		wlf->y = -1;
		while (++wlf->y < wlf->winh)
		{
			rc_init(wlf);
			wlf->lineh = (int)(wlf->winh / wlf->walldist);
			if (wlf->side == 1)
				wlf->testcolor = 0x3679ff;
			else if (wlf->side == 2)
				wlf->testcolor = 0xb01cff;
			else
				wlf->testcolor = 0xF0330A;
			if (wlf->side == 2)
				render_floor(wlf);
			else
				wall_stripe(wlf);
		}
		wlf->x += wlf->trx;
	}
	//wlf->tex = SDL_CreateTextureFromSurface(wlf->rend, wlf->surf);
	//SDL_RenderCopy(wlf->rend, wlf->tex, NULL, NULL);
	//SDL_RenderPresent(wlf->rend);
	return (1);
}

void	gravity(t_doom *wlf)
{
	if (wlf->keytwo)
		return ;
	wlf->gravity.z += 0.1;
	if (wlf->gravity.z > 0.2)
		wlf->gravity.z = 0.2;
	if (wlf->gravity.z < 0)
	{
		if (wlf->map[(int)(wlf->posz + wlf->gravity.z - 0.1)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
			wlf->posz += wlf->gravity.z;
	}
	else if (wlf->map[(int)(wlf->posz + wlf->gravity.z + 0.5)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
		wlf->posz += wlf->gravity.z;
	else
	{
		wlf->airbrn = 0;
		wlf->gravity.z = 0;
	}
	if (wlf->map[(int)(wlf->posz + 0.5)][(int)(wlf->posy)][(int)wlf->posx] > 1)
		wlf->posz -= 0.1;
}

void	pickupitem(t_doom *wlf)
{
	int			obj;

	obj = wlf->map[(int)(wlf->posz + 0.5)][(int)wlf->posy][(int)wlf->posx];
	if (obj == 8)//this will be used when we have sprites.
	{
		wlf->accesscard = 1;
	}
	else if (obj == 5)
	{
		wlf->map[(int)(wlf->posz + 0.5)][(int)wlf->posy][(int)wlf->posx] = 0;
		wlf->accesscard = 1;
	}
}

/*
void	drawinventory(t_doom *wlf, int endx, int endy)//work in progress. Now really slows down the game.
{
	int	x;
	int	y;

	mlx_string_put(wlf->mlx, wlf->win, 710, 160, COLOR_ORANGE, "INVENTORY");
	y = 149;
	while (++y < endy)
	{
		x = 699;
		while (++x < endx)
		{
			mlx_pixel_put(wlf->mlx, wlf->win, y, x, COLOR_WHITE);
		}
	}
}*/

void	render(t_doom *wlf)
{
	int			x;

	gravity(wlf);
	x = 0;
	if (wlf->trx < 0)
		wlf->trx = 1;
	while (x < wlf->trx)
	{
		ft_memcpy((void*)&wlf->data_r[x], (void*)wlf, sizeof(t_doom));
		wlf->data_r[x].x = x;
		wlf->threads[x] = SDL_CreateThread(renthread, "Thread", (void*)&wlf->data_r[x]);
		x++;
	}
	while (x--)
	{
		if (wlf->threads[x] == NULL)
			ft_putendl("Thread failure.");
		else
			SDL_WaitThread(wlf->threads[x], NULL);
	}
	//draw_gfx(wlf, wlf->gfx[15], 100, 100);
	//if (wlf->accesscard == 0)
	//	pickupitem(wlf);
	//if (wlf->keyi)
	//	drawinventory(wlf, 1300, 500);
	//if (wlf->accesscard == 1)
	//	mlx_string_put(wlf->mlx, wlf->win, 300, 200, COLOR_ORANGE, "Access card");
	wlf->tex = SDL_CreateTextureFromSurface(wlf->rend, wlf->img.tex);             
	SDL_RenderCopy(wlf->rend, wlf->tex, NULL, NULL);
	SDL_RenderPresent(wlf->rend);
	wlf->fps++;
}
