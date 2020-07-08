/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:50:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/08 13:08:53 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	key_release_menu(int key, t_doom *wlf)
{
	if (key == ESC)
		error_out(FINE, wlf);
	if (key == DOWN)
		wlf->sel++;
	if (key == UP)
		wlf->sel--;
	if (key == SPACE)
	{
		if (wlf->sel == 0)
		{
			wlf->cycle = &render;
			wlf->keyck = &key_state_game;
			ft_bzero(&wlf->key, sizeof(t_key));
			reset_position(wlf);
			wlf->ismenu = 0;
		}
		else if (wlf->sel == 1)
			editor_main(wlf);
		else if (wlf->sel == 2)
			printf("Show help/keys and credits.\n"); //help_n_credits(wlf);
		else
			error_out(FINE, wlf);
	}
	if (wlf->sel > 3)
		wlf->sel = 0;
	else if (wlf->sel < 0)
		wlf->sel = 3;
}