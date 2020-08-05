/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:43:54 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:32:56 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	key_state_game(t_doom *dm)
{
	if (SDL_PollEvent(&(dm->event)))
	{
		if (SDL_HasEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL))
			SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
		if (dm->event.type == SDL_QUIT)
			error_out(FINE, dm);
		if (dm->event.window.event == SDL_WINDOWEVENT_RESIZED || dm->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			resize_window(dm);
		if (dm->event.key.state == SDL_PRESSED)
			key_hold(dm->event.key.keysym.scancode, dm);
		if (dm->event.key.state == SDL_RELEASED)
			key_release(dm->event.key.keysym.scancode, dm);
		//if (dm->event.cbutton.state == SDL_PRESSED)
		//	key_hold(dm->event.cbutton.button, dm);
		//if (dm->event.cbutton.state == SDL_RELEASED)
		//	key_release(dm->event.cbutton.button, dm);
		if (dm->event.button.state == SDL_PRESSED)
		{
			if (dm->event.button.button == SDL_BUTTON_MIDDLE)
				dm->mousemovement = (dm->mousemovement * dm->mousemovement) - 1;
			else if (dm->event.button.button == SDL_BUTTON_RIGHT)
				interact(dm);
			else if (dm->event.button.state == SDL_BUTTON_LEFT && dm->shooting == 0 && dm->magazine > 0 && !dm->reloading)
				dm->shooting = 1;
			if (dm->mousemovement)
				SDL_SetRelativeMouseMode(SDL_TRUE);
			else
				SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		if (dm->mousemovement)
			mouse_move(dm->event.motion.xrel, dm->event.motion.yrel, dm);
	}
	move(dm);
}

void	key_state_menu(t_doom *dm)
{
	if (SDL_PollEvent(&(dm->event)))
	{
		if (dm->event.type == SDL_QUIT || dm->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			error_out(FINE, dm);
		if (dm->event.window.event == SDL_WINDOWEVENT_RESIZED || dm->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			resize_window(dm);
		if (dm->event.key.state == SDL_RELEASED)
			key_release_menu(dm->event.key.keysym.scancode, dm);
	}
}

void	key_state_editor(t_editor *le, t_doom *dm)
{
	if (SDL_PollEvent(&(dm->event)))
	{
		//if (SDL_HasEvent(SDL_MOUSEMOTION))
		//	SDL_FlushEvent(SDL_MOUSEMOTION);
		if (dm->event.type == SDL_MOUSEBUTTONDOWN)
			check_area(le, dm->event);
		if (dm->event.type == SDL_MOUSEBUTTONUP)
		{
			le->marea = 0;
			le->mslider = 0;
			le->mblock = 0;
		}
		if (dm->event.window.event == SDL_WINDOWEVENT_RESIZED || dm->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			SDL_SetWindowSize(dm->win, 1500, 750);
			resize_window(dm);
		}
		if (dm->event.type == SDL_QUIT)
			le->quit = 1;
		if (dm->event.key.state == SDL_PRESSED)
			editor_key_press(dm->event.key.keysym.scancode, le);
		if (dm->event.key.state == SDL_RELEASED)
			editor_key_release(dm->event.key.keysym.scancode, le, dm);
	}
	draw_screen(le, dm, 0, 0);
}
