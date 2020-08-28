/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:09:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/27 15:58:46 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	defaults(t_editor *le, t_doom *dm)
{
	ft_bzero(le, sizeof(t_editor));
	dm->area[(int)dm->spawn.z][(int)dm->spawn.y][(int)dm->spawn.x].b = 7;
	le->blk = 2;
	le->options[0] = 2;				//floor
	le->options[1] = 15;			//light
	le->options[2] = 0;				//plane type, NULL-ZYX, PN
	le->options[3] = 1;				//plane thickness
	le->options[4] = 0;				//metadata
	le->maxval[0] = dm->mxflr - 1;
	le->maxval[1] = 15.0;
	le->maxval[2] = 8.0;
	le->maxval[3] = 15.0;
	le->maxval[4] = 2.0;
	le->minval[0] = 0;
	le->minval[1] = 0;
	le->minval[2] = 0;
	le->minval[3] = 1;
	le->minval[4] = 0;
}

void	render_editor(t_doom *dm, t_editor *le)
{
	draw_bg(dm, dm->gfx[0]);
	draw_level_screen(dm, le, 0, 0);
	draw_editor_cursor(dm, le, dm->winw * 0.5, 0);
	draw_sliders(dm, le, dm->winw * 0.5, 0);
	draw_blk_select(dm, le, 0, 0);
	//dm->tex = SDL_CreateTextureFromSurface(dm->rend, dm->img.tex);
	//SDL_RenderCopy(dm->rend, dm->tex, NULL, NULL);
	//SDL_UpdateWindowSurface(dm->win);
	SDL_RenderPresent(dm->rend);
	//mouse_move(2, 0, dm);
	//dm->keyck(dm);
}

void	editor_main(t_doom *dm)
{
	t_editor	*le;

	if (!(le = (t_editor*)malloc(sizeof(t_editor))))
		error_out(MEM_ERROR, dm);
	defaults(le, dm);
	SDL_SetWindowSize(dm->win, 1500, 750);
	printf("Dim %d %d\n", dm->width, dm->height);
	while (!le->quit)
	{
		key_state_editor(le, dm);
		render_editor(dm, le);
		dm->fps++;
	}
	SDL_SetWindowSize(dm->win, WINX, WINY);
	free(le);
	dm->pos = dm->spawn;
}