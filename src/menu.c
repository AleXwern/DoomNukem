/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:03:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/20 15:11:27 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_bars2(t_doom *dm, int y, int x)
{
	while (++x < dm->winw / 2 + 1)
	{
		if (x < (0xff * 2))
			dm->black = 0xff000000 + (x / 2 * 0x00010000)
			+ (x / 2 * 0x00000100) + (x / 2);
		else
			dm->black = 0xffffffff;
		dm->img.data[dm->winw * (y + dm->sy) + (x + dm->sx - 1)] = dm->black;
	}
}

void	draw_bars(t_doom *dm, int y, int x, int pc)
{
	t_uint32	color;

	while (++pc < 10 + dm->minopt)
	{
		dm->sy = ((pc - dm->minopt) * (dm->winh / 10));
		if (dm->sy < 0)
			dm->sy = 0;
		dm->sx = dm->winw / 2;
		y = 0;
		while (++y < dm->winh / 10 - 1)
		{
			x = -1;
			*dm->options[pc] = abs(*dm->options[pc]);
			while (++x < dm->winw / 2 * (*dm->options[pc]
				/ dm->maxvalue[pc]) && x < dm->winw)
			{
				if (0xffffcd38 + x > 0xffffcdff)
					color = 0xffffcdff;
				else
					color = 0xffffcd38 + x;
				dm->img.data[dm->winw * (y + dm->sy) + (x + dm->sx)] = color;
			}
			draw_bars2(dm, y, x);
		}
	}
}

void	menu_text(t_doom *dm, int opt, int y)
{
	char	*val;

	while (opt < 10 + dm->minopt)
	{
		y = (dm->winh / 10) * (opt - dm->minopt) + 20;
		val = ft_itoa(*dm->options[opt]);
		set_text(dm, dm->optext[opt], (int[3]){y, 20, 0}, 1);
		set_text(dm, val, (int[3]){y, dm->winw / 2 + 20, 0x1773e3}, 1);
		free(val);
		opt++;
	}
}

void	options_menu(t_doom *dm)
{
	static int i;

	options_menu_create(dm);
	draw_menu(dm, 0, 0, dm->cur - dm->minopt);
	draw_bars(dm, 0, -1, -1);
	menu_text(dm, dm->minopt, -1);
	SDL_RenderPresent(dm->rend);
	i++;
	dm->fps++;
}
