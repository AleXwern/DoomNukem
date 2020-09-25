/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 12:42:17 by anystrom         ###   ########.fr       */
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
**	i = 25-32 for the following SpriteSheets.
*/

void	comp_spritesheets(t_doom *dm, char *bpath, int i)
{
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/crosshair.bmp"), 0, 0);//25
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/GreyDragon.bmp"), 0, 0);//26
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/gun.bmp"), 0, 0);//27
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "hud/health.bmp"), 0, 0);//28
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/inventory.bmp"), 0, 0);//29
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/keycard.bmp"), 0, 0);//30
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/numbers.bmp"), 0, 0);//31
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/PokemonTrainer.bmp"), 0, 0);//32
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/alpha.bmp"), 0, 0);//33
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foeF0.bmp"), 0, 0);//34
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foeF1.bmp"), 0, 0);//35
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/pistol.bmp"), 0, 0);//36
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "SpriteSheets/chest.bmp"), 0, 0);//37
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/goldore.bmp"), 0, 0);//38
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/keycardreaderredright.bmp"), 0, 0);//39
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/keycardreaderredleft.bmp"), 0, 0);//40
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/keycardreadergreenright.bmp"), 0, 0);//41
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/keycardreadergreenleft.bmp"), 0, 0);//42
	//dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/handle.bmp"), 0, 0);
	dm->gfxcount = i;
	if (i != GFXCOUNT)
		error_out(GFX_ERROR, dm);
}

/*
**	i = 15-24 for the foes.
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
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "foe/foeP.bmp"), 0, 0);
	comp_spritesheets(dm, bpath, i);
}

/*
** 7-15 second set
*/

void	comp_hud_gfx(t_doom *dm, char *bpath, int i)
{
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/spawn.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/handle.bmp"), 0, 0);
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
	dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/sky.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/floor.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/wall.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/stairu.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/staird.bmp", ""), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/door.bmp", ""), 0, 0);
	//dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/warp.bmp", ""), 0, 0);
	//dm->gfx[i++] = read_bmp(ft_strjoin(bpath, "misc/glass.bmp"), 0, 0);
	dm->gfx[i++] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile, "/glass.bmp", ""), 0, 0);
	comp_hud_gfx(dm, bpath, i);
	dm->tile -= 48;
	SDL_free(path);
	free(bpath);
}
