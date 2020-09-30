/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:41:51 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/30 14:25:47 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	destroy_gfx(t_doom *dm, int i)
{
	while (++i < dm->gfxcount)
	{
		if (dm->gfx[i].wid > 0)
			free(dm->gfx[i].data);
	}
	free(dm->gfx);
}

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

void	comp_spritesheets(t_doom *dm, char *bpath, int i)
{
	dm->gfx[25] = read_bmp(ft_strjoin(bpath, "hud/crosshair.bmp"), 0, 0);
	dm->gfx[27] = read_bmp(ft_strjoin(bpath, "hud/gun.bmp"), 0, 0);
	dm->gfx[28] = read_bmp(ft_strjoin(bpath, "hud/health.bmp"), 0, 0);
	dm->gfx[29] = read_bmp(ft_strjoin(bpath, "hud/inventory.bmp"), 0, 0);
	dm->gfx[30] = read_bmp(ft_strjoin(bpath, "obj/keycard.bmp"), 0, 0);
	dm->gfx[33] = read_bmp(ft_strjoin(bpath, "misc/alpha.bmp"), 0, 0);
	dm->gfx[34] = read_bmp(ft_strjoin(bpath, "foe/foeF0.bmp"), 0, 0);
	dm->gfx[35] = read_bmp(ft_strjoin(bpath, "foe/foeF1.bmp"), 0, 0);
	dm->gfx[36] = read_bmp(ft_strjoin(bpath, "obj/pistol.bmp"), 0, 0);
	dm->gfx[37] = read_bmp(ft_strjoin(bpath, "obj/chest.bmp"), 0, 0);
	dm->gfx[38] = read_bmp(ft_strjoin(bpath, "misc/goldore.bmp"), 0, 0);
	dm->gfx[39] = read_bmp(ft_strjoin(bpath, "misc/handlerr.bmp"), 0, 0);
	dm->gfx[40] = read_bmp(ft_strjoin(bpath, "misc/handlerl.bmp"), 0, 0);
	dm->gfx[41] = read_bmp(ft_strjoin(bpath, "misc/handlegr.bmp"), 0, 0);
	dm->gfx[42] = read_bmp(ft_strjoin(bpath, "misc/handlegl.bmp"), 0, 0);
}

void	comp_foe(t_doom *dm, char *bpath, int i)
{
	dm->gfx[16] = read_bmp(ft_strjoin(bpath, "foe/foe1.bmp"), 0, 0);
	dm->gfx[17] = read_bmp(ft_strjoin(bpath, "foe/foe2.bmp"), 0, 0);
	dm->gfx[18] = read_bmp(ft_strjoin(bpath, "foe/foe3.bmp"), 0, 0);
	dm->gfx[19] = read_bmp(ft_strjoin(bpath, "foe/foe4.bmp"), 0, 0);
	dm->gfx[20] = read_bmp(ft_strjoin(bpath, "foe/foe5.bmp"), 0, 0);
	dm->gfx[21] = read_bmp(ft_strjoin(bpath, "foe/foe6.bmp"), 0, 0);
	dm->gfx[22] = read_bmp(ft_strjoin(bpath, "foe/foe7.bmp"), 0, 0);
	dm->gfx[23] = read_bmp(ft_strjoin(bpath, "foe/foe8.bmp"), 0, 0);
	dm->gfx[24] = read_bmp(ft_strjoin(bpath, "foe/projectile.bmp"), 0, 0);
	comp_spritesheets(dm, bpath, i);
}

void	comp_hud_gfx(t_doom *dm, char *bpath, int i)
{
	dm->gfx[7] = read_bmp(ft_strjoin(bpath, "misc/spawn.bmp"), 0, 0);
	dm->gfx[8] = read_bmp(ft_strjoin(bpath, "misc/handle.bmp"), 0, 0);
	dm->gfx[9] = read_bmp(ft_strjoin(bpath, "hud/options.bmp"), 0, 0);
	dm->gfx[10] = read_bmp(ft_strjoin(bpath, "foe/wyvern.bmp"), 0, 0);
	dm->gfx[11] = read_bmp(ft_strjoin(bpath, "hud/btlmenu.bmp"), 0, 0);
	dm->gfx[12] = read_bmp(ft_strjoin(bpath, "hud/btlsel.bmp"), 0, 0);
	dm->gfx[13] = read_bmp(ft_strjoin(bpath, "hud/pcturn.bmp"), 0, 0);
	dm->gfx[14] = read_bmp(ft_strjoin(bpath, "hud/pcsel.bmp"), 0, 0);
	dm->gfx[15] = read_bmp(ft_strjoin(bpath, "hud/mainmenu.bmp"), 0, 0);
	comp_foe(dm, bpath, i);
}

void	comp_gfx(t_doom *dm, int i)
{
	char	*bpath;
	char	*path;

	dm->tile += 48;
	path = SDL_GetBasePath();
	bpath = ft_strjoin(path, "gfx/");
	if (!(dm->gfx = (t_gfx*)malloc(sizeof(t_gfx) * GFXCOUNT)))
		error_out(MEM_ERROR, dm);
	dm->gfx[0] = read_bmp(ft_strjoin(bpath, "misc/sky.bmp"), 0, 0);
	dm->gfx[1] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile,
		"/floor.bmp", ""), 0, 0);
	dm->gfx[2] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile,
		"/wall.bmp", ""), 0, 0);
	dm->gfx[3] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile,
		"/stairu.bmp", ""), 0, 0);
	dm->gfx[4] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile,
		"/staird.bmp", ""), 0, 0);
	dm->gfx[5] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile,
		"/door.bmp", ""), 0, 0);
	dm->gfx[6] = read_bmp(ft_quadjoin(bpath, (char*)&dm->tile,
		"/glass.bmp", ""), 0, 0);
	comp_hud_gfx(dm, bpath, i);
	dm->tile -= 48;
	SDL_free(path);
	free(bpath);
}
