/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:07:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/06 15:40:20 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void			menu_keys_hold(int key, t_doom *wlf)
{
	if (key == LEFT)
	{
		(*wlf->options[wlf->cur])--;
		if ((*wlf->options[wlf->cur]) < 0)
			(*wlf->options[wlf->cur]) = 0;
	}
	else if (key == RIGHT)
	{
		(*wlf->options[wlf->cur])++;
		if ((*wlf->options[wlf->cur]) > (int)wlf->maxvalue[wlf->cur])
			(*wlf->options[wlf->cur]) = (int)wlf->maxvalue[wlf->cur];
	}
}

int				key_hold(int key, t_doom *wlf)
{
	if (wlf->ismenu)
	{
		menu_keys_hold(key, wlf);
		return (0);
	}
	if (key == ESC)
		error_out(FINE, wlf);
	if (key == LEFT || key == KEY_A)
		wlf->keyleft = 1;
	if (key == RIGHT || key == KEY_D)
		wlf->keyright = 1;
	if (key == UP || key == KEY_W)
		wlf->keyup = 1;
	if (key == DOWN || key == KEY_S)
		wlf->keydown = 1;
	if (key == NUM_PLU)
		wlf->keyplus = 1;
	if (key == NUM_MIN)
		wlf->keyminus = 1;
	//if (key == KEY_W)
	//	wlf->keyw = 1;
	//if (key == KEY_S)
	//	wlf->keys = 1;
	/*if (key == KEY_A)
		wlf->keya = 1;
	if (key == KEY_D)
		wlf->keyd = 1;*/
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
	if (key == KEY_O)
	{
		wlf->shift++;
		if (wlf->shift > 100)
			wlf->shift = 100;
	}
	if (key == KEY_P)
	{
		wlf->shift--;
		if (wlf->shift < 0)
			wlf->shift = 0;
	}
	if (key == KEY_C && !wlf->crouching)
	{
		wlf->crouching = 1;
		wlf->movsp -= 0.03;
		wlf->posz += 0.2;
	}
	return (0);
}

void			menu_keys(int key, t_doom *wlf)
{
	if (key == DOWN)
		wlf->cur++;
	else if (key == UP)
		wlf->cur--;
	if (wlf->cur < 0)
		wlf->cur = 7;
	if (wlf->cur > 7)
		wlf->cur = 0;
}

int				key_release(int key, t_doom *wlf)
{
	if (key == KEY_M)
		wlf->ismenu = wlf->ismenu * wlf->ismenu - 1;
	if (wlf->ismenu)
		wlf->cycle = &options_menu;
	else
		wlf->cycle = &render;
	if (wlf->ismenu)
	{
		menu_keys(key, wlf);
		return (0);
	}
	if (key == KEY_T)
		wlf->texbool = (wlf->texbool * wlf->texbool) - 1;
	if (key == KEY_TRE)
		interact(wlf);
	if (key == LEFT || key == KEY_A)
		wlf->keyleft = 0;
	if (key == RIGHT || key == KEY_D)
		wlf->keyright = 0;
	if (key == UP || key == KEY_W)
		wlf->keyup = 0;
	if (key == DOWN || key == KEY_S)
		wlf->keydown = 0;
	if (key == 69)
		wlf->keyplus = 0;
	if (key == 78)
		wlf->keyminus = 0;
	//if (key == KEY_W)
	//	wlf->keyw = 0;
	//if (key == KEY_S)
	//	wlf->keys = 0;
	if (key == KEY_ONE)
		wlf->keyone = 0;
	if (key == KEY_TWO)
		wlf->keytwo = 0;
	if (key == KEY_Q)
		wlf->keyq = 0;
	if (key == KEY_E)
		wlf->keye = 0;
	if (key == KEY_I || key == SDL_SCANCODE_I)
	{
		ft_putendl("I pressed");
		wlf->keyi = wlf->keyi == 1 ? 0 : 1;
	}
	if (key == KEY_SHIFT)
		wlf->movsp -= 0.06;
	if (key == KEY_L)
		wlf->isoutline = (wlf->isoutline * wlf->isoutline) - 1;
	if (key == KEY_C && wlf->crouching)
	{
		wlf->crouching = 0;
		wlf->movsp += 0.03;
		wlf->posz -= 0.2;
	}
	if (key == KEY_R)
		doom_default(wlf);
	if (key == SPACE)
	{
		if (!wlf->airbrn)
		{
			wlf->airbrn = 1;
			wlf->gravity.z = -0.55 * (30.0 / wlf->buffer / wlf->prefps);
		}
	}
	return (0);
}

int				x_press(t_doom *wolf)
{
	error_out(FINE, wolf);
	return (0);
}

void			jetpack(t_doom *wlf)
{
	if (wlf->keyone)
		if (wlf->map[(int)(wlf->posz + 0.5)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
			wlf->posz += 0.05 * (30.0 / wlf->buffer / wlf->prefps);
	if (wlf->keytwo)
		if (wlf->map[(int)(wlf->posz - 0.5)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
			wlf->posz -= 0.05 * (30.0 / wlf->buffer / wlf->prefps);
}

int				mouse_move(int x, int y, t_doom *wlf)
{
	t_vector	olddir;
	t_vector	oldplane;
	t_vector	rota;

	olddir = wlf->dir;
	oldplane = wlf->plane;
	//printf("%d %d\n", x, y);
	if (x && abs(x) < wlf->winw)
	{
		rota.x = (double)x / wlf->winw * OSCAM;
		//printf("%f\nwith: %d %d\n", rota.x, x, wlf->winw);
		wlf->dir.x = olddir.x * cos(rota.x) - olddir.y * sin(rota.x);
		wlf->dir.y = olddir.x * sin(rota.x) + olddir.y * cos(rota.x);
		wlf->plane.x = oldplane.x * cos(rota.x) - oldplane.y * sin(rota.x);
		wlf->plane.y = oldplane.x * sin(rota.x) + oldplane.y * cos(rota.x);
	}
	if (y && abs(y) < wlf->winh)
	{
		rota.y = (double)y / wlf->winh * OSCAM;
		if (wlf->dir.z + rota.y > -0.6 && wlf->dir.z + rota.y < 0.6)
			wlf->dir.z += rota.y;
		wlf->camshift = 1.0 - (wlf->dir.z * 2);
	}
	return (0);
}

int				move(t_doom *wlf)
{
	if ((wlf->keydown || wlf->keyup) && !wlf->isoptions)
		move_fb(wlf);
	if ((wlf->keyleft || wlf->keyright) && !wlf->isoptions)
		move_lr(wlf);
	if ((wlf->keyw || wlf->keys || wlf->keya || wlf->keyd) && !wlf->isoptions)
		cam_udy(wlf);
	if ((wlf->keyone || wlf->keytwo) && !wlf->isoptions)
		jetpack(wlf);
	if ((wlf->keyq || wlf->keye) && !wlf->isoptions)
		strafe(wlf, 0, 0);
	gravity(wlf);
	return (0);
}
