/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:07:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/11 17:17:43 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/value.h"
#include "../includes/wolf.h"

int				key_hold(int key, t_wolf *wlf)
{
	//ft_putnbrln(key);
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
		if (key == NUM_PLU)
		wlf->keyplus = 1;
	if (key == NUM_MIN)
		wlf->keyminus = 1;
	if (key == KEY_W)
		wlf->keyw = 1;
	if (key == KEY_S)
		wlf->keys = 1;
	if (key == KEY_A)
		wlf->keya = 1;
	if (key == KEY_D)
		wlf->keyd = 1;
	if (key == KEY_ONE)
		wlf->keyone = 1;
	if (key == KEY_TWO)
		wlf->keytwo = 1;
	if (key == KEY_SHIFT)
		wlf->movsp += 0.06;
	if (key == KEY_Q)
		wlf->keyq = 1;
	if (key == KEY_E)
		wlf->keye = 1;
	return (0);
}

int				key_release(int key, t_wolf *wlf)
{
	if (key == KEY_T)
		wlf->texbool = (wlf->texbool * wlf->texbool) - 1;
	if (key == KEY_R)
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
	if (key == KEY_W)
		wlf->keyw = 0;
	if (key == KEY_S)
		wlf->keys = 0;
	if (key == KEY_A)
		wlf->keya = 0;
	if (key == KEY_D)
		wlf->keyd = 0;
	if (key == KEY_ONE)
		wlf->keyone = 0;
	if (key == KEY_TWO)
		wlf->keytwo = 0;
	if (key == KEY_Q)
		wlf->keyq = 0;
	if (key == KEY_E)
		wlf->keye = 0;
	if (key == KEY_SHIFT)
		wlf->movsp -= 0.06;
	if (key == SPACE)
	{
		if (wlf->map[(int)(wlf->posz - 0.5)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
			if (wlf->map[(int)(wlf->posz + 0.5)][(int)(wlf->posy)][(int)wlf->posx] > 1)
				wlf->posz -= 1;
	}
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
		if (wlf->map[(int)(wlf->posz + wlf->movsp - 0.4)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
		{
			wlf->posz -= 0.1;
		}
	}
	if (wlf->keyplus)
	{
		if (wlf->map[(int)(wlf->posz - wlf->movsp + 0.4)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
		{
			wlf->posz += 0.1;
		}
	}
}

void			jetpack(t_wolf *wlf)
{
	if (wlf->keyone)
		if (wlf->map[(int)(wlf->posz + 0.5)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
			wlf->posz += 0.05;
	if (wlf->keytwo)
		if (wlf->map[(int)(wlf->posz - 0.5)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
			wlf->posz -= 0.05;
}

int				move(t_wolf *wlf)
{
	if (wlf->keydown || wlf->keyup)
		move_fb(wlf);
	if (wlf->keyleft || wlf->keyright)
		move_lr(wlf);
	if (wlf->keyplus || wlf->keyminus)
		move_z(wlf);
	if (wlf->keyw || wlf->keys || wlf->keya || wlf->keyd)
		cam_udy(wlf, 0.0, 0.0);
	if (wlf->keyone || wlf->keytwo)
		jetpack(wlf);
	if (wlf->keyq || wlf->keye)
		strafe(wlf);
	wlf->cycle(wlf);
	return (0);
}
