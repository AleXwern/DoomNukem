/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:35:34 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>//

void	dda_sys(t_doom *dm)
{
	dm->hit = 0;
	while (dm->hit == 0)
	{
		//printf("--before--\nHit: %d\nMAP: %d %d %d\nSIDE: %f %f %f\n", dm->hit, dm->mapz, dm->mapy, dm->mapx, dm->sidedz, dm->sidedy, dm->sidedx);
		if (dm->sidedx < dm->sidedy && dm->sidedx < dm->sidedz)
		{
			dm->sidedx += dm->deltadx;
			dm->map.x += dm->stepx;
			dm->side = 0;
		}
		else if (dm->sidedy < dm->sidedx && dm->sidedy < dm->sidedz)
		{
			dm->sidedy += dm->deltady;
			dm->map.y += dm->stepy;
			dm->side = 1;
		}
		else
		{
			dm->sidedz += dm->deltadz;
			dm->map.z += dm->stepz;
			dm->side = 2;
		}
		//printf("--after--\nHit: %d\nMAP: %d %d %d\nSIDE: %f %f %f\n", dm->hit, dm->mapz, dm->mapy, dm->mapx, dm->sidedz, dm->sidedy, dm->sidedx);
		if (dm->map.z < 0 || dm->map.y < 0 || dm->map.x < 0 || dm->map.z >= 9 || dm->map.y >= 25 || dm->map.x >= 25)
			dm->hit = 2;
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] == 7)
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
	dm->deltadx = fabs(1 / dm->raydx);
	dm->deltady = fabs(1 / dm->raydy);
	dm->deltadz = fabs(1 / dm->raydz);
	//dm->deltadx = (1 / dm->raydx);
	//*((long*)&dm->deltadx) &= 0x7FFFFFFFFFFFFFFF;
	//dm->deltady = (1 / dm->raydy);
	//*((long*)&dm->deltady) &= 0x7FFFFFFFFFFFFFFF;
	//dm->deltadz = (1 / dm->raydz);
	//*((long*)&dm->deltadz) &= 0x7FFFFFFFFFFFFFFF;
	if (dm->raydx < 0)
	{
		dm->stepx = -1;
		dm->sidedx = (dm->pos.x - dm->map.x) * dm->deltadx;
	}
	else
	{
		dm->stepx = 1;
		dm->sidedx = (dm->map.x + 1.0 - dm->pos.x) * dm->deltadx;
	}
	if (dm->raydy < 0)
	{
		dm->stepy = -1;
		dm->sidedy = (dm->pos.y - dm->map.y) * dm->deltady;
	}
	else
	{
		dm->stepy = 1;
		dm->sidedy = (dm->map.y + 1.0 - dm->pos.y) * dm->deltady;
	}
	if (dm->raydz < 0)
	{
		dm->stepz = -1;
		dm->sidedz = (dm->pos.z - dm->map.z) * dm->deltadz;
	}
	else
	{
		dm->stepz = 1;
		dm->sidedz = (dm->map.z + 1.0 - dm->pos.z) * dm->deltadz;
	}
}

