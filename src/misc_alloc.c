/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:20:26 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/20 15:30:24 by anystrom         ###   ########.fr       */
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

t_img		init_image(t_doom *dm)
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

void	free_vram(t_doom *dm)
{
	free(dm->threads);
	free(dm->data_r);
	free(dm->maparr);
	free(dm->wallarr);
	free(dm->window);
	free(dm->winarr);
}

void	alloc_vram(t_doom *dm)
{
	if (!(dm->maparr = (int*)ft_memalloc(sizeof(int) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->wallarr = (t_fpoint*)ft_memalloc(sizeof(t_fpoint) * dm->winw
			* dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->winarr = (t_fpoint*)ft_memalloc(sizeof(t_fpoint) * dm->winw
			* dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->threads = (SDL_Thread**)ft_memalloc(sizeof(SDL_Thread*)
			* dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->data_r = (t_doom*)ft_memalloc(sizeof(t_doom) * dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->window = (Uint32*)ft_memalloc(sizeof(Uint32) * dm->winw
			* dm->winh)))
		error_out(MEM_ERROR, dm);
}
