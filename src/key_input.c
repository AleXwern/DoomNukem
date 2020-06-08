/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:07:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/08 15:18:37 by anystrom         ###   ########.fr       */
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
	return (0);
}

int				x_press(t_wolf *wolf)
{
	error_out(FINE, wolf);
	return (0);
}

int				move(t_wolf *wlf)
{
	if (wlf->keydown || wlf->keyup)
		move_fb(wlf);
	if (wlf->keyleft || wlf->keyright)
		move_lr(wlf);
	wlf->cycle(wlf);
	return (0);
}
