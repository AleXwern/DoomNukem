/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/17 14:20:26 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	destroy_gfx(t_doom* wlf, int i)
{
	while (++i < wlf->gfxcount)
	{
		if (wlf->gfx[i].wid > 0)
		{
			ft_putstr("Clear GFX: ");
			ft_putnbrln(i);
			SDL_FreeSurface(wlf->gfx[i].tex);
		}
	}
	free(wlf->gfx);
}

t_gfx			init_image(t_doom *wolf)
{
	t_gfx	image;

	if (!(image.tex = SDL_GetWindowSurface(wolf->win)))
		error_out(WIN_ERROR, wolf);
	image.img = SDL_CreateTextureFromSurface(wolf->rend, image.tex);
	image.data = (Uint32*)image.tex->pixels;
	return (image);
}

t_gfx	gfx_get(t_doom *wolf, char *file, int x, int y)
{
	t_gfx			gfx;
	SDL_Surface*	surf;

	//ft_putendl(file);
	wolf->rwops = SDL_RWFromFile(file, "rb");
	surf = IMG_Load(file);
	if (!surf)
	{
		printf("IMG error: %s\n", IMG_GetError());
		SDL_FreeSurface(surf);
		free(file);
		gfx.wid = 0;
		gfx.hgt = 0;
		SDL_FreeRW(wolf->rwops);
		error_out(GFX_ERROR, wolf);
	}
	gfx.tex = SDL_ConvertSurfaceFormat(surf, wolf->img.tex->format->format, 0);
	SDL_FreeSurface(surf);
	gfx.wid = gfx.tex->w;
	gfx.hgt = gfx.tex->h;
	gfx.data = (Uint32*)gfx.tex->pixels;
	free(file);
	SDL_FreeRW(wolf->rwops);
	return (gfx);
}

/*
**	i = 15-23 for the foes.
*/

void	comp_foe(t_doom *wlf, char *bpath, int i)
{
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "foe/foe0.xpm"), 564, 396);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "foe/foe1.xpm"), 564, 396);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "foe/foe2.xpm"), 564, 396);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "foe/foe4.xpm"), 564, 396);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "foe/foe5.xpm"), 564, 396);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "foe/foe6.xpm"), 564, 396);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "foe/foe7.xpm"), 564, 396);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "foe/foe8.xpm"), 564, 396);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "SpriteSheets/GreyDragon.xpm"), 384, 384);
	wlf->gfx[i++] = gfx_get(wlf, ft_strjoin(bpath, "misc/icon.xpm"), 157, 157);
	wlf->gfxcount = i;
	if (i != GFXCOUNT)
		error_out(GFX_ERROR, wlf);
}

/*
** 7-14 second set
*/

void	comp_hud_gfx(t_doom *wolf, char *bpath, int i)
{
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/notifup.xpm"), 41, 57);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/notifdown.xpm"), 441, 57);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/options.xpm"), 540, 720);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "foe/foe3.xpm"), 564, 396);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/btlmenu.xpm"), 221, 312);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/btlsel.xpm"), 221, 312);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/pcturn.xpm"), 354, 95);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/pcsel.xpm"), 354, 95);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/mainmenu.xpm"), 1080, 720);
	//free(bpath);
	//wolf->gfxcount = i;
	comp_foe(wolf, bpath, i);
}

/*
** 0-6 first set
*/

void	comp_gfx(t_doom *wolf, int i)
{
	char	*bpath;
	char	*path;

	wolf->tile += 48;
	path = SDL_GetBasePath();
	//bpath = "C:\\Users\\alexn\\Desktop\\All-things-coding\\WinDoom\\gfx\\";
	bpath = ft_strjoin(path, "gfx/");
	if (!(wolf->gfx = (t_gfx*)malloc(sizeof(t_gfx) * GFXCOUNT)))
		error_out(MEM_ERROR, wolf);
	wolf->gfx[i++] = gfx_get(wolf, ft_quadjoin(bpath, (char*)&wolf->tile, "/sky.xpm", ""), 1080, 360);
	wolf->gfx[i++] = gfx_get(wolf, ft_quadjoin(bpath, (char*)&wolf->tile, "/floor.xpm", ""), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_quadjoin(bpath, (char*)&wolf->tile, "/wall.xpm", ""), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_quadjoin(bpath, (char*)&wolf->tile, "/stairu.xpm", ""), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_quadjoin(bpath, (char*)&wolf->tile, "/staird.xpm", ""), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_quadjoin(bpath, (char*)&wolf->tile, "/door.xpm", ""), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_quadjoin(bpath, (char*)&wolf->tile, "/warp.xpm", ""), 128, 128);
	comp_hud_gfx(wolf, bpath, i);
	wolf->tile -= 48;
	SDL_free(path);
	free(bpath);
}
