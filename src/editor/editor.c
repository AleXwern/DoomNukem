/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:09:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/16 16:16:44 by tbergkul         ###   ########.fr       */
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
	le->maxval[4] = 7.0;
	le->minval[0] = 0;
	le->minval[1] = 0;
	le->minval[2] = 0;
	le->minval[3] = 1;
	le->minval[4] = 0;
}

void	draw_slidertext(t_doom *dm, t_editor *le)
{
	set_text(dm, "floor", (int[3]){25, 1065, 0xE71313}, 0.8);
	set_text(dm, "lighting", (int[3]){100, 1035, 0xE71313}, 0.8);
	set_text(dm, "blockstart", (int[3]){175, 1015, 0xE71313}, 0.8);
	set_text(dm, "block thickness", (int[3]){250, 970, 0xE71313}, 0.8);
	set_text(dm, "meta", (int[3]){325, 1075, 0xE71313}, 0.8);
	if (le->cur == 0)
		set_text(dm, "lower floor to the right", (int[3]){550, 790, 0xE71313}, 1);//m->winh - 200, dm->winw / 2 + 40
	else if (le->cur == 1)
		set_text(dm, "lighter to the right", (int[3]){550, 790, 0xE71313}, 1);
	else if (le->cur == 2)
		set_text(dm, "full  z   y   x\n     u d n s w e", (int[3]){550, 790, 0xE71313}, 1);
	else if (le->cur == 3)
		set_text(dm, "thicker to the right", (int[3]){550, 790, 0xE71313}, 1);
	else if (le->cur == 4)
	{
		set_text(dm, "paintings", (int[3]){550, 790, 0xE71313}, 1);
		set_text(dm, "1 w  2 n  3 e  4 s  5 empty  6 heal  7 kill", (int[3]){590, 790, 0xE71313}, 0.6);
	}
}

void	render_editor(t_doom *dm, t_editor *le)
{
	draw_bg(dm, dm->gfx[0]);
	draw_level_screen(dm, le, 0, 0);
	draw_editor_cursor(dm, le, dm->winw * 0.5, 0);
	draw_sliders(dm, le, dm->winw * 0.5, 0);
	draw_blk_select(dm, le, 0, 0);
	draw_slidertext(dm, le);
	SDL_RenderPresent(dm->rend);
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
	if (le->quit == 2)
		error_out(FINE, dm);
	validate_map(dm, -1, -1, (t_block){.b = 2, .lgt = 15, .meta = 0, .pt = 0});
}
