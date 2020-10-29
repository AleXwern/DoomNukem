/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/29 14:22:49 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	Crosshair 25
**	GunAnimation 27
**	Health 28
**	Inventory 29
**	Keycard 30 --
**	Alpha 33
**	Money 34 --
**	Plant 35 --
**	Pistol 36 --
**	Chest 37 --
**	Goldore 38
**	HandleRR 39
**	HandleRL 40
**	HandleGR 41
**	HandleGL 42
*/

void		comp_spritesheets(t_doom *dm, t_gfx pack)
{
	dm->gfx[25] = memcpy_gfx(pack, (int[2]){0, 784}, (int[2]){50, 50});
	dm->gfx[27] = memcpy_gfx(pack, (int[2]){148, 0}, (int[2]){160, 2880});
	dm->gfx[28] = memcpy_gfx(pack, (int[2]){0, 834}, (int[2]){60, 122});
	dm->gfx[29] = memcpy_gfx(pack, (int[2]){0, 956}, (int[2]){120, 410});
	dm->gfx[30] = memcpy_gfx(pack, (int[2]){0, 2268}, (int[2]){140, 200});
	dm->gfx[33] = memcpy_gfx(pack, (int[2]){867, 1081}, (int[2]){27, 997});
	dm->gfx[34] = memcpy_gfx(pack, (int[2]){0, 2469}, (int[2]){103, 200});
	dm->gfx[35] = memcpy_gfx(pack, (int[2]){309, 2702}, (int[2]){292, 150});
	dm->gfx[36] = memcpy_gfx(pack, (int[2]){309, 2321}, (int[2]){272, 380});
	dm->gfx[37] = memcpy_gfx(pack, (int[2]){668, 1080}, (int[2]){198, 1180});
	dm->gfx[38] = memcpy_gfx(pack, (int[2]){0, 1623}, (int[2]){128, 128});
	dm->gfx[39] = memcpy_gfx(pack, (int[2]){0, 2139}, (int[2]){128, 128});
	dm->gfx[40] = memcpy_gfx(pack, (int[2]){0, 2010}, (int[2]){128, 128});
	dm->gfx[41] = memcpy_gfx(pack, (int[2]){0, 1881}, (int[2]){128, 128});
	dm->gfx[42] = memcpy_gfx(pack, (int[2]){0, 1752}, (int[2]){128, 128});
}

/*
**	charizard 16
**	pokemon trainer 17
**	dragon 18
**	aggron 19
**	woman 20
**	greenguy 21
**	brownguy 22
**	Sky 23
**	Projectile 24
*/

void		comp_foe(t_doom *dm, t_gfx pack)
{
	dm->gfx[16] = memcpy_gfx(pack, (int[2]){0, 0}, (int[2]){148, 112});
	dm->gfx[17] = memcpy_gfx(pack, (int[2]){0, 112}, (int[2]){148, 112});
	dm->gfx[18] = memcpy_gfx(pack, (int[2]){0, 224}, (int[2]){148, 112});
	dm->gfx[19] = memcpy_gfx(pack, (int[2]){0, 336}, (int[2]){148, 112});
	dm->gfx[20] = memcpy_gfx(pack, (int[2]){0, 448}, (int[2]){148, 112});
	dm->gfx[21] = memcpy_gfx(pack, (int[2]){0, 560}, (int[2]){148, 112});
	dm->gfx[22] = memcpy_gfx(pack, (int[2]){0, 672}, (int[2]){148, 112});
	dm->gfx[23] = memcpy_gfx(pack, (int[2]){308, 1080}, (int[2]){360, 1080});
	dm->gfx[24] = memcpy_gfx(pack, (int[2]){0, 2669}, (int[2]){52, 52});
	comp_spritesheets(dm, pack);
}

/*
**	End 0
**	Spawn 7
**	Jetpack 9 --
**
**
**
**
**
**	MainMenu 15
*/

void		comp_hud_gfx(t_doom *dm, t_gfx pack)
{
	dm->gfx[0] = memcpy_gfx(pack, (int[2]){0, 1366}, (int[2]){128, 128});
	dm->gfx[7] = memcpy_gfx(pack, (int[2]){0, 1494}, (int[2]){128, 128});
	dm->gfx[9] = memcpy_gfx(pack, (int[2]){581, 2260}, (int[2]){350, 200});
	dm->gfx[10] = memcpy_gfx(pack, (int[2]){895, 1081}, (int[2]){57, 342}); //smallicons
	dm->gfx[15] = memcpy_gfx(pack, (int[2]){308, 0}, (int[2]){720, 1080});
	comp_foe(dm, pack);
	free(pack.data);
}

void		comp_gfx(t_doom *dm)
{
	char	*bpath;
	char	*path;
	t_gfx	pack;

	path = SDL_GetBasePath();
	bpath = ft_strjoin(path, "gfx/gfxpack.bmp");
	pack = read_bmp(bpath, 0, 0);
	SDL_free(path);
	if (pack.data == NULL)
		error_out(GFX_ERROR, dm);
	if (!(dm->gfx = (t_gfx*)ft_memalloc(sizeof(t_gfx) * GFXCOUNT)))
		error_out(MEM_ERROR, dm);
	comp_texpack(dm);
	comp_hud_gfx(dm, pack);
}

void		comp_texpack(t_doom *dm)
{
	char	*path;
	t_gfx	pack;

	dm->tile += 48;
	path = SDL_GetBasePath();
	pack = read_bmp(ft_quadjoin(path, "gfx/tex", (char*)&dm->tile, ".bmp"), 0, 0);
	if (pack.data == NULL)
		error_out(GFX_ERROR, dm);
	dm->gfx[1] = memcpy_gfx(pack, (int[2]){0, 256}, (int[2]){128, 128});
	dm->gfx[2] = memcpy_gfx(pack, (int[2]){0, 0}, (int[2]){128, 128});
	dm->gfx[3] = memcpy_gfx(pack, (int[2]){128, 0}, (int[2]){128, 128});
	dm->gfx[4] = memcpy_gfx(pack, (int[2]){0, 128}, (int[2]){128, 128});
	dm->gfx[5] = memcpy_gfx(pack, (int[2]){128, 256}, (int[2]){128, 128});
	dm->gfx[6] = memcpy_gfx(pack, (int[2]){128, 128}, (int[2]){128, 128});
	dm->gfx[8] = memcpy_gfx(pack, (int[2]){0, 384}, (int[2]){128, 128});
	free(pack.data);
	dm->tile -= 48;
	SDL_free(path);
}
