/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:09:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/23 14:41:04 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_slidertext(t_doom *dm, t_editor *le)
{
	set_ftext(dm, ft_strfjoin(le->opt[0], ft_itoa(le->options[0])),
		(int[3]){25, 770, 0xE71313}, 0.8);
	set_ftext(dm, ft_strfjoin(le->opt[1], ft_itoa(le->options[1])),
		(int[3]){100, 770, 0xE71313}, 0.8);
	set_ftext(dm, ft_strfjoin(le->opt[2], ft_itoa(le->options[2])),
		(int[3]){175, 770, 0xE71313}, 0.8);
	set_ftext(dm, ft_strfjoin(le->opt[3], ft_itoa(le->options[3])),
		(int[3]){250, 770, 0xE71313}, 0.8);
	set_ftext(dm, ft_strfjoin(le->opt[4], ft_itoa(le->options[4])),
		(int[3]){325, 770, 0xE71313}, 0.8);
	set_text(dm, le->opt[5 + le->cur], (int[3]){657, 790, 0xE71313}, 1);
	if (le->cur == 2)
		set_text(dm, le->opt[11], (int[3]){720, 790, 0xE71313}, 0.5);
	else if (le->cur == 4)
		set_text(dm, le->opt[10], (int[3]){720, 790, 0xE71313}, 0.5);
}

void	render_editor(t_doom *dm, t_editor *le)
{
	draw_bg(dm, dm->gfx[23]);
	draw_level_screen(dm, le, 0, 0);
	draw_layerspr(dm, le, 0, 0);
	draw_editor_cursor(dm, le, dm->winw * 0.5, 0);
	if (le->tab == 0)
	{
		draw_sliders(dm, le, dm->winw * 0.5, 0);
		draw_blk_select(dm, le, 0, 0);
		draw_slidertext(dm, le);
	}
	else
	{
		draw_sliders(dm, le, dm->winw * 0.5, 0);
		draw_sprselect(dm, le, 750, 3);
		draw_slidertext(dm, le);
	}
	SDL_RenderPresent(dm->rend);
}

void	editor_main(t_doom *dm)
{
	t_editor	*le;

	if (!(le = (t_editor*)malloc(sizeof(t_editor))))
		error_out(MEM_ERROR, dm);
	editor_defaults(le, dm);
	//opt_text(le);
	SDL_SetWindowSize(dm->win, 1500, 750);
	while (!le->quit)
	{
		key_state_editor(le, dm);
		render_editor(dm, le);
		dm->fps++;
	}
	dm->area[(int)dm->spw.z][(int)dm->spw.y][(int)dm->spw.x].b = 1;
	SDL_SetWindowSize(dm->win, WINX, WINY);
	free(le);
	dm->pos = dm->spw;
	if (le->quit == 2)
		error_out(FINE, dm);
	validate_map(dm, -1, -1, (t_block){.b = 2, .lgt = 15, .pln = 15, .pt = 0});
}
