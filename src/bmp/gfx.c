/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/20 16:11:00 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void		comp_spritesheets(t_doom *dm, t_gfx pack, char *bpath)
{
	/*//dm->gfx[25] = read_bmp(ft_strjoin(bpath, "hud/crosshair.bmp"), 0, 0);
	dm->gfx[27] = read_bmp(ft_strjoin(bpath, "hud/gun.bmp"), 0, 0);
	//dm->gfx[28] = read_bmp(ft_strjoin(bpath, "hud/health.bmp"), 0, 0);
	//dm->gfx[29] = read_bmp(ft_strjoin(bpath, "hud/inventory.bmp"), 0, 0);
	dm->gfx[30] = read_bmp(ft_strjoin(bpath, "obj/keycard.bmp"), 0, 0);
	//dm->gfx[33] = read_bmp(ft_strjoin(bpath, "misc/alpha.bmp"), 0, 0);
	dm->gfx[34] = read_bmp(ft_strjoin(bpath, "obj/money.bmp"), 0, 0);
	//dm->gfx[35] = read_bmp(ft_strjoin(bpath, "obj/plant.bmp"), 0, 0);
	//dm->gfx[36] = read_bmp(ft_strjoin(bpath, "obj/pistol.bmp"), 0, 0);
	//dm->gfx[37] = read_bmp(ft_strjoin(bpath, "obj/chest.bmp"), 0, 0);
	//dm->gfx[38] = read_bmp(ft_strjoin(bpath, "misc/goldore.bmp"), 0, 0);
	dm->gfx[39] = read_bmp(ft_strjoin(bpath, "misc/handlerr.bmp"), 0, 0);
	dm->gfx[40] = read_bmp(ft_strjoin(bpath, "misc/handlerl.bmp"), 0, 0);
	dm->gfx[41] = read_bmp(ft_strjoin(bpath, "misc/handlegr.bmp"), 0, 0);
	dm->gfx[42] = read_bmp(ft_strjoin(bpath, "misc/handlegl.bmp"), 0, 0);*/
	//NEW ONES
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

void		comp_foe(t_doom *dm, t_gfx pack, char *bpath)
{
	dm->gfx[16] = memcpy_gfx(pack, (int[2]){0, 0}, (int[2]){148, 112});
	dm->gfx[17] = memcpy_gfx(pack, (int[2]){0, 112}, (int[2]){148, 112});
	dm->gfx[18] = memcpy_gfx(pack, (int[2]){0, 224}, (int[2]){148, 112});
	dm->gfx[19] = memcpy_gfx(pack, (int[2]){0, 336}, (int[2]){148, 112});
	dm->gfx[20] = memcpy_gfx(pack, (int[2]){0, 448}, (int[2]){148, 112});
	dm->gfx[21] = memcpy_gfx(pack, (int[2]){0, 560}, (int[2]){148, 112});
	dm->gfx[22] = memcpy_gfx(pack, (int[2]){0, 672}, (int[2]){148, 112});
	dm->gfx[23] = memcpy_gfx(pack, (int[2]){308, 1080}, (int[2]){360, 1080});
	dm->gfx[24] = memcpy_gfx(pack, (int[2]){61, 785}, (int[2]){52, 52}); //ammo has issues
	comp_spritesheets(dm, pack, bpath);
}

void		comp_hud_gfx(t_doom *dm, char *bpath)
{
	t_gfx	pack;

	pack = read_bmp(ft_strjoin(bpath, "gfxpack.bmp"), 0, 0);
	dm->gfx[0] = memcpy_gfx(pack, (int[2]){0, 1366}, (int[2]){128, 128}); //end
	dm->gfx[7] = memcpy_gfx(pack, (int[2]){0, 1494}, (int[2]){128, 128}); //spawn
	dm->gfx[9] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[10] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[11] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[12] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[13] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[14] = read_bmp(ft_strjoin(bpath, "foe/wyvern1.bmp"), 0, 0); //NULL
	dm->gfx[15] = memcpy_gfx(pack, (int[2]){308, 0}, (int[2]){720, 1080});
	comp_foe(dm, pack, bpath);
	free(pack.data);
}

void		comp_gfx(t_doom *dm)
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
