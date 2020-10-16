/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:09:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/16 14:15:58 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
** 0 - floor
** 1 - light
** 2 - plane type
** 3 - block thickness
** 4 - metadata
*/
void	defaults(t_editor *le, t_doom *dm)
{
	ft_bzero(le, sizeof(t_editor));
	dm->area[(int)dm->spw.z][(int)dm->spw.y][(int)dm->spw.x].b = 7;
	le->blk = 2;
	le->options[0] = 2;
	le->options[1] = 15;
	le->options[2] = 0;
	le->options[3] = 1;
	le->options[4] = 0;
	le->maxval[0] = dm->mxflr - 1;
	le->maxval[1] = 15.0;
	le->maxval[2] = 14.0;
	le->maxval[3] = 15.0;
	le->maxval[4] = 8.0;
	le->minval[0] = 0;
	le->minval[1] = 0;
	le->minval[2] = 0;
	le->minval[3] = 1;
	le->minval[4] = 0;
}

void	opt_text(t_editor *le)
{
	le->opt[0] = "floor";
	le->opt[1] = "lighting";
	le->opt[2] = "plane type";
	le->opt[3] = "block thickness";
	le->opt[4] = "meta";
	le->opt[5] = "lower floor to the right";
	le->opt[6] = "lighter to the right";
	le->opt[7] = "full  z   y   x\n     u d n s w e";
	le->opt[8] = "thicker to the right";
	le->opt[9] = "paintings";
	le->opt[10] = "1 w  2 n  3 e  4 s  5 keyr  6 keyg  7 heal  8 kill";
}

void	draw_slidertext(t_doom *dm, t_editor *le)
{
	set_text(dm, le->opt[0], (int[3]){25, 1065, 0xE71313}, 0.8);
	set_text(dm, le->opt[1], (int[3]){100, 1035, 0xE71313}, 0.8);
	set_text(dm, le->opt[2], (int[3]){175, 1015, 0xE71313}, 0.8);
	set_text(dm, le->opt[3], (int[3]){250, 970, 0xE71313}, 0.8);
	set_text(dm, le->opt[4], (int[3]){325, 1075, 0xE71313}, 0.8);
	set_text(dm, le->opt[5 + le->cur], (int[3]){550, 790, 0xE71313}, 1);
	if (le->cur == 4)
		set_text(dm, le->opt[10], (int[3]){590, 790, 0xE71313}, 0.5);
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
	opt_text(le);
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
	dm->pos = dm->spw;
	if (le->quit == 2)
		error_out(FINE, dm);
	validate_map(dm, -1, -1, (t_block){.b = 2, .lgt = 15, .pln = 15, .pt = 0});
}
