/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wingame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:43:26 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/19 10:28:16 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	gamestart(t_doom *dm)
{
	set_text(dm, "you have stolen top secret documents",
		(int[3]){dm->winh / 2 - 300, dm->winw / 2 - 480, 16711680}, 1);
	set_text(dm, "and need to escape the building",
		(int[3]){dm->winh / 2 - 250, dm->winw / 2 - 430, 16711680}, 1);
	set_text(dm, "press space to start",
		(int[3]){dm->winh / 2 - 5, dm->winw / 2 - 270, 16711680}, 1);
	SDL_RenderPresent(dm->rend);
}

void	wingame(t_doom *dm)
{
	if (!dm->victoryplayed)
		Mix_PlayChannel(-1, dm->victory, 0);
	dm->victoryplayed = 1;
	if (!dm->moneytext)
	{
		dm->moneytemp = ft_itoa(dm->money);
		dm->moneytext = ft_strjoin("score ", dm->moneytemp);
		free(dm->moneytemp);
	}
	set_text(dm, "you escaped with the stolen documents",
		(int[3]){dm->winh / 2 - 70, dm->winw / 2 - 500, 65280}, 1);
	set_text(dm, "job completed", (int[3]){dm->winh / 2 + 10,
		dm->winw / 2 - 200, 65280}, 1);
	set_text(dm, dm->moneytext, (int[3]){dm->winh / 2 + 50,
		dm->winw / 2 - 100, 65280}, 1);
	SDL_RenderPresent(dm->rend);
	dm->alive = 0;
	dm->gamewon = 1;
}
