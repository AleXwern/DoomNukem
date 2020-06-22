/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/22 15:29:34 by anystrom         ###   ########.fr       */
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
	image.data = (Uint32*)image.tex->pixels;
	return (image);
}

t_gfx	gfx_get(t_doom *wolf, char *file, int x, int y)
{
	t_gfx			gfx;
	SDL_Surface*	surf;

	ft_putendl(file);
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
		return (gfx);
		//error_out(GFX_ERROR, wolf);
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
**	i = 15-22 for the foes.
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
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "3/battlebg.xpm"), WINX, WINY);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "foe/foe3.xpm"), 564, 396);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/btlmenu.xpm"), 221, 312);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/btlsel.xpm"), 221, 312);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/pcturn.xpm"), 354, 95);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "hud/pcsel.xpm"), 354, 95);
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
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "3/sky.xpm"), 1080, 360);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "3/floor.xpm"), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "3/wall.xpm"), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "3/stairu.xpm"), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "3/staird.xpm"), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "3/door.xpm"), 128, 128);
	wolf->gfx[i++] = gfx_get(wolf, ft_strjoin(bpath, "3/warp.xpm"), 128, 128);
	comp_hud_gfx(wolf, bpath, i);
	SDL_free(path);
	free(bpath);
}
