/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/04 00:38:53 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

#include <stdio.h>//remove this when project is done.

void	adjusted_dda(t_doom *dm)
{
	if (dm->sided.x < dm->sided.y && dm->sided.x < dm->sided.z)
	{
		dm->sided.x += dm->deltad.x;
		dm->map.x += dm->stepx;
		dm->side = 0;
	}
	else if (dm->sided.y < dm->sided.x && dm->sided.y < dm->sided.z)
	{
		dm->sided.y += dm->deltad.y;
		dm->map.y += dm->stepy;
		dm->side = 1;
	}
	else
	{
		dm->sided.z += dm->deltad.z;
		dm->map.z += dm->stepz;
		dm->side = 2;
	}
	dm->adj = 1;
}

void	dda_sys(t_doom *dm)
{
	dm->hit = 0;
	dm->adj = 0;
	if (dm->rayd.z < 0 && dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].pt == 2)
		dm->adj = 1;
	while (dm->hit == 0)
	{
		if (dm->map.z < 0 || dm->map.y < 0 || dm->map.x < 0 || dm->map.z >= 9 || dm->map.y >= 25 || dm->map.x >= 25)
		{
			dm->hit = 2;
			return;
		}
		if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].pt && !dm->adj
				&& dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b > 1)
			part_check(dm);
		//else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b == 8)
		//	dm->wincol = 1;
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b > 6 && !dm->adj)
			dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b = 1;
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b > 1 && !dm->adj)
			dm->hit = 1;
		if (dm->sided.x < dm->sided.y && dm->sided.x < dm->sided.z && !dm->hit)
		{
			dm->sided.x += dm->deltad.x;
			dm->map.x += dm->stepx;
			dm->side = 0;
		}
		else if (dm->sided.y < dm->sided.x && dm->sided.y < dm->sided.z && !dm->hit)
		{
			dm->sided.y += dm->deltad.y;
			dm->map.y += dm->stepy;
			dm->side = 1;
		}
		else if (!dm->hit)
		{
			dm->sided.z += dm->deltad.z;
			dm->map.z += dm->stepz;
			dm->side = 2;
		}
		dm->adj = 0;
	}
}

void	dda_prep(t_doom *dm)
{
	dm->deltad.x = fabs(1 / dm->rayd.x);
	dm->deltad.y = fabs(1 / dm->rayd.y);
	dm->deltad.z = fabs(1 / dm->rayd.z);
	if (dm->rayd.x < 0)
	{
		dm->stepx = -1;
		dm->sided.x = (dm->pos.x - dm->map.x) * dm->deltad.x;
	}
	else
	{
		dm->stepx = 1;
		dm->sided.x = (dm->map.x + 1.0 - dm->pos.x) * dm->deltad.x;
	}
	if (dm->rayd.y < 0)
	{
		dm->stepy = -1;
		dm->sided.y = (dm->pos.y - dm->map.y) * dm->deltad.y;
	}
	else
	{
		dm->stepy = 1;
		dm->sided.y = (dm->map.y + 1.0 - dm->pos.y) * dm->deltad.y;
	}
	if (dm->rayd.z < 0)
	{
		dm->stepz = -1;
		dm->sided.z = (dm->pos.z - dm->map.z) * dm->deltad.z;
	}
	else
	{
		dm->stepz = 1;
		dm->sided.z = (dm->map.z + 1.0 - dm->pos.z) * dm->deltad.z;
	}
}

void	rc_init(t_doom *dm)
{
	dm->cam.x = 2.0 * dm->x / (double)(dm->winw) - 1.0;
	dm->cam.y = 2.0 * dm->y / (double)(dm->winh) - 1.0;
	dm->rayd.x = dm->dir.x + dm->plane.x * dm->cam.x;
	dm->rayd.y = dm->dir.y + dm->plane.y * dm->cam.x;
	dm->rayd.z = dm->dir.z + dm->plane.z * dm->cam.y;
	dm->map.x = ((int)dm->pos.x) & 0x7fffffff;
	dm->map.y = ((int)dm->pos.y) & 0x7fffffff;
	dm->map.z = ((int)dm->pos.z) & 0x7fffffff;
	//printf("Cam: %f %f\n RayD: %f %f %f\n Map: %f %f %f\n", dm->camx, dm->camy, dm->raydz, dm->raydy, dm->raydx, dm->map.z, dm->map.y, dm->map.x);
	dda_prep(dm);
	dda_sys(dm);
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->walldist < 0.0001)
		dm->walldist += 0.01;
}

void	side_check(t_doom* dm)
{
	int			delta;

	if (dm->side == 0)
		delta = dm->pos.x - dm->map.x;
	else if (dm->side == 1)
		delta = dm->pos.y - dm->map.y;
	else
		delta = dm->pos.z - dm->map.z;
	if (delta > 0)
		dm->side += 3;
}

