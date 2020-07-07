/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:07:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/07 14:51:15 by anystrom         ###   ########.fr       */
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
	if (wlf->cur == 8)
	{
		if (wlf->tile < 1)
			wlf->tile = 1;
		destroy_gfx(wlf, -1);
		comp_gfx(wlf, 0);
	}
}

int				key_hold(int key, t_doom *wlf)
{
	if (wlf->ismenu)
	{
		menu_keys_hold(key, wlf);
		return (0);
	}
	if (key == LEFT || key == KEY_A)
		wlf->key.left = 1;
	if (key == RIGHT || key == KEY_D)
		wlf->key.right = 1;
	if (key == UP || key == KEY_W)
		wlf->key.up = 1;
	if (key == DOWN || key == KEY_S)
		wlf->key.down = 1;
	if (key == NUM_PLU)
		wlf->key.plus = 1;
	if (key == NUM_MIN)
		wlf->key.minus = 1;
	//if (key == KEY_W)
	//	wlf->keyw = 1;
	//if (key == KEY_S)
	//	wlf->keys = 1;
	/*if (key == KEY_A)
		wlf->keya = 1;
	if (key == KEY_D)
		wlf->keyd = 1;*/
	if (key == KEY_ONE)
		wlf->key.one = 1;
	if (key == KEY_TWO)
		wlf->key.two = 1;
	if (key == KEY_SHIFT)
		wlf->movsp += 0.06;
	if (key == KEY_Q)
		wlf->key.q = 1;
	if (key == KEY_E)
		wlf->key.e = 1;
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
		wlf->cur = 8;
	if (wlf->cur > 8)
		wlf->cur = 0;
}

int				key_release(int key, t_doom *wlf)
{
	if (key == ESC)
	{
		wlf->cycle = &main_menu;
		wlf->keyck = &key_state_menu;
		reset_position(wlf);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		wlf->mousemovement = 0;
		return (1);
	}
	if (key == KEY_M)
		wlf->ismenu = wlf->ismenu * wlf->ismenu - 1;
	if (wlf->ismenu == -1)
		wlf->cycle = &options_menu;
	else if (wlf->ismenu == 0)
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
		wlf->key.left = 0;
	if (key == RIGHT || key == KEY_D)
		wlf->key.right = 0;
	if (key == UP || key == KEY_W)
		wlf->key.up = 0;
	if (key == DOWN || key == KEY_S)
		wlf->key.down = 0;
	if (key == 69)
		wlf->key.plus = 0;
	if (key == 78)
		wlf->key.minus = 0;
	if (key == KEY_ONE)
		wlf->key.one = 0;
	if (key == KEY_TWO)
		wlf->key.two = 0;
	if (key == KEY_Q)
		wlf->key.q = 0;
	if (key == KEY_E)
		wlf->key.e = 0;
	if (key == KEY_I || key == SDL_SCANCODE_I)
	{
		ft_putendl("I pressed");
		wlf->key.i = wlf->key.i == 1 ? 0 : 1;
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
		reset_window(wlf, 0);
	if (key == SPACE)
	{
		if (!wlf->airbrn && !wlf->isgravity)
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
	if (wlf->key.one)
		if (wlf->map[(int)(wlf->posz + 0.5)][(int)(wlf->posy)][(int)wlf->posx] <= 1)
			wlf->posz += 0.05 * (30.0 / wlf->buffer / wlf->prefps);
	if (wlf->key.two)
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
	if ((wlf->key.down || wlf->key.up) && !wlf->isoptions)
		move_fb(wlf);
	if ((wlf->key.left || wlf->key.right) && !wlf->isoptions)
		move_lr(wlf);
	if ((wlf->key.w || wlf->key.s || wlf->key.a || wlf->key.d) && !wlf->isoptions)
		cam_udy(wlf);
	if ((wlf->key.one || wlf->key.two) && !wlf->isoptions)
		jetpack(wlf);
	if ((wlf->key.q || wlf->key.e) && !wlf->isoptions)
		strafe(wlf, 0, 0);
	gravity(wlf);
	return (0);
}
