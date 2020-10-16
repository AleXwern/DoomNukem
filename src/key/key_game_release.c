/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_game_release.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:12:40 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/16 15:48:10 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	key_release_5(int key, t_doom *dm)
{
	if (key == KEY_R && !dm->reloading && !dm->shooting && dm->gun)
	{
		dm->reloading = 1;
		dm->ani = 2;
	}
	if (key == SPACE && !dm->crouching)
		jump(dm);
	if (key == KEY_E)
		if (dm->invincible == 1)
			dm->invincible++;
	if (key == KEY_X)
	{
		if (dm->invincible == 0)
			dm->invincible++;
		else if (dm->invincible == 4)
			dm->invincible = 0;
	}
	if (key == KEY_A)
	{
		if (dm->invincible == 3)
			dm->invincible++;
		dm->key.a = 0;
	}
	if (key == KEY_D)
		dm->key.d = 0;
}

void	key_release_4(int key, t_doom *dm)
{
	if (key == KEY_J)
		dm->hp += 1;
	if (key == KEY_SHIFT)
		dm->movsp -= 0.15;
	if (key == KEY_L)
	{
		if (dm->invincible == 2)
			dm->invincible++;
		else
			dm->isoutline = (dm->isoutline * dm->isoutline) - 1;
	}
	if (key == KEY_C && dm->crouching)
		reset_crouching(dm);
	if (key == KEY_B)//remove when crouching works
		dm->pos.x -= 0.5;
	key_release_5(key, dm);
}

void	key_release_3(int key, t_doom *dm)
{
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
	if (key == KEY_ONE)
		dm->key.one = 0;
	if (key == KEY_TWO)
		dm->key.two = 0;
	if (key == KEY_TRE)
		dm->key.three = (dm->key.three == 0 ? 1 : 0);
	key_release_4(key, dm);
}

void	key_release_2(int key, t_doom *dm)
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
		return ;
	}
	if (key == KEY_T)
		dm->texbool = (dm->texbool * dm->texbool) - 1;
	if (key == KEY_TRE)
		interact(dm);
	key_release_3(key, dm);
}

int		key_release(int key, t_doom *dm)
{
	if (key == ESC && !dm->gamewon)
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
		key_release_2(key, dm);
	else if (!dm->alive && !dm->gamewon && key == SPACE)
	{
			reset_position(dm);
			ft_bzero(&dm->key, sizeof(t_key));
	}
	else if (dm->gamewon && (key == SPACE || key == ESC))
		error_out(WINGAME, dm);
	return (0);
}
