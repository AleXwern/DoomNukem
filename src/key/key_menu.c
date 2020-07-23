/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:50:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:32:45 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	key_release_menu(int key, t_doom *dm)
{
	if (key == ESC)
		error_out(FINE, dm);
	if (key == DOWN)
		dm->sel++;
	if (key == UP)
		dm->sel--;
	if (key == SPACE)
	{
		if (dm->sel == 0)
		{
			SDL_SetWindowResizable(dm->win, SDL_TRUE);
			dm->cycle = &render;
			dm->keyck = &key_state_game;
			ft_bzero(&dm->key, sizeof(t_key));
			reset_position(dm);
			dm->ismenu = 0;
			dm->area[(int)dm->spawn.z][(int)dm->spawn.y][(int)dm->spawn.x] = 1;
			//Mix_PlayChannel(-1, dm->readyForAction, 0);
			dm->mousemovement = 1;
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
		else if (dm->sel == 1)
			editor_main(dm);
		else if (dm->sel == 2)
			printf("Show help/keys and credits.\n"); //help_n_credits(dm);
		else
			error_out(FINE, dm);
	}
	if (dm->sel > 3)
		dm->sel = 0;
	else if (dm->sel < 0)
		dm->sel = 3;
}
