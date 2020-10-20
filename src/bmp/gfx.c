/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/20 14:48:49 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

t_img	init_image(t_doom *dm)
{
	t_img	image;

	if (!(image.tex = SDL_GetWindowSurface(dm->win)))
		error_out(WIN_ERROR, dm);
	image.img = SDL_CreateTextureFromSurface(dm->rend, image.tex);
	image.data = (Uint32*)image.tex->pixels;
	dm->winb = 1;
	dm->winh = image.tex->h;
	dm->winw = image.tex->w;
	return (image);
}

void	comp_spritesheets(t_doom *dm, char *bpath)
{
	dm->gfx[25] = read_bmp(ft_strjoin(bpath, "hud/crosshair.bmp"), 0, 0);
	dm->gfx[27] = read_bmp(ft_strjoin(bpath, "hud/gun.bmp"), 0, 0);
	dm->gfx[28] = read_bmp(ft_strjoin(bpath, "hud/health.bmp"), 0, 0);
	dm->gfx[29] = read_bmp(ft_strjoin(bpath, "hud/inventory.bmp"), 0, 0);
	dm->gfx[30] = read_bmp(ft_strjoin(bpath, "obj/keycard.bmp"), 0, 0);
	dm->gfx[33] = read_bmp(ft_strjoin(bpath, "misc/alpha.bmp"), 0, 0);
	dm->gfx[34] = read_bmp(ft_strjoin(bpath, "obj/money.bmp"), 0, 0);
	dm->gfx[35] = read_bmp(ft_strjoin(bpath, "obj/plant.bmp"), 0, 0);
	dm->gfx[36] = read_bmp(ft_strjoin(bpath, "obj/pistol.bmp"), 0, 0);
	dm->gfx[37] = read_bmp(ft_strjoin(bpath, "obj/chest.bmp"), 0, 0);
	dm->gfx[38] = read_bmp(ft_strjoin(bpath, "misc/goldore.bmp"), 0, 0);
	dm->gfx[39] = read_bmp(ft_strjoin(bpath, "misc/handlerr.bmp"), 0, 0);
	dm->gfx[40] = read_bmp(ft_strjoin(bpath, "misc/handlerl.bmp"), 0, 0);
	dm->gfx[41] = read_bmp(ft_strjoin(bpath, "misc/handlegr.bmp"), 0, 0);
	dm->gfx[42] = read_bmp(ft_strjoin(bpath, "misc/handlegl.bmp"), 0, 0);
}

/*
**	charizard 16
**	pokemon trainer 17
**	dragon 18
**	aggron 19
**	woman 20
**	greenguy 21
**	brownguy 22
*/

void	comp_foe(t_doom *dm, char *bpath)
{
	dm->gfx[16] = read_bmp(ft_strjoin(bpath, "foe/foe1.bmp"), 0, 0);
	dm->gfx[17] = read_bmp(ft_strjoin(bpath, "foe/foe2.bmp"), 0, 0);
	dm->gfx[18] = read_bmp(ft_strjoin(bpath, "foe/foe3.bmp"), 0, 0);
	dm->gfx[19] = read_bmp(ft_strjoin(bpath, "foe/foe4.bmp"), 0, 0);
	dm->gfx[20] = read_bmp(ft_strjoin(bpath, "foe/foe5.bmp"), 0, 0);
	dm->gfx[21] = read_bmp(ft_strjoin(bpath, "foe/foe6.bmp"), 0, 0);
	dm->gfx[22] = read_bmp(ft_strjoin(bpath, "foe/foe7.bmp"), 0, 0);
	dm->gfx[23] = read_bmp(ft_strjoin(bpath, "misc/sky.bmp"), 0, 0);
	dm->gfx[24] = read_bmp(ft_strjoin(bpath, "foe/projectile.bmp"), 0, 0);
	comp_spritesheets(dm, bpath);
}

void	comp_hud_gfx(t_doom *dm, char *bpath)
{
	dm->gfx[7] = read_bmp(ft_strjoin(bpath, "misc/spawn.bmp"), 0, 0);
	//dm->gfx[8] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile,
	//	"/warp.bmp", ""), 0, 0);
	dm->gfx[9] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[10] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[11] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[12] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[13] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[14] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[15] = read_bmp(ft_strjoin(bpath, "hud/mainmenu.bmp"), 0, 0);
	comp_foe(dm, bpath);
}

void	comp_gfx(t_doom *dm)
{
	char	*bpath;
	char	*path;
	t_gfx	pack;

	dm->tile += 48;
	path = SDL_GetBasePath();
	bpath = ft_strjoin(path, "gfx/");
	if (!(dm->gfx = (t_gfx*)malloc(sizeof(t_gfx) * GFXCOUNT)))
		error_out(MEM_ERROR, dm);
	pack = read_bmp(ft_quadjoin(bpath, "tex", (char*)&dm->tile, ".bmp"), 0, 0);
	dm->gfx[0] = read_bmp(ft_strjoin(bpath, "misc/end.bmp"), 0, 0);
	dm->gfx[1] = memcpy_gfx(pack, (int[2]){0, 256}, (int[2]){128, 128});
	dm->gfx[2] = memcpy_gfx(pack, (int[2]){0, 0}, (int[2]){128, 128});
	dm->gfx[3] = memcpy_gfx(pack, (int[2]){128, 0}, (int[2]){128, 128});
	dm->gfx[4] = memcpy_gfx(pack, (int[2]){0, 128}, (int[2]){128, 128});
	dm->gfx[5] = memcpy_gfx(pack, (int[2]){128, 256}, (int[2]){128, 128});
	dm->gfx[6] = memcpy_gfx(pack, (int[2]){128, 128}, (int[2]){128, 128});
	dm->gfx[8] = memcpy_gfx(pack, (int[2]){0, 384}, (int[2]){128, 128});
	free(pack.data);
	comp_hud_gfx(dm, bpath);
	dm->tile -= 48;
	SDL_free(path);
	free(bpath);
}
