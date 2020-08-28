/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:04:11 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/06 19:04:11 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	initSprite(t_sprite *sprite)
{
	sprite->id = 0;
	sprite->pos.x = 0;
	sprite->pos.y = 0;
	sprite->pos.z = 1;
	sprite->hp = 100;
}

void	damageSprite(t_doom *dm, int spriteId, int damage)
{
	dm->spr.hp -= damage;
	if (dm->spr.hp <= 0)//sprite dies
	{
		Mix_PlayChannel(-1, dm->osrsMonsterDeath, 0);
	}
	else//sprite got hit but didn't die
	{
		Mix_PlayChannel(-1, dm->gettingHit, 0);
	}
}

void	pickupitem(t_doom* dm)
{
	int			obj;

	obj = dm->area[(int)(dm->pos.z + 0.5)][(int)dm->pos.y][(int)dm->pos.x].b;
	if (obj == 8)//this will be used when we have sprites.
	{
		dm->keycard = 1;
	}
	else if (obj == 5)
	{
		dm->area[(int)(dm->pos.z + 0.5)][(int)dm->pos.y][(int)dm->pos.x].b = 0;
		dm->keycard = 1;
	}
}

void	load_animsprite(t_doom* dm)
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

void	draw_sprite(t_doom* dm)
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

// Contents that were in Rendthread function. Cleaned it up as it was way too annoying to scroll so many lines everytime
/*int		renthread(void* ptr)
{
	t_doom* dm;
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
			}
		}
		dm->x += dm->trx;
	}
	//SDL_UnlockMutex(dm->lock);
	//printf("Thread ID %d drew %d threads\nClaimline at %d\n", dm->id, test, dm->dm->claimline[dm->winw]);
	//SDL_UnlockMutex(dm->lock);
	return (1);
}*/
