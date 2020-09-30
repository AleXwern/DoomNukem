/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:07:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/30 13:37:43 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	menu_keys_hold(int key, t_doom *dm)
{
	if (key == RIGHT && dm->cur == 11)
		dm->netstat = connect_server(dm);
	else if (key == LEFT && dm->cur == 11)
	{
		SDLNet_TCP_Close(dm->sock);
		dm->netstat = 0;
	}
	else if (key == LEFT && dm->cur != 11)
	{
		(*dm->options[dm->cur])--;
		if ((*dm->options[dm->cur]) < 0)
			(*dm->options[dm->cur]) = 0;
	}
	else if (key == RIGHT && dm->cur != 11)
	{
		(*dm->options[dm->cur])++;
		if ((*dm->options[dm->cur]) > (int)dm->maxvalue[dm->cur])
			(*dm->options[dm->cur]) = (int)dm->maxvalue[dm->cur];
	}
	if (dm->cur == 8)
	{
		if (dm->tile < 1)
			dm->tile = 1;
		destroy_gfx(dm, -1);
		comp_gfx(dm, 0);
	}
	else if (dm->cur == 9)
	{
		Mix_VolumeMusic(dm->volume);
		Mix_Volume(-1, dm->volume);
	}
}

int		key_hold(int key, t_doom *dm)
{
	if (dm->ismenu)
	{
		menu_keys_hold(key, dm);
		return (0);
	}
	if (key == KEY_A)
		dm->key.a = 1;
	if (key == KEY_D)
		dm->key.d = 1;
	if (key == KEY_W)
		dm->key.w = 1;
	if (key == KEY_S)
		dm->key.s = 1;
	if (key == NUM_PLU)
		dm->key.plus = 1;
	if (key == NUM_MIN)
		dm->key.minus = 1;
	if (key == KEY_ONE)
		dm->key.one = 1;
	if (key == KEY_TWO)
		dm->key.two = 1;
	if (key == KEY_SHIFT)
		dm->movsp += 0.10;
	if (key == KEY_O)
	{
		dm->shift++;
		if (dm->shift > 15)
			dm->shift = 15;
	}
	if (key == KEY_P)
	{
		dm->shift--;
		if (dm->shift < 0)
			dm->shift = 0;
	}
	if (key == KEY_C && !dm->crouching)
	{
		printf("started crouching\n");
		dm->movsp -= 0.03;
		dm->pos.z += 0.2;
		dm->crouching = 1;
	}
	if (key == UP)
		dm->key.up = 1;
	if (key == DOWN)
		dm->key.down = 1;
	if (key == LEFT)
		dm->key.left = 1;
	if (key == RIGHT)
		dm->key.right = 1;
	return (0);
}

void	menu_keys(int key, t_doom *dm)
{
	if (key == DOWN)
		dm->cur++;
	else if (key == UP)
		dm->cur--;
	else if (key == SPACE && (*dm->options[dm->cur]) < (int)dm->maxvalue[dm->cur] && dm->cur != 11)
		(*dm->options[dm->cur]) = (int)dm->maxvalue[dm->cur];
	else if (key == SPACE && dm->cur != 11)
		(*dm->options[dm->cur]) = 0;
	if (dm->cur < 0)
		dm->cur = OP;
	if (dm->cur > OP)
		dm->cur = 0;
	if (dm->minopt > dm->cur)
		dm->minopt = 0;
	if (dm->cur - dm->minopt > 9)
		dm->minopt = dm->cur - 9;
	if (dm->cur == 8)
	{
		if (dm->tile < 1)
			dm->tile = 1;
		destroy_gfx(dm, -1);
		comp_gfx(dm, 0);
	}
	else if (dm->cur == 9)
	{
		Mix_VolumeMusic(dm->volume);
		Mix_Volume(-1, dm->volume);
	}
}

