/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/02 15:03:37 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>//

int cond = SDL_FALSE;

void	dda_sys(t_doom *wlf)
{
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
}

void	dda_prep(t_doom *wlf)
{
	wlf->deltadx = fabs(1 / wlf->raydx);
	wlf->deltady = fabs(1 / wlf->raydy);
	wlf->deltadz = fabs(1 / wlf->raydz);
	//wlf->deltadx = (1 / wlf->raydx);
	//*((long*)&wlf->deltadx) &= 0x7FFFFFFFFFFFFFFF;
	//wlf->deltady = (1 / wlf->raydy);
	//*((long*)&wlf->deltady) &= 0x7FFFFFFFFFFFFFFF;
	//wlf->deltadz = (1 / wlf->raydz);
	//*((long*)&wlf->deltadz) &= 0x7FFFFFFFFFFFFFFF;
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
		wlf->walldist = (wlf->mapx - wlf->posx + (1 - wlf->stepx) * 0.5) / wlf->raydx;
	else if (wlf->side == 1)
		wlf->walldist = (wlf->mapy - wlf->posy + (1 - wlf->stepy) * 0.5) / wlf->raydy;
	else
		wlf->walldist = (wlf->mapz - wlf->posz + (1 - wlf->stepz) * 0.5) / wlf->raydz;
	if (wlf->walldist < 0.0001)
		wlf->walldist += 0.01;
}

int		renthread(void *ptr)
{
	t_doom *wlf;
	int		x;
	int		test = 0;

	wlf = (t_doom*)ptr;
	x = wlf->x;
	SDL_LockMutex(wlf->mutex);
	while (!wlf->wlf->killthread)
	{
		*wlf = *wlf->wlf;
		wlf->x = x;
		wlf->id = x + 1;
		while (wlf->x < wlf->winw && !wlf->ismenu)
		{
			wlf->y = -1;
			if (wlf->wlf->claimline[wlf->x] == 0)
				wlf->wlf->claimline[wlf->x] = wlf->id;
			while (++wlf->y < wlf->winh/* && wlf->wlf->claimline[wlf->x] == wlf->id*/)
			{
				rc_init(wlf);
				wlf->lineh = (int)(wlf->winh / wlf->walldist);
				if (wlf->side == 1)
					wlf->testcolor = 0xff3679ff;
				else if (wlf->side == 2)
					wlf->testcolor = 0xffb01cff;
				else
					wlf->testcolor = 0xffF0330A;
				wlf->wlf->wallarr[wlf->winw * wlf->y + wlf->x] = wlf->walldist;
				wlf->wlf->maparr[wlf->winw * wlf->y + wlf->x] = (wlf->side + 1) * wlf->map[wlf->mapz][wlf->mapy][wlf->mapx];
				if (wlf->side == 2)
					render_floor(wlf);
				else
					wall_stripe(wlf);
			}
			if (wlf->y > 0)
			{
				test++;
				wlf->wlf->claimline[wlf->x] = -1;
			}
			//printf("Values %d %d %d\n", wlf->x, wlf->winw, wlf->wlf->claimline[wlf->x]);
			//while (wlf->x < wlf->winw && wlf->wlf->claimline[wlf->x] != 0)
			wlf->x += wlf->trx;
		}
		wlf->wlf->claimline[wlf->x]++;
		wlf->wlf->fps++;
		printf("Drew %d threads\n", test);
		if (SDL_CondWait(wlf->wlf->cond, wlf->wlf->mutex) == -1)
		{
			ft_putendl("Broadcast failed");
			exit(0);
		}
		else
			printf("Thread ID %d\n", wlf->id);
		test = 0;
	}
	SDL_UnlockMutex(wlf->mutex);
	return (1);
}

void	gravity(t_doom *wlf)
{
	if (wlf->keytwo || wlf->isgravity || wlf->ismenu)
		return ;
	while (wlf->gravity.z >= 1.0 || wlf->gravity.z <= -1.0)
		wlf->gravity.z += wlf->fallsp.z;
	if (wlf->gravity.z < 0)
	{
		if (wlf->map[(int)(wlf->posz + wlf->gravity.z - 0.1)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
			wlf->posz += wlf->gravity.z;
	}
	else if (wlf->map[(int)(wlf->posz + 1)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
		wlf->posz += wlf->gravity.z;
	else
	{
		wlf->airbrn = 0;
		wlf->gravity.z = 0;
		wlf->posz = floor(wlf->posz) + 0.5;
	}
	wlf->gravity.z += wlf->fallsp.z;
	if (wlf->gravity.z > 0.2 * (30.0 / wlf->buffer / wlf->prefps))
		wlf->gravity.z = 0.2 * (30.0 / wlf->buffer / wlf->prefps);
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
/*
__global__ void test(void)
{
	printf("This is a test\n");
}*/

void	render(t_doom *wlf)
{
	static int	x;

	//x = 0;
	if (wlf->trx < 0)
		wlf->trx = 1;
	while (x < wlf->trx)
	{
		ft_memcpy((void*)&wlf->data_r[x], (void*)wlf, sizeof(t_doom));
		wlf->data_r[x].x = x;
		wlf->data_r[x].id = x + 1;
		wlf->threads[x] = SDL_CreateThread(renthread, "Thread", (void*)&wlf->data_r[x]);
		printf("Created thread: %d\n", x);
		x++;
	}
	while (x > wlf->trx)
	{
		if (wlf->threads[x] == NULL)
			ft_putendl("Thread failure.");
		else
			SDL_WaitThread(wlf->threads[x], NULL);
		x--;
	}
	//wlf->y = -1;
	if (wlf->isoutline)
		post_effects(wlf);
	//draw_gfx(wlf, wlf->gfx[15], 100, 100);
	//if (wlf->accesscard == 0)
	//	pickupitem(wlf);
	//if (wlf->keyi)
	//	drawinventory(wlf, 1300, 500);
	//if (wlf->accesscard == 1)
	//	mlx_string_put(wlf->mlx, wlf->win, 300, 200, COLOR_ORANGE, "Access card");
	//wlf->tex = SDL_CreateTextureFromSurface(wlf->rend, wlf->img.tex);             
	//SDL_RenderCopy(wlf->rend, wlf->img.img, NULL, NULL);
	if (wlf->claimline[wlf->winw] >= wlf->trx)
	{
		SDL_RenderPresent(wlf->rend);
		ft_bzero(wlf->claimline, sizeof(int) * wlf->winw + 1);
		wlf->claimline[wlf->winw] = 0;
		SDL_CondBroadcast(wlf->cond);
	}
	/*else
	{
		for (int i = 0; i <= wlf->winw; i++)
		{
			ft_putnbr(wlf->claimline[i]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}*/
	//wlf->fps++;
}
