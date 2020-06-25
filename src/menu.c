/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:03:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/25 15:28:31 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	options_menu(t_doom *wlf)
{
	draw_gfx(wlf, wlf->gfx[9], 0, 0);
	wlf->tex = SDL_CreateTextureFromSurface(wlf->rend, wlf->img.tex);
	SDL_RenderCopy(wlf->rend, wlf->tex, NULL, NULL);
	SDL_RenderPresent(wlf->rend);
}