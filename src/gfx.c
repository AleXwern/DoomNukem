/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/26 13:22:34 by anystrom         ###   ########.fr       */
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
