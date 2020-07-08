/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:43:54 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/08 15:57:09 by anystrom         ###   ########.fr       */
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
		if (wlf->event.type == SDL_QUIT)
			error_out(FINE, wlf);
		if (wlf->event.window.event == SDL_WINDOWEVENT_RESIZED || wlf->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			resize_window(wlf);
		if (wlf->event.key.state == SDL_PRESSED)
			key_hold(wlf->event.key.keysym.scancode, wlf);
		if (wlf->event.key.state == SDL_RELEASED)
			key_release(wlf->event.key.keysym.scancode, wlf);
		//if (wlf->event.cbutton.state == SDL_PRESSED)
		//	key_hold(wlf->event.cbutton.button, wlf);
		//if (wlf->event.cbutton.state == SDL_RELEASED)
		//	key_release(wlf->event.cbutton.button, wlf);
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

void	key_state_menu(t_doom *wlf)
{
	if (SDL_PollEvent(&(wlf->event)))
	{
		if (wlf->event.type == SDL_QUIT || wlf->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			error_out(FINE, wlf);
		if (wlf->event.window.event == SDL_WINDOWEVENT_RESIZED || wlf->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			resize_window(wlf);
		if (wlf->event.key.state == SDL_RELEASED)
			key_release_menu(wlf->event.key.keysym.scancode, wlf);
	}
}

void	key_state_editor(t_editor *le, t_doom *dm)
{
	if (SDL_PollEvent(&(le->ev)))
	{
		if (le->ev.window.event == SDL_WINDOWEVENT_RESIZED || le->ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			resize_window(dm);
		if (le->ev.type == SDL_QUIT)
			le->quit = 1;
		if (le->ev.key.state == SDL_PRESSED)
			editor_key_press(le->ev.key.keysym.scancode, le);
		if (le->ev.key.state == SDL_RELEASED)
			editor_key_release(le->ev.key.keysym.scancode, le);
	}
}