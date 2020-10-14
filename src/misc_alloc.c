/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:20:26 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/07 13:41:20 by tbergkul         ###   ########.fr       */
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
