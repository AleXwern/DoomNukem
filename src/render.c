/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/10 14:55:47 by tbergkul         ###   ########.fr       */
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
		{
			wlf->hit = 1;
			if (wlf->map[wlf->mapz][wlf->mapy][wlf->mapx] == 9)//distance from player to sprite (sprite is 9 on the map)
			{
				wlf->spriteLoc.x = wlf->mapx;
				wlf->spriteLoc.y = wlf->mapy;
				wlf->spriteLoc.z = wlf->mapz;
				wlf->disttosprite = ((wlf->posx - wlf->mapx) * (wlf->posx - wlf->mapx) + (wlf->posy - wlf->mapy) * (wlf->posy - wlf->mapy));//initialize disttosprite
			}
		}
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
	wlf->mapx = ((int)wlf->posx) & 0x0fffffff;
	wlf->mapy = ((int)wlf->posy) & 0x0fffffff;
	wlf->mapz = ((int)wlf->posz) & 0x0fffffff;
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

void	side_check(t_doom* wlf)
{
	int	delta;

	if (wlf->side == 0)
		delta = wlf->posx - wlf->mapx;
	else if (wlf->side == 1)
		delta = wlf->posy - wlf->mapy;
	else
		delta = wlf->posz - wlf->mapz;
	if (delta > 0)
		wlf->side += 3;
}

int		renthread(void *ptr)
{
	t_doom	*wlf;
	int		i;
	int		j;
	int		d;

	wlf = (t_doom*)ptr;
	//SDL_TryLockMutex(wlf->mutex);
	while (wlf->x < wlf->winw)
	{
		wlf->y = -1;
		while (++wlf->y < wlf->winh)
		{
			rc_init(wlf);
			wlf->lineh = (wlf->winh / wlf->walldist);
			side_check(wlf);
			if (wlf->side % 3 == 1)
				wlf->testcolor = 0xff3679ff;
			else if (wlf->side % 3 == 2)
				wlf->testcolor = 0xffb01cff;
			else
				wlf->testcolor = 0xffF0330A;
			wlf->wallarr[wlf->winw * wlf->y + wlf->x] = wlf->walldist;
			//wlf->maparr[wlf->winw * wlf->y + wlf->x] = (wlf->side + 1) * wlf->map[wlf->mapz][wlf->mapy][wlf->mapx];
			wlf->maparr[wlf->winw * wlf->y + wlf->x] = wlf->side + 1 + wlf->mapz + wlf->mapy + wlf->mapx;
			if (wlf->side == 2 || wlf->side == 5)
				render_floor(wlf);
			else
				wall_stripe(wlf);

			//trying to draw stationary sprite in map:

			//saving the depth for each raycast
			wlf->depthbuffer[wlf->x] = wlf->walldist;

			//sprites relative location to the player.
			wlf->spriteRelLoc.x = wlf->spriteLoc.x - wlf->posx;
			wlf->spriteRelLoc.y = wlf->spriteLoc.y - wlf->posy;
			wlf->spriteRelLoc.z = wlf->spriteLoc.z - wlf->posz;

			wlf->invDet = 1.0 / (wlf->plane.x * wlf->dir.y - wlf->plane.y * wlf->dir.x);

			wlf->transformX = wlf->invDet * (wlf->dir.y * wlf->spriteRelLoc.x - wlf->dir.x * wlf->spriteRelLoc.y);
			wlf->transformY = wlf->invDet * (-wlf->dir.y * wlf->spriteRelLoc.x + wlf->plane.x * wlf->spriteRelLoc.y);

			wlf->spriteScreenX = (int)((WINX / 2) * (1 + wlf->transformX / wlf->transformY));
			wlf->spriteHeight = abs((int)(WINY / (wlf->transformY)));

			wlf->drawStartY = -wlf->spriteHeight / 2 + WINY / 2;
			if (wlf->drawStartY < 0)
				wlf->drawStartY = 0;
			wlf->drawEndY = wlf->spriteHeight / 2 + WINY / 2;
			if (wlf->drawEndY >= WINY)
				wlf->drawEndY = WINY - 1;
			wlf->spriteWidth = abs((int)(WINY / wlf->transformY));

			wlf->drawStartX = -wlf->spriteWidth / 2 + wlf->spriteScreenX;
			if (wlf->drawStartX < 0)
				wlf->drawStartX = 0;
			wlf->drawEndX = wlf->spriteWidth / 2 + wlf->spriteScreenX;
			if (wlf->drawEndX >= WINX)
				wlf->drawEndX = WINX - 1;
			i = wlf->drawStartX - 1;
			while (++i < wlf->drawEndX)//enderdragon: 564w 396h			GreyDragon: 384w384h
			{
				//wlf->textureX = (int)(564 * (i - (-wlf->spriteWidth / 2 + wlf->spriteScreenX)) * 564 / wlf->spriteWidth) / 564;//EnderDragon
				wlf->textureX = (int)(1536 * (i - (-wlf->spriteWidth / 2 + wlf->spriteScreenX)) * 384 / wlf->spriteWidth) / 1536;//GreyDragon
				if (wlf->transformY > 0 && i > 0 && i < WINX && wlf->transformY < wlf->depthbuffer[i])
				{
					j = wlf->drawStartY - 1;
					while (++j < wlf->drawEndY)
					{
						d = j * 1536 - WINY * 768 + wlf->spriteHeight * 768;//GreyDragon
						//d = j * 2256 - WINY * 1128 + wlf->spriteHeight * 1128;//EnderDragon
						wlf->textureY = ((d * 384) / wlf->spriteHeight) / 1536;//GreyDragon
						//wlf->textureY = ((d * 396) / wlf->spriteHeight) / 396;//EnderDragon
						//wlf->spriteColor = wlf->gfx[15].data[396 * wlf->textureY + wlf->textureX];//EnderDragon
						wlf->spriteColor = wlf->gfx[23].data[384 * wlf->textureY + wlf->textureX];//GreyDragon
						//if (wlf->spriteColor != 0xffff00ff)//Use if EnderDragon with pink background
						wlf->img.data[WINX * j + i] = wlf->spriteColor;
					}
				}
			}
		}
		wlf->x += wlf->trx;
	}
	//printf("Thread ID %d drew %d threads\nClaimline at %d\n", wlf->id, test, wlf->wlf->claimline[wlf->winw]);
	//UnlockMutex(wlf->mutex);
	return (1);
}