int		key_release(int key, t_doom *dm)
{
	if (key == ESC)
	{
		SDL_SetWindowResizable(dm->win, SDL_FALSE);
		SDL_SetWindowSize(dm->win, WINX, WINY);
		dm->cycle = &main_menu;
		dm->keyck = &key_state_menu;
		reset_position(dm);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		dm->mousemovement = 0;
		if (dm->netstat)
			SDLNet_TCP_Close(dm->sock);
		dm->netstat = 0;
		return (1);
	}
	if (dm->alive)
	{
		if (key == KEY_M)
			dm->ismenu = dm->ismenu * dm->ismenu - 1;
		if (dm->ismenu == -1)
			dm->cycle = &options_menu;
		else if (dm->ismenu == 0)
			dm->cycle = &render;
		if (dm->ismenu)
		{
			menu_keys(key, dm);
			return (0);
		}
		if (key == KEY_T)
			dm->texbool = (dm->texbool * dm->texbool) - 1;
		if (key == KEY_TRE)
			interact(dm);
		if (key == KEY_A)
			dm->key.a = 0;
		if (key == KEY_D)
			dm->key.d = 0;
		if (key == KEY_W)
			dm->key.w = 0;
		if (key == KEY_S)
			dm->key.s = 0;
		if (key == UP)
			dm->key.up = 0;
		if (key == DOWN)
			dm->key.down = 0;
		if (key == LEFT)
			dm->key.left = 0;
		if (key == RIGHT)
			dm->key.right = 0;
		if (key == 69)
			dm->key.plus = 0;
		if (key == 78)
			dm->key.minus = 0;
		if (key == KEY_ONE)
			dm->key.one = 0;
		if (key == KEY_TWO)
			dm->key.two = 0;
		if (key == KEY_TRE)
			dm->key.three = (dm->key.three == 0 ? 1 : 0);
		if (key == KEY_I)
			dm->keycard = (dm->keycard == 0 ? 1 : 0);
		if (key == KEY_K && !dm->iframe)
		{
			Mix_PlayChannel(-1, dm->ishit, 0);
			dm->hp -= 1;
			dm->iframe = IFRAME;
		}
		if (key == KEY_J)
		{
			dm->hp += 1;
		}
		if (key == KEY_SHIFT)
			dm->movsp -= 0.10;
		if (key == KEY_L)
			dm->isoutline = (dm->isoutline * dm->isoutline) - 1;
		if (key == KEY_C && dm->crouching)
		{
			if (dm->area[(int)(dm->pos.z - 0.2)][(int)dm->pos.y][(int)dm->pos.x].b <= 1)
			{
				//printf("uncrouched\n");
				dm->crouching = 0;
				dm->movsp += 0.03;
				dm->pos.z -= 0.2;
			}
			else
			{
				//printf("can't uncrouch\n");
				dm->uncrouch = 1;
			}
		}
		if (key == KEY_R && !dm->reloading && !dm->shooting && dm->gun)
		{
			dm->reloading = 1;
			dm->ani = 2;
		}
		if (key == SPACE)
			dm->key.space = 3;
		if (key == KEY_Y)
			dm->plane.z -= 0.05;
		if (key == KEY_H)
			dm->plane.z += 0.05;
	}
	else
	{
		if (key == SPACE)
		{
			dm->alive = 1;
			dm->hp = 5;
			dm->magazine = 10;
			reset_position(dm);
			ft_bzero(&dm->key, sizeof(t_key));
		}
	}

	return (0);
}

int		x_press(t_doom *dm)
{
	error_out(FINE, dm);
	return (0);
}

void	jetpack(t_doom *dm)
{
	if (dm->key.one)
	{
		if (dm->area[(int)(dm->pos.z + 0.5)][(int)(dm->pos.y)][(int)dm->pos.x].b <= 1)
			dm->pos.z += 0.05 * (30.0 / dm->buffer / dm->prefps);
	}
	if (dm->key.two)
	{
		Mix_PlayChannel(-1, dm->jetpack, 0);
		if (dm->area[(int)(dm->pos.z - 0.5)][(int)(dm->pos.y)][(int)dm->pos.x].b <= 1 &&
			dm->pos.z > 1)
			dm->pos.z -= 0.05 * (30.0 / dm->buffer / dm->prefps);
	}
	dm->airbrn = 1;
}

int		mouse_move(int x, int y, t_doom *dm)
{
	t_vector	olddir;
	t_vector	oldplane;
	t_vector	rota;

	olddir = dm->dir;
	oldplane = dm->plane;
	if (x && abs(x) < dm->winw)
	{
		rota.x = (double)x / dm->winw * OSCAM;
		dm->dir.x = olddir.x * cos(rota.x) - olddir.y * sin(rota.x);
		dm->dir.y = olddir.x * sin(rota.x) + olddir.y * cos(rota.x);
		dm->plane.x = oldplane.x * cos(rota.x) - oldplane.y * sin(rota.x);
		dm->plane.y = oldplane.x * sin(rota.x) + oldplane.y * cos(rota.x);
	}
	if (y && abs(y) < dm->winh)
	{
		rota.y = (double)y / dm->winh * OSCAM;
		if (dm->dir.z + rota.y > -0.5 && dm->dir.z + rota.y < 0.5)
			dm->dir.z += rota.y;
		dm->camshift = 1.0 - (dm->dir.z * 2);
	}
	return (0);
}

int		move(t_doom *dm)
{
	if (dm->alive)
	{
		if ((dm->key.w || dm->key.s) && !dm->isoptions)
			move_fb(dm);
		if ((dm->key.a || dm->key.d) && !dm->isoptions)
			strafe(dm, 0, 0);
		if ((dm->key.up || dm->key.down || dm->key.left || dm->key.right) && !dm->isoptions)
			cam_udy(dm);
		if ((dm->key.one || dm->key.two) && !dm->isoptions)
			jetpack(dm);
		gravity(dm);
		if ((dm->key.space) && !dm->isoptions && !dm->airbrn)
		{
			dm->airbrn = 1;
			dm->gravity.z = -0.45 * (30.0 / dm->buffer / dm->prefps);
		}
		if (!dm->airbrn && !dm->iframe)
			suffrocate(dm, dm->area[(int)(dm->pos.z - 0.1)][(int)dm->pos.y][(int)dm->pos.x],
			(t_vector){.z = dm->pos.z - (int)dm->pos.z, .y = dm->pos.y - (int)dm->pos.y, .x = dm->pos.x - (int)dm->pos.x});
		if (dm->key.space > 0)
			dm->key.space--;
	}
	return (0);
}
