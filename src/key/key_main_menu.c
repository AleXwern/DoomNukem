/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_main_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:49:29 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/30 13:52:52 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	The following two functions handle keys pressed at the main menu.
*/

void	key_release_menu_more(int key, t_doom *dm)
{
	if (key == ESC && !dm->credits)
		error_out(FINE, dm);
	if (key == ESC && dm->credits)
	{
		dm->credits = 0;
		dm->creds = dm->winh;
	}
	if (key == DOWN && !dm->credits)
		dm->sel++;
	if (key == UP && !dm->credits)
		dm->sel--;
}

void	key_release_menu(int key, t_doom *dm)
{
	key_release_menu_more(key, dm);
	if (key == SPACE && !dm->credits)
	{
		if (dm->sel == 0)
		{
			SDL_SetWindowResizable(dm->win, SDL_TRUE);
			dm->cycle = &render;
			dm->keyck = &key_state_game;
			ft_bzero(&dm->key, sizeof(t_key));
			reset_position(dm);
			dm->ismenu = 0;
			dm->area[(int)dm->spw.z][(int)dm->spw.y][(int)dm->spw.x].b = 1;
		}
		else if (dm->sel == 1)
			editor_main(dm);
		else if (dm->sel == 2)
			dm->credits = 1;
		else
			error_out(FINE, dm);
	}
	if (dm->sel > 3)
		dm->sel = 0;
	else if (dm->sel < 0)
		dm->sel = 3;
}
