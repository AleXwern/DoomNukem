/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:09:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:32:13 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	defaults(t_editor *le, t_doom *dm)
{
	ft_bzero(le, sizeof(t_editor));
	dm->area[(int)dm->spawn.z][(int)dm->spawn.y][(int)dm->spawn.x] = 7;
	le->blk = 2;
	le->options[0] = dm->width;
	le->options[1] = dm->height;
	le->options[2] = dm->mxflr;
	le->options[3] = 2;
	le->options[4] = dm->tile;
	le->maxval[0] = 25.0;
	le->maxval[1] = 25.0;
	le->maxval[2] = 9.0;
	le->maxval[3] = dm->mxflr - 1;
	le->maxval[4] = 6.0;
	le->minval[0] = 5;
	le->minval[1] = 5;
	le->minval[2] = 0;
	le->minval[3] = 0;
	le->minval[4] = 1;
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
	dm->tile = le->options[4];
	destroy_gfx(dm, -1);
	comp_gfx(dm, 0);
	free(le);
	dm->pos = dm->spawn;
}