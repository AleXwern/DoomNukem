/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:23:46 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/10 11:32:58 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_main_menu(t_doom *wlf, int x, int y, int cur)
{
	int		gy;
	int		gx;

	gy = -1;
	//printf("%#010x\n", wlf->gfx[15].data[wlf->gfx[15].wid * 0 + 0]);
	while (++gy < wlf->winh)
	{
		y = gy * (wlf->gfx[15].hgt / (double)wlf->winh);
		gx = -1;
		while (++gx < wlf->winw)
		{
			x = gx * (wlf->gfx[15].wid / ((double)wlf->winw));
			if (gy > (cur * wlf->winh / 7) + wlf->winh / 4 && gy < ((cur + 1) * wlf->winh / 7) + wlf->winh / 4)
				wlf->img.data[wlf->winw * gy + gx] = wlf->gfx[15].data[wlf->gfx[15].wid * y + x] + 0x00252525;
			else if (wlf->gfx[15].data[wlf->gfx[15].wid * y + x] == 0xffff00ff || wlf->gfx[15].data[wlf->gfx[15].wid * y + x] == 0x00ff00ff)
				x += 0;
			else
				wlf->img.data[wlf->winw * gy + gx] = wlf->gfx[15].data[wlf->gfx[15].wid * y + x];
		}
	}
}

void	bg_render(t_doom *wlf)
{
	int	x;

	x = 0;
	if (wlf->trx < 0)
		wlf->trx = 1;
	while (x < wlf->trx)
	{
		wlf->data_r[x] = *wlf;
		wlf->data_r[x].x = x;
		wlf->threads[x] = SDL_CreateThread(renthread, "Thread", (void*)&wlf->data_r[x]);
		x++;
	}
	while (--x >= 0)
	{
		if (wlf->threads[x] == NULL)
			ft_putendl("Thread failure.");
		else
			SDL_WaitThread(wlf->threads[x], NULL);
	}
	wlf->fps++;
}

void	main_menu(t_doom *wlf)
{
	bg_render(wlf);
	draw_main_menu(wlf, 0, 0, wlf->sel);
	//draw_bars(wlf, -1, -1, -1);
	//wlf->tex = SDL_CreateTextureFromSurface(wlf->rend, wlf->img.tex);
	//SDL_RenderCopy(wlf->rend, wlf->tex, NULL, NULL);
	//SDL_UpdateWindowSurface(wlf->win);
	SDL_RenderPresent(wlf->rend);
	mouse_move(2, 0, wlf);
	wlf->fps++;
	wlf->keyck(wlf);
}