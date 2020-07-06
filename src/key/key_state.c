/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:43:54 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/06 15:26:45 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	key_state_game(t_doom *wlf)
{
		if (SDL_PollEvent(&(wlf->event)))
	{
		if (SDL_HasEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL))
			SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
		if (wlf->event.type == SDL_QUIT || wlf->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			error_out(FINE, wlf);
		if (wlf->event.window.event == SDL_WINDOWEVENT_RESIZED || wlf->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			wind_default(wlf);
		if (wlf->event.key.state == SDL_PRESSED)
			key_hold(wlf->event.key.keysym.scancode, wlf);
		if (wlf->event.key.state == SDL_RELEASED)
			key_release(wlf->event.key.keysym.scancode, wlf);
		if (wlf->event.cbutton.state == SDL_PRESSED)
			key_hold(wlf->event.cbutton.button, wlf);
		if (wlf->event.cbutton.state == SDL_RELEASED)
			key_release(wlf->event.cbutton.button, wlf);
		if (wlf->event.button.state == SDL_PRESSED)
		{
			if (wlf->event.button.button == SDL_BUTTON_LEFT)
				wlf->mousemovement = (wlf->mousemovement * wlf->mousemovement) - 1;
			else if (wlf->event.button.button == SDL_BUTTON_RIGHT)
				interact(wlf);
			if (wlf->mousemovement)
				SDL_SetRelativeMouseMode(SDL_TRUE);
			else
				SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		if (wlf->mousemovement)
			mouse_move(wlf->event.motion.xrel, wlf->event.motion.yrel, wlf);
	}
	move(wlf);
}

void	key_state_menu(t_doom* wlf)
{
	if (wlf->event.key.state == SDL_RELEASED)
	{
		if (wlf->event.key.keysym.scancode == DOWN)
			wlf->sel++;
		if (wlf->event.key.keysym.scancode == UP)
			wlf->sel--;
		if (wlf->event.key.keysym.scancode == SPACE)
		{
			if (wlf->sel == 0)
			{
				wlf->cycle = &render;
				wlf->keyck = &key_state_game;
			}
			else if (wlf->sel == 1)
			{
				ft_putendl("Yes yes, this is editor.");
			}
			else
				error_out(FINE, wlf);
		}
		if (wlf->sel > 2)
			wlf->sel = 0;
		else if (wlf->sel < 0)
			wlf->sel = 2;
	}
}