void	rc_init(t_doom *dm)
{
	dm->camx = 2.0 * dm->x / (double)(dm->winw) - 1.0;
	dm->camy = 2.0 * dm->y / (double)(dm->winh) - 1.0;
	dm->raydx = dm->dir.x + dm->plane.x * dm->camx;
	dm->raydy = dm->dir.y + dm->plane.y * dm->camx;
	dm->raydz = dm->dir.z + dm->plane.z * dm->camy;
	dm->map.x = ((int)dm->pos.x) & 0x0fffffff;
	dm->map.y = ((int)dm->pos.y) & 0x0fffffff;
	dm->map.z = ((int)dm->pos.z) & 0x0fffffff;
	//printf("Cam: %f %f\n RayD: %f %f %f\n Map: %f %f %f\n", dm->camx, dm->camy, dm->raydz, dm->raydy, dm->raydx, dm->map.z, dm->map.y, dm->map.x);
	dda_prep(dm);
	dda_sys(dm);
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->raydx;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->raydy;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->raydz;
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

int		renthread(void *ptr)
{
	t_doom	*dm;
	int		x;
	int		i;
	int		j;
	int		d;

	dm = (t_doom*)ptr;
	x = dm->x;
	//SDL_TryLockMutex(dm->lock);
	while (dm->x < dm->winw)
	{
		dm->y = -1;
		while (++dm->y < dm->winh)
		{
			rc_init(dm);
			dm->lineh = (dm->winh / dm->walldist);
			side_check(dm);
			if (dm->side % 3 == 1)
				dm->testcolor = 0xff3679ff;
			else if (dm->side % 3 == 2)
				dm->testcolor = 0xffb01cff;
			else
				dm->testcolor = 0xffF0330A;
			dm->wallarr[dm->winw * dm->y + dm->x] = dm->walldist;
			//dm->maparr[dm->winw * dm->y + dm->x] = (dm->side + 1) * dm->map[dm->mapz][dm->mapy][dm->mapx];
			dm->maparr[dm->winw * dm->y + dm->x] = dm->side + 1 + dm->map.z + dm->map.y + dm->map.x;
			if (dm->hit == 2)
				draw_sky(dm);
			else if (dm->side == 2 || dm->side == 5)
				render_floor(dm);
			else
				wall_stripe(dm);
			/*
			//trying to draw stationary sprite in map:

			//saving the depth for each raycast
			dm->depthbuffer[dm->x] = dm->walldist;

			//sprites relative location to the player.
			dm->spriteRelLoc.x = dm->spriteLoc.x - dm->posx;
			dm->spriteRelLoc.y = dm->spriteLoc.y - dm->posy;
			dm->spriteRelLoc.z = dm->spriteLoc.z - dm->posz;

			dm->invDet = 1.0 / (dm->plane.x * dm->dir.y - dm->plane.y * dm->dir.x);

			dm->transformX = dm->invDet * (dm->dir.y * dm->spriteRelLoc.x - dm->dir.x * dm->spriteRelLoc.y);
			dm->transformY = dm->invDet * (-dm->plane.y * dm->spriteRelLoc.x + dm->plane.x * dm->spriteRelLoc.y);

			dm->spriteScreenX = (int)((WINX / 2) * (1 + dm->transformX / dm->transformY));
			dm->spriteHeight = abs((int)(WINY / (dm->transformY)));

			dm->drawStartY = -dm->spriteHeight / 2 + WINY / 2;
			if (dm->drawStartY < 0)
				dm->drawStartY = 0;
			dm->drawEndY = dm->spriteHeight / 2 + WINY / 2;
			if (dm->drawEndY >= WINY)
				dm->drawEndY = WINY - 1;
			dm->spriteWidth = abs((int)(WINY / dm->transformY));

			dm->drawStartX = -dm->spriteWidth / 2 + dm->spriteScreenX;
			if (dm->drawStartX < 0)
				dm->drawStartX = 0;
			dm->drawEndX = dm->spriteWidth / 2 + dm->spriteScreenX;
			if (dm->drawEndX >= WINX)
				dm->drawEndX = WINX - 1;
			i = dm->drawStartX;
			while (i < dm->drawEndX)// && dm->transformY > 0 && dm->transformY < dm->depthbuffer[i])	//enderdragon: 564w 396h		GreyDragon: 384w384h
			{
				//dm->textureX = (int)(2256 * (i - (-dm->spriteWidth / 2 + dm->spriteScreenX)) * 564 / dm->spriteWidth) / 2256;//EnderDragon
				dm->textureX = (int)(1536 * (i - (-dm->spriteWidth / 2 + dm->spriteScreenX)) * 384 / dm->spriteWidth) / 1536;//GreyDragon
				if (dm->transformY > 0 && i > 0 && i < WINX && dm->transformY < dm->depthbuffer[i])
				{
					j = dm->drawStartY;
					while (j < dm->drawEndY)
					{
						d = j * 1536 - WINY * 768 + dm->spriteHeight * 768;//GreyDragon
						//d = j * 2256 - WINY * 1128 + dm->spriteHeight * 1128;//EnderDragon
						dm->textureY = ((d * 384) / dm->spriteHeight) / 1536;//GreyDragon
						//dm->textureY = ((d * 396) / dm->spriteHeight) / 1584;//EnderDragon
						//dm->spriteColor = dm->gfx[15].data[564 * dm->textureY + dm->textureX];//EnderDragon
						dm->spriteColor = dm->gfx[23].data[384 * dm->textureY + dm->textureX];//GreyDragon
						if (dm->spriteColor != 0xffff00ff || dm->spriteColor != 4294902015)//Used to not draw EnderDragons pink background && transparent background in GreyDragon(?)
							dm->img.data[WINX * j + i] = dm->spriteColor;
						j++;
					}
				}
				i++;
			}*/
		}
		dm->x += dm->trx;
	}
	//SDL_UnlockMutex(dm->lock);
	//printf("Thread ID %d drew %d threads\nClaimline at %d\n", dm->id, test, dm->dm->claimline[dm->winw]);
	//SDL_UnlockMutex(dm->lock);
	return (1);
}

void	gravity(t_doom *dm)
{
	if (dm->key.two || dm->isgravity || dm->ismenu)
		return ;
	if (dm->gravity.z >= 1.0 || dm->gravity.z <= -1.0)
		dm->gravity.z /= fabs(dm->gravity.z);
	//dm->gravity.z += dm->fallsp.z;
	if (dm->gravity.z < 0)
	{
		if (dm->area[(int)(dm->pos.z + dm->gravity.z - 0.1)][(int)(dm->pos.y)][(int)dm->pos.x] <= 1)
			dm->pos.z += dm->gravity.z;
	}
	else if (dm->area[(int)(dm->pos.z + 1)][(int)(dm->pos.y)][(int)dm->pos.x] <= 1)
		dm->pos.z += dm->gravity.z;
	else
	{
		dm->airbrn = 0;
		dm->gravity.z = 0;
		dm->pos.z = floor(dm->pos.z) + 0.5;
	}
	dm->gravity.z += dm->fallsp.z;
	if (dm->gravity.z > 0.2 * (30.0 / dm->buffer / dm->prefps))
		dm->gravity.z = 0.2 * (30.0 / dm->buffer / dm->prefps);
	if (dm->area[(int)(dm->pos.z + 0.5)][(int)(dm->pos.y)][(int)dm->pos.x] > 1)
		dm->pos.z -= 0.1;
}

void	pickupitem(t_doom *dm)
{
	int			obj;

	obj = dm->area[(int)(dm->pos.z + 0.5)][(int)dm->pos.y][(int)dm->pos.x];
	if (obj == 8)//this will be used when we have sprites.
	{
		dm->keycard = 1;
	}
	else if (obj == 5)
	{
		dm->area[(int)(dm->pos.z + 0.5)][(int)dm->pos.y][(int)dm->pos.x] = 0;
		dm->keycard = 1;
	}
}

/*
void	drawinventory(t_doom *dm, int endx, int endy)//work in progress. Now really slows down the game.
{
	int	x;
	int	y;

	mlx_string_put(dm->mlx, dm->win, 710, 160, COLOR_ORANGE, "INVENTORY");
	y = 149;
	while (++y < endy)
	{
		x = 699;
		while (++x < endx)
		{
			mlx_pixel_put(dm->mlx, dm->win, y, x, COLOR_WHITE);
		}
	}
}*/

void	load_animsprite(t_doom *dm)
{
	//This will be good for use later when we have many sprites:
	//SDL_QueryTexture() method gets the width and height of the texture
	//SDL_QueryTexture(spriteSheet, NULL, NULL, &textureRect.w, &textureRect.h);
	//Now, textureRect.w and textureRect.h are filled
	//with respective dimensions of the image/texture

	//As there are 8 frames with same width, we simply
	//get the width of a frame by dividing with 8
	//textureRect.w /= 8;
	//Height for each frame is the same as for the whole sheet/texture


	//dm->sprites = IMG_Load("./gfx/SpriteSheets/PokemonTrainer.png");
	dm->spriteSurface = IMG_Load("./gfx/SpriteSheets/GreyDragon.xpm");
	dm->spriteTexture = SDL_CreateTextureFromSurface(dm->rend, dm->spriteSurface);
	SDL_FreeSurface(dm->spriteSurface);

	dm->frame = 0;
	dm->anim = 3;
	//walking towards you
	dm->spriteRect[0][0].x = 0;//upper left corner x-coordinate
	dm->spriteRect[0][0].y = 0;//upper left corner y-coordinate
	dm->spriteRect[0][0].w = 96;//width of one animation part of the sheet
	dm->spriteRect[0][0].h = 96;//height of one animation part of the sheet

	dm->spriteRect[0][1].x = 96;
	dm->spriteRect[0][1].y = 0;
	dm->spriteRect[0][1].w = 96;
	dm->spriteRect[0][1].h = 96;

	dm->spriteRect[0][2].x = 192;
	dm->spriteRect[0][2].y = 0;
	dm->spriteRect[0][2].w = 96;
	dm->spriteRect[0][2].h = 96;

	dm->spriteRect[0][3].x = 288;
	dm->spriteRect[0][3].y = 0;
	dm->spriteRect[0][3].w = 96;
	dm->spriteRect[0][3].h = 96;

	//walking to your left
	dm->spriteRect[1][0].x = 0;//upper left corner x-coordinate
	dm->spriteRect[1][0].y = 96;//upper left corner y-coordinate
	dm->spriteRect[1][0].w = 96;//width of one animation part of the sheet
	dm->spriteRect[1][0].h = 96;//height of one animation part of the sheet

	dm->spriteRect[1][1].x = 96;
	dm->spriteRect[1][1].y = 96;
	dm->spriteRect[1][1].w = 96;
	dm->spriteRect[1][1].h = 96;

	dm->spriteRect[1][2].x = 192;
	dm->spriteRect[1][2].y = 96;
	dm->spriteRect[1][2].w = 96;
	dm->spriteRect[1][2].h = 96;

	dm->spriteRect[1][3].x = 288;
	dm->spriteRect[1][3].y = 96;
	dm->spriteRect[1][3].w = 96;
	dm->spriteRect[1][3].h = 96;

	//walking to your right
	dm->spriteRect[2][0].x = 0;//upper left corner x-coordinate
	dm->spriteRect[2][0].y = 192;//upper left corner y-coordinate
	dm->spriteRect[2][0].w = 96;//width of one animation part of the sheet
	dm->spriteRect[2][0].h = 96;//height of one animation part of the sheet

	dm->spriteRect[2][1].x = 96;
	dm->spriteRect[2][1].y = 192;
	dm->spriteRect[2][1].w = 96;
	dm->spriteRect[2][1].h = 96;

	dm->spriteRect[2][2].x = 192;
	dm->spriteRect[2][2].y = 192;
	dm->spriteRect[2][2].w = 96;
	dm->spriteRect[2][2].h = 96;

	dm->spriteRect[2][3].x = 288;
	dm->spriteRect[2][3].y = 192;
	dm->spriteRect[2][3].w = 96;
	dm->spriteRect[2][3].h = 96;

	//walking away from you
	dm->spriteRect[3][0].x = 0;//upper left corner x-coordinate
	dm->spriteRect[3][0].y = 288;//upper left corner y-coordinate
	dm->spriteRect[3][0].w = 96;//width of one animation part of the sheet
	dm->spriteRect[3][0].h = 96;//height of one animation part of the sheet

	dm->spriteRect[3][1].x = 96;
	dm->spriteRect[3][1].y = 288;
	dm->spriteRect[3][1].w = 96;
	dm->spriteRect[3][1].h = 96;

	dm->spriteRect[3][2].x = 192;
	dm->spriteRect[3][2].y = 288;
	dm->spriteRect[3][2].w = 96;
	dm->spriteRect[3][2].h = 96;

	dm->spriteRect[3][3].x = 288;
	dm->spriteRect[3][3].y = 288;
	dm->spriteRect[3][3].w = 96;
	dm->spriteRect[3][3].h = 96;

	dm->screenRect.x = (WINX - 200) / 2;//where on screen the upper left corner of the sprite should be drawn
	dm->screenRect.y = (WINY - 200) / 2;//where on screen the upper left corner of the sprite should be drawn
	dm->screenRect.w = 200;//width of the final sprite on screen
	dm->screenRect.h = 200;//height of the final sprite on screen
}

void	draw_sprite(t_doom *dm)
{
	SDL_RenderCopy(dm->rend, dm->spriteTexture, &dm->spriteRect[dm->anim][dm->frame / 4], &dm->screenRect);
	dm->frame++;
	if (dm->screenRect.w < 550)
		dm->screenRect.w += 3;
	if (dm->screenRect.x > 200)//440
		dm->screenRect.x -= 3;
	if (dm->screenRect.w < 550)
		dm->screenRect.h += 3;
	if (dm->screenRect.y > 200)
		dm->screenRect.y -= 3;
	if ((dm->frame / 4) > 3)
	{
		if (dm->anim != 0)
			dm->anim--;
		dm->frame = 0;
	}
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
	//SDL_RenderPresent(dm->rend);
	draw_gun(dm);
	draw_crosshair(dm);
	draw_ammo(dm);
	draw_inventory(dm);
	if (dm->keycard)
		draw_keycard(dm);
	/*if (dm->key.i)
		draw_sprite(dm);*/
	if (dm->isoutline)
		post_effects(dm);
	//SDL_UpdateWindowSurface(dm->win);
	SDL_RenderPresent(dm->rend);
	dm->fps++;
}
