/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:07:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/09 15:07:22 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/value.h"
#include "../includes/wolf.h"

int				key_hold(int key, t_wolf *wlf)
{
	if (key == ESC)
		error_out(FINE, wlf);
	if (key == LEFT)
		wlf->keyleft = 1;
	if (key == RIGHT)
		wlf->keyright = 1;
	if (key == UP)
		wlf->keyup = 1;
	if (key == DOWN)
		wlf->keydown = 1;
		if (key == 69)
		wlf->keyplus = 1;
	if (key == 78)
		wlf->keyminus = 1;
	return (0);
}

int				key_release(int key, t_wolf *wlf)
{
	if (key == KEY_T)
		wlf->texbool = (wlf->texbool * wlf->texbool) - 1;
	if (key == SPACE)
		interact(wlf);
	if (key == KEY_C)
		wlf->aggro = 499;
	if (key == LEFT)
		wlf->keyleft = 0;
	if (key == RIGHT)
		wlf->keyright = 0;
	if (key == UP)
		wlf->keyup = 0;
	if (key == DOWN)
		wlf->keydown = 0;
	if (key == 69)
		wlf->keyplus = 0;
	if (key == 78)
		wlf->keyminus = 0;
	return (0);
}

int				x_press(t_wolf *wolf)
{
	error_out(FINE, wolf);
	return (0);
}

void			move_z(t_wolf *wlf)
{
	if (wlf->keyminus)
	{
		if (wlf->map[(int)(wlf->posz + wlf->movsp)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
		{
			wlf->posz -= wlf->movsp;
		}
	}
	if (wlf->keyplus)
	{
		if (wlf->map[(int)(wlf->posz - wlf->movsp)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
		{
			wlf->posz += wlf->movsp;
		}
	}
}

int				move(t_wolf *wlf)
{
	if (wlf->keydown || wlf->keyup)
		move_fb(wlf);
	if (wlf->keyleft || wlf->keyright)
		move_lr(wlf);
	if (wlf->keyplus || wlf->keyminus)
		move_z(wlf);
	wlf->cycle(wlf);
	return (0);
}
