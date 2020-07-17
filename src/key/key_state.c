/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:43:54 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/16 15:56:58 by tbergkul         ###   ########.fr       */
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
			if (wlf->event.button.button == SDL_BUTTON_MIDDLE)
				wlf->mousemovement = (wlf->mousemovement * wlf->mousemovement) - 1;
			else if (wlf->event.button.button == SDL_BUTTON_RIGHT)
				interact(wlf);
			else if (wlf->event.button.state == SDL_BUTTON_LEFT && wlf->shooting == 0 && wlf->magazine > 0 && !wlf->reloading)
				wlf->shooting = 1;
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
			editor_key_release(dm->event.key.keysym.scancode, le);
	}
	draw_screen(le, dm, 0, 0);
}
