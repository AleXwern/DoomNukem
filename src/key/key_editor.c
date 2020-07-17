/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:50:10 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/10 13:10:07 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_screen(t_editor* le, t_doom* dm, int x, int y)
{
	if (le->marea && dm->event.motion.x < 750)
	{
		y = dm->event.motion.y / 30;
		x = dm->event.motion.x / 30;
		if (y >= dm->height)
			y = dm->height - 1;
		if (x >= dm->width)
			x = dm->width - 1;
		if (y < 0)
			y = 0;
		if (x < 0)
			x = 0;
		if (le->blk == 7)
		{
			dm->spawn.x = x + 0.51;
			dm->spawn.y = y + 0.51;
			dm->spawn.z = le->options[3] + 0.5;
		}
		dm->area[le->options[3]][y][x] = le->blk;
		printf("Drew block %d\n", le->blk);
	}
	else if (le->mslider)
	{

	}
	else if (le->mblock)
	{
		//le->blk = ((dm->event.motion.x - 750) / 107) - 1;
		printf("Selected block %d\n", le->blk);
	}
}

void	check_area(t_editor* le, SDL_Event ev)
{
	if (ev.motion.x >= 0 && ev.motion.y >= 0)
	{
		if (ev.motion.x < 750 && ev.motion.y < 750)
			le->marea = 1;
		else if (ev.motion.x < 1500 && ev.motion.y < 375)
			le->mslider = 1;
		else if (ev.motion.x < 1500 && ev.motion.y < 750)
		{
			le->blk = ((ev.motion.x - 750) / 107) + 1;
			le->mblock = 1;
		}
	}
	printf("Mouse POS %d %d\n", ev.motion.x, ev.motion.y);
	printf("Area STS %d %d %d\n", le->marea, le->mslider, le->mblock);
}

void	editor_key_release(Uint32 key, t_editor *le)
{
	if (key == ESC)
		le->quit = 1;
	if (key == DOWN)
		le->cur++;
	if (key == UP)
		le->cur--;
	if (le->cur > 4)
		le->cur = 0;
	if (le->cur < 0)
		le->cur = 4;
}

void	editor_key_press(Uint32 key, t_editor *le)
{
	if (key == LEFT)
		le->options[le->cur]--;
	if (key == RIGHT)
		le->options[le->cur]++;
	if (le->options[le->cur] > le->maxval[le->cur])
		le->options[le->cur] = le->maxval[le->cur];
	if (le->options[le->cur] < le->minval[le->cur])
		le->options[le->cur] = le->minval[le->cur];
	//printf("Min %d max %f\n", le->minval[le->cur], le->maxval[le->cur]);
}