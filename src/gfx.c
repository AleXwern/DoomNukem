/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:34:07 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	destroy_gfx(t_doom* dm, int i)
{
	while (++i < dm->gfxcount)
	{
		if (dm->gfx[i].wid > 0)
		{
			ft_putstr("Clear GFX: ");
			ft_putnbrln(i);
			SDL_FreeSurface(dm->gfx[i].tex);
		}
	}
	free(dm->gfx);
}

t_gfx			init_image(t_doom *dm)
{
	t_gfx	image;

	if (!(image.tex = SDL_GetWindowSurface(dm->win)))
		error_out(WIN_ERROR, dm);
	image.img = SDL_CreateTextureFromSurface(dm->rend, image.tex);
	image.data = (Uint32*)image.tex->pixels;
	return (image);
}

t_gfx	gfx_get(t_doom *dm, char *file, int x, int y)
{
	t_gfx			gfx;
	SDL_Surface*	surf;

	//ft_putendl(file);
	dm->rwops = SDL_RWFromFile(file, "rb");
	surf = IMG_Load(file);
	if (!surf)
	{
		printf("IMG error: %s\n", IMG_GetError());
		SDL_FreeSurface(surf);
		free(file);
		gfx.wid = 0;
		gfx.hgt = 0;
		SDL_FreeRW(dm->rwops);
		error_out(GFX_ERROR, dm);
	}
	gfx.tex = SDL_ConvertSurfaceFormat(surf, dm->img.tex->format->format, 0);
	SDL_FreeSurface(surf);
	gfx.wid = gfx.tex->w;
	gfx.hgt = gfx.tex->h;
	gfx.data = (Uint32*)gfx.tex->pixels;
	free(file);
	SDL_FreeRW(dm->rwops);
	return (gfx);
}

/*
**	i = 15-23 for the foes.
*/

void	comp_foe(t_doom *dm, char *bpath, int i)
{
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe0.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe1.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe2.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe4.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe5.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe6.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe7.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe8.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "SpriteSheets/GreyDragon.xpm"), 384, 384);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "misc/icon.xpm"), 157, 157);
	dm->gfxcount = i;
	if (i != GFXCOUNT)
		error_out(GFX_ERROR, dm);
}

/*
** 7-14 second set
*/

void	comp_hud_gfx(t_doom *dm, char *bpath, int i)
{
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "misc/spawn.xpm"), 128, 128);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "hud/notifdown.xpm"), 441, 57);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "hud/options.xpm"), 540, 720);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "foe/foe3.xpm"), 564, 396);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "hud/btlmenu.xpm"), 221, 312);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "hud/btlsel.xpm"), 221, 312);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "hud/pcturn.xpm"), 354, 95);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "hud/pcsel.xpm"), 354, 95);
	dm->gfx[i++] = gfx_get(dm, ft_strjoin(bpath, "hud/mainmenu.xpm"), 1080, 720);
	//free(bpath);
	//dm->gfxcount = i;
	comp_foe(dm, bpath, i);
}

/*
** 0-6 first set
*/

void	comp_gfx(t_doom *dm, int i)
{
	char	*bpath;
	char	*path;

	dm->tile += 48;
	path = SDL_GetBasePath();
	//bpath = "C:\\Users\\alexn\\Desktop\\All-things-coding\\WinDoom\\gfx\\";
	bpath = ft_strjoin(path, "gfx/");
	if (!(dm->gfx = (t_gfx*)malloc(sizeof(t_gfx) * GFXCOUNT)))
		error_out(MEM_ERROR, dm);
	dm->gfx[i++] = gfx_get(dm, ft_quadjoin(bpath, (char*)&dm->tile, "/sky.xpm", ""), 1080, 360);
	dm->gfx[i++] = gfx_get(dm, ft_quadjoin(bpath, (char*)&dm->tile, "/floor.xpm", ""), 128, 128);
	dm->gfx[i++] = gfx_get(dm, ft_quadjoin(bpath, (char*)&dm->tile, "/wall.xpm", ""), 128, 128);
	dm->gfx[i++] = gfx_get(dm, ft_quadjoin(bpath, (char*)&dm->tile, "/stairu.xpm", ""), 128, 128);
	dm->gfx[i++] = gfx_get(dm, ft_quadjoin(bpath, (char*)&dm->tile, "/staird.xpm", ""), 128, 128);
	dm->gfx[i++] = gfx_get(dm, ft_quadjoin(bpath, (char*)&dm->tile, "/door.xpm", ""), 128, 128);
	dm->gfx[i++] = gfx_get(dm, ft_quadjoin(bpath, (char*)&dm->tile, "/warp.xpm", ""), 128, 128);
	comp_hud_gfx(dm, bpath, i);
	dm->tile -= 48;
	SDL_free(path);
	free(bpath);
}