void	gravity(t_doom *wlf)
{
	if (wlf->key.two || wlf->isgravity || wlf->ismenu)
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

void	load_animsprite(t_doom *wlf)
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


	//wlf->sprites = IMG_Load("./gfx/SpriteSheets/PokemonTrainer.png");
	wlf->spriteSurface = IMG_Load("./gfx/SpriteSheets/GreyDragon.png");
	wlf->spriteTexture = SDL_CreateTextureFromSurface(wlf->rend, wlf->spriteSurface);
	SDL_FreeSurface(wlf->spriteSurface);

	wlf->frame = 0;
	wlf->anim = 3;
	//walking towards you
	wlf->spriteRect[0][0].x = 0;//upper left corner x-coordinate
	wlf->spriteRect[0][0].y = 0;//upper left corner y-coordinate
	wlf->spriteRect[0][0].w = 96;//width of one animation part of the sheet
	wlf->spriteRect[0][0].h = 96;//height of one animation part of the sheet

	wlf->spriteRect[0][1].x = 96;
	wlf->spriteRect[0][1].y = 0;
	wlf->spriteRect[0][1].w = 96;
	wlf->spriteRect[0][1].h = 96;

	wlf->spriteRect[0][2].x = 192;
	wlf->spriteRect[0][2].y = 0;
	wlf->spriteRect[0][2].w = 96;
	wlf->spriteRect[0][2].h = 96;

	wlf->spriteRect[0][3].x = 288;
	wlf->spriteRect[0][3].y = 0;
	wlf->spriteRect[0][3].w = 96;
	wlf->spriteRect[0][3].h = 96;

	//walking to your left
	wlf->spriteRect[1][0].x = 0;//upper left corner x-coordinate
	wlf->spriteRect[1][0].y = 96;//upper left corner y-coordinate
	wlf->spriteRect[1][0].w = 96;//width of one animation part of the sheet
	wlf->spriteRect[1][0].h = 96;//height of one animation part of the sheet

	wlf->spriteRect[1][1].x = 96;
	wlf->spriteRect[1][1].y = 96;
	wlf->spriteRect[1][1].w = 96;
	wlf->spriteRect[1][1].h = 96;

	wlf->spriteRect[1][2].x = 192;
	wlf->spriteRect[1][2].y = 96;
	wlf->spriteRect[1][2].w = 96;
	wlf->spriteRect[1][2].h = 96;

	wlf->spriteRect[1][3].x = 288;
	wlf->spriteRect[1][3].y = 96;
	wlf->spriteRect[1][3].w = 96;
	wlf->spriteRect[1][3].h = 96;

	//walking to your right
	wlf->spriteRect[2][0].x = 0;//upper left corner x-coordinate
	wlf->spriteRect[2][0].y = 192;//upper left corner y-coordinate
	wlf->spriteRect[2][0].w = 96;//width of one animation part of the sheet
	wlf->spriteRect[2][0].h = 96;//height of one animation part of the sheet

	wlf->spriteRect[2][1].x = 96;
	wlf->spriteRect[2][1].y = 192;
	wlf->spriteRect[2][1].w = 96;
	wlf->spriteRect[2][1].h = 96;

	wlf->spriteRect[2][2].x = 192;
	wlf->spriteRect[2][2].y = 192;
	wlf->spriteRect[2][2].w = 96;
	wlf->spriteRect[2][2].h = 96;

	wlf->spriteRect[2][3].x = 288;
	wlf->spriteRect[2][3].y = 192;
	wlf->spriteRect[2][3].w = 96;
	wlf->spriteRect[2][3].h = 96;

	//walking away from you
	wlf->spriteRect[3][0].x = 0;//upper left corner x-coordinate
	wlf->spriteRect[3][0].y = 288;//upper left corner y-coordinate
	wlf->spriteRect[3][0].w = 96;//width of one animation part of the sheet
	wlf->spriteRect[3][0].h = 96;//height of one animation part of the sheet

	wlf->spriteRect[3][1].x = 96;
	wlf->spriteRect[3][1].y = 288;
	wlf->spriteRect[3][1].w = 96;
	wlf->spriteRect[3][1].h = 96;

	wlf->spriteRect[3][2].x = 192;
	wlf->spriteRect[3][2].y = 288;
	wlf->spriteRect[3][2].w = 96;
	wlf->spriteRect[3][2].h = 96;

	wlf->spriteRect[3][3].x = 288;
	wlf->spriteRect[3][3].y = 288;
	wlf->spriteRect[3][3].w = 96;
	wlf->spriteRect[3][3].h = 96;

	wlf->screenRect.x = (WINX - 200) / 2;//where on screen the upper left corner of the sprite should be drawn
	wlf->screenRect.y = (WINY - 200) / 2;//where on screen the upper left corner of the sprite should be drawn
	wlf->screenRect.w = 200;//width of the final sprite on screen
	wlf->screenRect.h = 200;//height of the final sprite on screen
}

