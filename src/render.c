/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/17 16:04:27 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>//

void	dda_sys(t_doom *dm)
{
	int	map;

	dm->hit = 0;
	ft_bzero(&dm->texshift, sizeof(t_ivector));
	while (dm->hit == 0)
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
		//printf("--after--\nHit: %d\nMAP: %d %d %d\nSIDE: %f %f %f\n", dm->hit, dm->mapz, dm->mapy, dm->mapx, dm->sidedz, dm->sidedy, dm->sidedx);
		if (dm->map.z < 0 || dm->map.y < 0 || dm->map.x < 0 || dm->map.z >= 9 || dm->map.y >= 25 || dm->map.x >= 25)
		{
			dm->hit = 2;
			return;
		}
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] == 6)
		{
			//part_dda_zp(dm);	//Z plane, filled top - Rays go through the block sometimes, fixed by 1 -> 0.99999
			//part_dda_zn(dm);	//Z plane, filled bottom
			//part_dda_yp(dm);	//Y plane, filled top
			//part_dda_yn(dm);	//Y plane, filled bottom
			//part_dda_xp(dm);	//X plane, filled top
			//part_dda_xn(dm);	//X plane, filled bottom
			slope_dda_xzn(dm);	//XZ slope, filled bottom
			//slope_dda_xzp(dm);	//XZ slope, filled top
		}
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] > 6)
			dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] = 1;
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] > 1)
		{
			dm->hit = 1;
			if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] == 9)//distance from player to sprite (sprite is 9 on the map)
			{
				dm->spriteLoc.x = dm->map.x;
				dm->spriteLoc.y = dm->map.y;
				dm->spriteLoc.z = dm->map.z;
				dm->disttosprite = ((dm->pos.x - dm->map.x) * (dm->pos.x - dm->map.x) + (dm->pos.y - dm->map.y) * (dm->pos.y - dm->map.y));//initialize disttosprite
			}
		}
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
	int	delta;

	if (dm->side == 0)
		delta = dm->pos.x - dm->map.x;
	else if (dm->side == 1)
		delta = dm->pos.y - dm->map.y;
	else
		delta = dm->pos.z - dm->map.z;
	if (delta > 0)
		dm->side += 3;
}

void	draw(t_doom* dm)
{
	dm->rtex.z = dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->map.z;
	dm->rtex.y = dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y;
	dm->rtex.x = dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x;
	dm->texy = (int)((((dm->y * 256 - dm->winh * 128 * dm->camshift - dm->lineh * 128) * 128) / dm->lineh) / 256) % 128;
	if (dm->texy < 0)
		dm->texy += 128;
	dm->texnum = dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x];
	//dm->col = dm->gfx[dm->texnum].data[(int)(128 * (128 * dm->rtex.z) + (128 * dm->rtex.x))];
	dm->col = dm->gfx[dm->texnum].data[(int)(dm->texy + (128 * dm->rtex.y))];
	dm->img.data[dm->winw * dm->y + dm->x] = dm->col;
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
			if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			{
				printf("Sid: %f %f %f\nDelta: %f %f %f\nDir: %f %f %f\nRay: %f %f %f\nMap: %f %f %f\nMad: %f %f %f\nWallD: %f\nSide %d %d\nRmapZ %f %f\n----\n", dm->sided.z, dm->sided.y, dm->sided.x, dm->deltad.z, dm->deltad.y, dm->deltad.x, dm->dir.z, dm->dir.y, dm->dir.x, dm->rayd.z, dm->rayd.y, dm->rayd.x, dm->map.z, dm->map.y, dm->map.x, dm->pos.z + (dm->rayd.z * dm->walldist), dm->pos.y + (dm->dir.y * dm->walldist), dm->pos.x + (dm->dir.x * dm->walldist), dm->walldist, dm->side, dm->area[(int)dm->rmap1.z][(int)dm->rmap1.y][(int)dm->rmap1.x], dm->rmap1.z, dm->rmap2.z);
				dm->img.data[dm->winw * dm->y + dm->x] = 0xfff01111;
				//printf("%f %f %f\n---\n", dm->pos.z + (dm->dir.z * dm->walldist), dm->pos.y + (dm->dir.y * dm->walldist), dm->pos.x + (dm->dir.x * dm->walldist));
			}
			else
			{
				if (dm->hit == 2)
					draw_sky(dm);
				else if (dm->side == 2 || dm->side == 5) // Uncomment these for normal render
					render_floor(dm);
				else
					wall_stripe(dm);
				//else // uncomment this for experimental render
				//	draw(dm);
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
	draw_gun(dm);
	draw_crosshair(dm);
	draw_ammo(dm);
	draw_inventory(dm);
	if (dm->keycard)
		draw_keycard(dm);
	if (dm->key.three)
		draw_sprite(dm);
	if (dm->isoutline)
		post_effects(dm);
	//SDL_UpdateWindowSurface(dm->win);
	SDL_RenderPresent(dm->rend);
	dm->fps++;
}
