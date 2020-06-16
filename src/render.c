/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/16 17:05:01 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

#include <stdio.h>//

void	dda_sys(t_wolf *wlf)
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

void	*multit(void *arg)
{
	t_wolf *wlf;

	wlf = (t_wolf*)arg;

	while (wlf->x < wlf->xmax)
	{
		wlf->y = -1;
		while (++wlf->y < WINY)
		{
			rc_init(wlf);
			wlf->lineh = (int)(WINY / wlf->walldist);
			/*
			if (wlf->side == 2)
				wlf->lineh = (int)(WINX / wlf->walldist);
			wlf->start = -wlf->lineh / 2 + WINY / 2;
			if (wlf->start < 0)
				wlf->start = 0;
			wlf->end = wlf->lineh / 2 + WINY / 2;
			if (wlf->end >= WINY)
				wlf->end = WINY - 1;
			*/
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
		wlf->x++;
	}
	return (0);
}

void	gravity(t_wolf *wlf)
{
	if (wlf->keytwo)
		return ;
	if (wlf->map[(int)(wlf->posz + 0.5)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
		wlf->posz += 0.1;
}

void	pickupitem(t_wolf *wlf)
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

void	drawinventory(t_wolf *wlf, int endx, int endy)//work in progress. Now really slows down the game.
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
}

void	draw_gfx(t_wolf *wlf, t_gfx gfx, int x, int y)
{
	int	gx;
	int	gy;

	gy = 0;
	while (gy < gfx.hgt)
	{
		gx = 0;
		while (gx < gfx.wid)
		{
			if (gfx.data[gfx.wid * gy + gx] != 0xff00ff)
				wlf->img.data[WINX * (y + gy) + (x + gx)] = gfx.data[gfx.wid *
					gy + gx];
			gx++;
		}
		gy++;
	}
}

void	render(t_wolf *wlf)
{
	pthread_t	threads[THREADS];
	t_wolf		data_r[THREADS];
	int			x;
	t_gfx		gfx;

	gravity(wlf);
	x = 0;
	wlf->img = init_image(wlf, WINX, WINY);
	while (x < THREADS)
	{
		ft_memcpy((void*)&data_r[x], (void*)wlf, sizeof(t_wolf));
		data_r[x].x = x * (WINX / THREADS);
		data_r[x].xmax = (x + 1) * (WINX / THREADS);
		pthread_create(&threads[x], NULL, multit, &data_r[x]);
		x++;
	}
	while (x--)
		pthread_join(threads[x], NULL);
	draw_gfx(wlf, wlf->gfx[15], 100, 100);
	if (wlf->accesscard == 0)
		pickupitem(wlf);
	mlx_put_image_to_window(wlf->mlx, wlf->win, wlf->img.img, 0, 0);
	if (wlf->keyi)
		drawinventory(wlf, 1300, 500);
	if (wlf->accesscard == 1)
		mlx_string_put(wlf->mlx, wlf->win, 300, 200, COLOR_ORANGE, "Access card");
	mlx_destroy_image(wlf->mlx, wlf->img.img);
}
