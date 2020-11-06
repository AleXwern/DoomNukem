/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_game_hold.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:07:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/11/04 12:09:37 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	key_hold2(int key, t_doom *dm)
{
	if (key == RIGHT)
		dm->key.right = 1;
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
		crouch(dm);
	if (key == KEY_ONE)
		dm->key.one = 1;
	if (key == KEY_TWO)
		dm->key.two = 1;
	if (key == KEY_SHIFT)
		dm->movsp += 0.15;
}

int		key_hold(int key, t_doom *dm)
{
	if (dm->gamestarted)
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
		if (key == UP)
			dm->key.up = 1;
		if (key == DOWN)
			dm->key.down = 1;
		if (key == LEFT)
			dm->key.left = 1;
		key_hold2(key, dm);
	}
	return (0);
}

void	crouch(t_doom *dm)
{
	dm->crouching = 1;
	dm->movsp -= 0.03;
	dm->plrhight = 0.4;
	dm->pos.z += 0.2;
	dm->airbrn = 1;
}

void	reset_crouching(t_doom *dm)
{
	dm->crouching = 0;
	dm->movsp += 0.03;
	dm->plrhight = 0.6;
	dm->pos.z -= 0.2;
	dm->airbrn = 1;
}
