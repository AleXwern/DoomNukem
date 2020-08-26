/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/26 13:07:52 by anystrom         ###   ########.fr       */
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
			free(dm->gfx[i].data);
		}
	}
	free(dm->gfx);
}

t_img			init_image(t_doom *dm)
{
	t_img	image;

	if (!(image.tex = SDL_GetWindowSurface(dm->win)))
		error_out(WIN_ERROR, dm);
	image.img = SDL_CreateTextureFromSurface(dm->rend, image.tex);
	image.data = (Uint32*)image.tex->pixels;
	return (image);
}
/*
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
	char* temp = ft_itoa(sizeof(Uint32) * gfx.wid * gfx.hgt);
	temp = ft_strfjoin(temp, ft_strdup("\n"));
	temp = ft_strfjoin(ft_strdup("\n"), temp);
	write(dm->cur, temp, ft_strlen(temp));
	free(temp);
	temp = (char*)malloc(sizeof(Uint32) * x * y);
	ft_strncpy(temp, gfx.data, sizeof(Uint32) * x * y);
	temp = ft_replace(temp, '\n', '\t', sizeof(Uint32) * x * y);
	//write(dm->cur, temp, sizeof(Uint32) * gfx.wid * gfx.hgt);
	free(temp);
	//write(dm->cur, "\nZZZ\n", 5);
	return (gfx);
}*/

/*
**	i = 15-23 for the foes.
*/

void	comp_foe(t_doom *dm, char *bpath, int i)
{
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe0.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe1.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe2.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe4.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe5.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe6.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe7.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe8.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/GreyDragon.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/icon.bmp"), 0, 0);
	dm->gfxcount = i;
	if (i != GFXCOUNT)
		error_out(GFX_ERROR, dm);
}

/*
** 7-14 second set
*/

void	comp_hud_gfx(t_doom *dm, char *bpath, int i)
{
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/spawn.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "hud/notifdown.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "hud/options.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foe3.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "hud/btlmenu.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "hud/btlsel.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "hud/pcturn.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "hud/pcsel.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "hud/mainmenu.bmp"), 0, 0);
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
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/sky.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/floor.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/wall.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/stairu.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/staird.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/door.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/warp.bmp", ""), 0, 0);
	comp_hud_gfx(dm, bpath, i);
	dm->tile -= 48;
	SDL_free(path);
	free(bpath);
}
