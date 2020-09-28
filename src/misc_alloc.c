/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:36:54 by AleXwern          #+#    #+#             */
/*   Updated: 2020/09/28 12:36:54 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	free_vram(t_doom *dm)
{
	free(dm->threads);
	free(dm->data_r);
	free(dm->maparr);
	free(dm->wallarr);
}

void	alloc_vram(t_doom *dm)
{
	if (!(dm->maparr = (int*)ft_memalloc(sizeof(int) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->wallarr = (double*)ft_memalloc(sizeof(double) * dm->winw
			* dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->threads = (SDL_Thread**)ft_memalloc(sizeof(SDL_Thread*)
			* dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->data_r = (t_doom*)ft_memalloc(sizeof(t_doom) * dm->trx)))
		error_out(MEM_ERROR, dm);
}
