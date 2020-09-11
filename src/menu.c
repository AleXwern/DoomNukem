/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:03:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/11 13:53:57 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_bars(t_doom *dm, int y, int x, int pc)
{
	int		sy;
	int		sx;
	Uint32	color;
	Uint32	black;

	while (++pc < 10 + dm->minopt)
	{
		sy = ((pc - dm->minopt) * (dm->winh / 10));
		sx = dm->winw / 2;
		y = 0;
		while (++y < dm->winh / 10 - 1)
		{
			x = -1;
			*dm->options[pc] = abs(*dm->options[pc]);
			while (++x < dm->winw / 2 * (*dm->options[pc] / dm->maxvalue[pc]) && x < dm->winw)
			{
				if (0xffffcd38 + x > 0xffffcdff)
					color = 0xffffcdff;
				else
					color = 0xffffcd38 + x;
				dm->img.data[dm->winw * (y + sy) + (x + sx)] = color;
			}
			while (++x < dm->winw / 2 + 1)
			{
				if (x < (0xff * 2))
					black = 0xff000000 + (x / 2 * 0x00010000) + (x / 2 * 0x00000100) + (x / 2);
				else
					black = 0xffffffff;
				dm->img.data[dm->winw * (y + sy) + (x + sx - 1)] = black;
			}
		}
	}
}

void	options_menu_create(t_doom *dm)
{
	dm->options[0] = &dm->isfpscap;
	dm->maxvalue[0] = 1.0;
	dm->optext[0] = "fps cap";
	dm->options[1] = &dm->fpscap;
	dm->maxvalue[1] = 180.0;
	dm->optext[1] = "fps cap amount";
	dm->options[2] = &dm->isoutline;
	dm->maxvalue[2] = 1.0;
	dm->optext[2] = "outlines";
	dm->options[3] = &dm->buffer;
	dm->maxvalue[3] = 100.0;
	dm->optext[3] = "framebuffer";
	dm->options[4] = &dm->texbool;
	dm->maxvalue[4] = 1.0;
	dm->optext[4] = "textures";
	dm->options[5] = &dm->isgravity;
	dm->maxvalue[5] = 1.0;
	dm->optext[5] = "gravity";
	dm->options[6] = &dm->shift;
	dm->maxvalue[6] = 15.0;
	dm->optext[6] = "lighting";
	dm->options[7] = &dm->ismenu;
	dm->maxvalue[7] = 1.0;
	dm->optext[7] = "options menu";
	dm->options[8] = &dm->tile;
	dm->maxvalue[8] = 6.0;
	dm->optext[8] = "texturepack";
	dm->options[9] = &dm->volume;
	dm->maxvalue[9] = 128;
	dm->optext[9] = "volume";
	dm->options[10] = &dm->hp;
	dm->maxvalue[10] = 5;
	dm->optext[10] = "health";
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
	options_menu_create(dm);
	draw_menu(dm, 0, 0, dm->cur - dm->minopt);
	draw_bars(dm, -1, -1, -1);
	menu_text(dm, dm->minopt, -1);
	SDL_RenderPresent(dm->rend);
	dm->fps++;
}