int		renthread(void *ptr)
{
	t_doom	*dm;

	dm = (t_doom*)ptr;
	while (dm->x < dm->winw)
	{
		dm->y = -1;
		while (++dm->y < dm->winh)
		{
			rc_init(dm);
			dm->lineh = (dm->winh / dm->walldist);
			side_check(dm);
			if (dm->side % 3 == 1)
				dm->col = 0xff3679ff;
			else if (dm->side % 3 == 2)
				dm->col = 0xffb01cff;
			else
				dm->col = 0xffF0330A;
			dm->wallarr[dm->winw * dm->y + dm->x] = dm->walldist;
			//dm->maparr[dm->winw * dm->y + dm->x] = (dm->side + 1) * dm->map[dm->mapz][dm->mapy][dm->mapx];
			dm->maparr[dm->winw * dm->y + dm->x] = dm->side + 1 + dm->map.z + dm->map.y + dm->map.x;
			if (dm->x == 0 && dm->y == 0)
				dm->dm->min = dm->rayd;
			else if (dm->x == dm->winw - 1 && dm->y == dm->winh - 1)
				dm->dm->max = dm->rayd;
			/*if (dm->x == 0 && dm->y == 0)
				printf("Rayd0 %f %f %f\n", dm->rayd.z, dm->rayd.y, dm->rayd.x);
			else if (dm->x == dm->winw - 1 && dm->y == dm->winh - 1)
				printf("RaydXY %f %f %f\n", dm->rayd.z, dm->rayd.y, dm->rayd.x);*/
			if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2 && dm->hit != 2)
			{
				//printf("Sid: %f %f %f\nDelta: %f %f %f\nDir: %f %f %f\nRay: %f %f %f\nMap: %f %f %f\nMad: %f %f %f\nWallD: %f\nSide %d %d\nRmapZ %f %f\n----\n", dm->sided.z, dm->sided.y, dm->sided.x, dm->deltad.z, dm->deltad.y, dm->deltad.x, dm->dir.z, dm->dir.y, dm->dir.x, dm->rayd.z, dm->rayd.y, dm->rayd.x, dm->map.z, dm->map.y, dm->map.x, dm->pos.z + (dm->rayd.z * dm->walldist), dm->pos.y + (dm->dir.y * dm->walldist), dm->pos.x + (dm->dir.x * dm->walldist), dm->walldist, dm->side, dm->area[(int)dm->rmap1.z][(int)dm->rmap1.y][(int)dm->rmap1.x].b, dm->rmap1.z, dm->rmap2.z);
				dm->img.data[dm->winw * dm->y + dm->x] = 0xfff01111;
				//printf("%f %f %f\n---\n", dm->pos.z + (dm->dir.z * dm->walldist), dm->pos.y + (dm->dir.y * dm->walldist), dm->pos.x + (dm->dir.x * dm->walldist));
				//printf("\n\n\nblock hit = %hhu\n\n\n", dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b);
				if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b == 2 && dm->ani == 0 && dm->frm == 1)//if enemy hit, make a soundeffect. Now just testing with block instead of enemy.
				{
					//shooting the walls
					/*if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].hp >= 35)
						dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].hp -= 35;
					else*/
					dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].hp = 0;
					/*if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].hp > 0)
							Mix_PlayChannel(-1, dm->gettingHit, 0);*/
					if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].hp == 0)//else
					{
						Mix_PlayChannel(-1, dm->windowShatter, 0);
						dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b = 1;
					}
				}
				//if (sprite pixel is hit && dm->ani == 0 && dm->frm == 1)
			}
			else
			{
				if (dm->hit == 2)
					draw_sky(dm);
				else if (dm->hit == 3)
					dm->img.data[dm->winw * dm->y + dm->x] = 0xff000000;
				else if (dm->side == 2 || dm->side == 5)
					render_floor(dm);
				else
					wall_stripe(dm);
			}
		}
		dm->x += dm->trx;
	}
	return (1);
}

void	render(t_doom *dm)
{
	static int	x;
	int	i;

	//x = 0;
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
	//sprite_set(dm);
	//printf("Z pos %f\n", dm->pos.z);
	demodraw_sprite(dm);
	draw_hud(dm);
	pickupitem(dm);
	if (dm->isoutline)
		post_effects(dm);
	if (dm->alive && dm->hp <= 0)
	{
		dm->alive = 0;
		Mix_PlayChannel(-1, dm->osrsDeath, 0);
		set_text(dm, "you died", (int[3]){dm->winh / 2 - 26, dm->winw / 2 - 210, 0xE71313}, 2);
		SDL_RenderPresent(dm->rend);
	}
	if (dm->alive)
		SDL_RenderPresent(dm->rend);
	//printf("Pos z y x: %f %f %f\n", dm->pos.z, dm->pos.y, dm->pos.x);
	dm->fps++;
}
