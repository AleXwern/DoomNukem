/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:09:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/10 13:09:35 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	defaults(t_editor *le, t_doom *dm)
{
	ft_bzero(le, sizeof(t_editor));
	le->options[0] = dm->width;
	le->options[1] = dm->height;
	le->options[2] = dm->mxflr;
	le->options[3] = 2;
	le->options[4] = dm->tile;
	le->maxval[0] = 35.0;
	le->maxval[1] = 35.0;
	le->maxval[2] = 35.0;
	le->maxval[3] = dm->mxflr - 1;
	le->maxval[4] = 6.0;
	le->minval[0] = 5;
	le->minval[1] = 5;
	le->minval[2] = 0;
	le->minval[3] = 0;
	le->minval[4] = 1;
	le->spawn.x = 2.51;
	le->spawn.y = 2.51;
	le->spawn.z = 2.5;
}

void	render_editor(t_doom *wlf, t_editor *le)
{
	draw_bg(wlf, wlf->gfx[0]);
	draw_level_screen(wlf, le, 0, 0);
	draw_sliders(wlf, le, wlf->winw * 0.5, 0);
	//draw_blocks(wlf, le);
	//wlf->tex = SDL_CreateTextureFromSurface(wlf->rend, wlf->img.tex);
	//SDL_RenderCopy(wlf->rend, wlf->tex, NULL, NULL);
	//SDL_UpdateWindowSurface(wlf->win);
	SDL_RenderPresent(wlf->rend);
	//mouse_move(2, 0, wlf);
	wlf->fps++;
	//wlf->keyck(wlf);
}

void	editor_main(t_doom *wlf)
{
	t_editor	*le;

	if (!(le = (t_editor*)malloc(sizeof(t_editor))))
		error_out(MEM_ERROR, wlf);
	defaults(le, wlf);
	//SDL_SetWindowResizable(wlf->win, SDL_FALSE);
	printf("Dim %d %d", wlf->width, wlf->height);
	while (!le->quit)
	{
		key_state_editor(le, wlf);
		render_editor(wlf, le);
	}
	//SDL_SetWindowResizable(wlf->win, SDL_TRUE);
	free(le);
}