void	draw_sprite(t_doom *wlf)
{
	SDL_RenderCopy(wlf->rend, wlf->spriteTexture, &wlf->spriteRect[wlf->anim][wlf->frame / 4], &wlf->screenRect);
	wlf->frame++;
	if (wlf->screenRect.w < 550)
		wlf->screenRect.w += 3;
	if (wlf->screenRect.x > 200)//440
		wlf->screenRect.x -= 3;
	if (wlf->screenRect.w < 550)
		wlf->screenRect.h += 3;
	if (wlf->screenRect.y > 200)
		wlf->screenRect.y -= 3;
	if ((wlf->frame / 4) > 3)
	{
		if (wlf->anim != 0)
			wlf->anim--;
		wlf->frame = 0;
	}
}

void	render(t_doom *wlf)
{
	int	x;
	int	i;

	x = 0;
	if (wlf->trx < 0)
		wlf->trx = 1;
	while (x < wlf->trx)
	{
		wlf->data_r[x] = *wlf;
		wlf->data_r[x].x = x;
		wlf->threads[x] = SDL_CreateThread(renthread, "Thread", (void*)&wlf->data_r[x]);
		x++;
	}
	while (--x >= 0)
	{
		if (wlf->threads[x] == NULL)
			ft_putendl("Thread failure.");
		else
			SDL_WaitThread(wlf->threads[x], NULL);
	}
	if (wlf->key.i)
		draw_sprite(wlf);
	if (wlf->isoutline)
		post_effects(wlf);
	//SDL_UpdateWindowSurface(wlf->win);
	SDL_RenderPresent(wlf->rend);
	wlf->fps++;
	//draw_gfx(wlf, wlf->gfx[15], 100, 100);
	//if (wlf->accesscard == 0)
	//	pickupitem(wlf);
	//if (wlf->keyi)
	//	drawinventory(wlf, 1300, 500);
	//if (wlf->accesscard == 1)
	//	mlx_string_put(wlf->mlx, wlf->win, 300, 200, COLOR_ORANGE, "Access card");
}
