/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:03:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/30 16:24:10 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_bars(t_doom *wlf, int y, int x, int pc)
{
	int		sy;
	int		sx;
	Uint32	color;

	while (++pc < 5)
	{
		sy = (pc * (wlf->winh / 10));
		sx = wlf->winw / 2;
		y = -1;
		while (++y < wlf->winh / 10)
		{
			x = -1;
			while (++x < wlf->winw / 2 * (*wlf->options[pc] / wlf->maxvalue[pc]) && x < wlf->winw)
			{
				if (0xffffcd38 + x > 0xffffcdff)
					color = 0xffffcdff;
				else
					color = 0xffffcd38 + x;
				wlf->img.data[wlf->winw * (y + sy) + (x + sx)] = color;
			}
			while (++x < wlf->winw / 2 && x < wlf->winw)
				wlf->img.data[wlf->winw * (y + sy) + (x + sx)] = 0xff000000;
		}
	}
}

void	options_menu_create(t_doom *wlf)
{
	wlf->options[0] = &wlf->isfpscap;
	wlf->maxvalue[0] = -1.0;
	wlf->options[1] = &wlf->fpscap;
	wlf->maxvalue[1] = 180.0;
	wlf->options[2] = &wlf->isoutline;
	wlf->maxvalue[2] = -1.0;
	wlf->options[3] = &wlf->buffer;
	wlf->maxvalue[3] = 100.0;
	wlf->options[4] = &wlf->texbool;
	wlf->maxvalue[4] = -1.0;
}

void	options_menu(t_doom *wlf)
{
	options_menu_create(wlf);
	draw_menu(wlf, 0, 0);
	draw_bars(wlf, -1, -1, -1);
	wlf->tex = SDL_CreateTextureFromSurface(wlf->rend, wlf->img.tex);
	SDL_RenderCopy(wlf->rend, wlf->tex, NULL, NULL);
	SDL_RenderPresent(wlf->rend);
	wlf->fps++;
}