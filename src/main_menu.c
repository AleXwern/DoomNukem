/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:23:46 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:34:54 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_main_menu(t_doom *dm, int x, int y, int cur)
{
	int		gy;
	int		gx;

	gy = -1;
	//printf("%#010x\n", dm->gfx[15].data[dm->gfx[15].wid * 0 + 0]);
	while (++gy < dm->winh)
	{
		y = gy * (dm->gfx[15].hgt / (double)dm->winh);
		gx = -1;
		while (++gx < dm->winw)
		{
			x = gx * (dm->gfx[15].wid / ((double)dm->winw));
			if (gy > (cur * dm->winh / 7) + dm->winh / 4 && gy < ((cur + 1) * dm->winh / 7) + dm->winh / 4)
				dm->img.data[dm->winw * gy + gx] = dm->gfx[15].data[dm->gfx[15].wid * y + x] + 0x00252525;
			else if (dm->gfx[15].data[dm->gfx[15].wid * y + x] == 0xffff00ff || dm->gfx[15].data[dm->gfx[15].wid * y + x] == 0x00ff00ff)
				x += 0;
			else
				dm->img.data[dm->winw * gy + gx] = dm->gfx[15].data[dm->gfx[15].wid * y + x];
		}
	}
}

void	bg_render(t_doom *dm)
{
	static int	x;

	//x = 0;
	if (dm->trx < 1)
		dm->trx = 1;
	while (x < dm->trx)
	{
		dm->data_r[x] = *dm;
		dm->data_r[x].x = x;
		dm->threads[x] = SDL_CreateThread(renthread, "Thread", (void*)&dm->data_r[x]);
		x++;
	}
	while (x > 0)
	{
		x--;
		if (dm->threads[x] == NULL)
			ft_putendl("Thread failure.");
		else
			SDL_WaitThread(dm->threads[x], NULL);
	}
	//SDL_RenderPresent(dm->rend);
	dm->fps++;
}

void	main_menu(t_doom *dm)
{
	bg_render(dm);
	draw_main_menu(dm, 0, 0, dm->sel);
	//draw_bars(dm, -1, -1, -1);
	//dm->tex = SDL_CreateTextureFromSurface(dm->rend, dm->img.tex);
	//SDL_RenderCopy(dm->rend, dm->tex, NULL, NULL);
	//SDL_UpdateWindowSurface(dm->win);
	SDL_RenderPresent(dm->rend);
	mouse_move(2, 0, dm);
	dm->fps++;
	dm->keyck(dm);
}