/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:50:10 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/23 15:05:05 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	set_slider(t_editor *le, t_doom *dm, double x, int y)
{
	y = dm->event.motion.y / 75;
	if (dm->event.motion.x > 750 && y < 5)
	{
		x = 1.0 * (dm->event.motion.x - 750) / 750;
		le->options[y] = (le->maxval[y] + 1) * x;
		if (le->options[y] < le->minval[y])
			le->options[y] = le->minval[y];
		le->cur = y;
	}
}

void	draw_screen(t_editor *le, t_doom *dm, int x, int y)
{
	y = dm->event.motion.y / 30;
	x = dm->event.motion.x / 30;
	if (le->marea && dm->event.motion.x < 750)
	{
		if (!le->tab)
			draw_screen_more(le, dm, x, y);
		else
			set_sprite_tomap(le, dm, dm->event.motion.x, dm->event.motion.y);
	}
	else if (le->mcopy && dm->event.motion.x < 750)
	{
		if (y >= dm->height || x >= dm->width)
			return ;
		if (y < 0 || x < 0)
			return ;
		le->blk = dm->area[le->options[0]][y][x].b;
		le->options[1] = dm->area[le->options[0]][y][x].lgt;
		le->options[2] = dm->area[le->options[0]][y][x].pt;
		le->options[3] = dm->area[le->options[0]][y][x].pln;
		le->options[4] = dm->area[le->options[0]][y][x].meta;
	}
	else if (le->mslider)
		set_slider(le, dm, x, y);
}

void	check_area(t_editor *le, t_doom *dm, SDL_Event ev)
{
	if (ev.motion.x >= 0 && ev.motion.y >= 0 && ev.button.button == 1)
	{
		if (ev.motion.x < 750 && ev.motion.y < 750)
			le->marea = 1;
		else if (ev.motion.x < 1500 && ev.motion.y < 375)
			le->mslider = 1;
		else if (ev.motion.x < 1500 && ev.motion.y < 592 && le->tab == 0)
		{
			le->blk = ((ev.motion.x - 750) / 107);
			if (ev.motion.y > 485)
				le->blk += 7;
			le->mblock = 1;
			if (le->blk > BLK)
				le->blk = BLK;
		}
		else if (ev.motion.x < 1500 && ev.motion.y < 592 && le->tab == 1)
			grab_sprite(dm, le, ((ev.motion.x - 750) / 107) + 4);
	}
	else if (ev.motion.x >= 0 && ev.motion.y >= 0 && ev.button.button == 3)
		le->mcopy = 1;
}

void	editor_key_release(Uint32 key, t_editor *le, t_doom *dm)
{
	if (key == ESC)
		le->quit = 1;
	else if (key == DOWN)
		le->cur++;
	else if (key == UP)
		le->cur--;
	else if (key == KEY_S)
		save_file(dm, 0, "1s", -1);
	else if (key == KEY_ONE)
		le->tab = 0;
	else if (key == KEY_TWO)
		le->tab = 1;
	if (key == KEY_ONE || key == KEY_TWO)
		tab_change(le);
	if (le->cur > 4)
		le->cur = 0;
	if (le->cur < 0)
		le->cur = 4;
}

void	editor_key_press(Uint32 key, t_editor *le)
{
	if (key == LEFT)
		le->options[le->cur]--;
	else if (key == RIGHT)
		le->options[le->cur]++;
	else if (key == SPACE && le->options[le->cur] < le->maxval[le->cur])
		le->options[le->cur] = le->maxval[le->cur];
	else if (key == SPACE)
		le->options[le->cur] = le->minval[le->cur];
	if (le->options[le->cur] > le->maxval[le->cur])
		le->options[le->cur] = le->maxval[le->cur];
	if (le->options[le->cur] < le->minval[le->cur])
		le->options[le->cur] = le->minval[le->cur];
}
