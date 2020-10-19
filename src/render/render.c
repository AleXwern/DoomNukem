/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/19 15:15:55 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

int		renthread(void *ptr)
{
	t_doom	*dm;

	dm = (t_doom*)ptr;
	while (dm->x < dm->winw)
	{
		dm->y = -1;
		while (++dm->y < dm->winh)
		{
			rc_init(dm);
			dm->lineh = (dm->winh / dm->walldist);
			side_check(dm);
			if (dm->side % 3 == 1)
				dm->col = 0xff3679ff;
			else if (dm->side % 3 == 2)
				dm->col = 0xffb01cff;
			else
				dm->col = 0xffF0330A;
			renthread2(dm);
		}
		dm->x += dm->trx;
	}
	return (1);
}

void	threads2(t_doom *dm, int *x)
{
	while (*x > 0)
	{
		*x -= 1;
		if (dm->threads[*x] == NULL)
			ft_putendl("Thread failure.");
		else
			SDL_WaitThread(dm->threads[*x], NULL);
	}
}

/*
**	if (dm->trx < 1)
**		dm->trx = 1;
**	//ft_bzero(dm->img.data, dm->winw * dm->winh); might want to use this
**	while (x < dm->trx)
**	{
*/

void	threads(t_doom *dm)
{
	static int	x;
	static int	i;

	if (dm->trx < 1)
		dm->trx = 1;
	while (x < dm->trx)
	{
		dm->data_r[x] = *dm;
		dm->data_r[x].x = x;
		dm->threads[x] =
			SDL_CreateThread(renthread, "Thread", (void*)&dm->data_r[x]);
		x++;
	}
	if (i >= 0 && dm->netstat)
	{
		if (send_pos(dm))
			recv_pos(dm);
		i = 0;
	}
	i++;
	threads2(dm, &x);
}

void	render2(t_doom *dm)
{
	if (dm->slidedoor != 'x')
		slide_door(dm);
	set_text(dm, dm->fpschar, (int[3]) {20, 350, 0xf70e0e }, 1);
	if (dm->alive && dm->hp <= 0)
	{
		dm->alive = 0;
		Mix_PlayChannel(-1, dm->death, 0);
		set_text(dm, "you died", (int[3]){dm->winh / 2 - 46,
			dm->winw / 2 - 250, 0xf70e0e}, 2);
		set_text(dm, "press space", (int[3]){dm->winh / 2 + 30,
			dm->winw / 2 - 310, 0xf70e0e}, 2);
		SDL_RenderPresent(dm->rend);
	}
	if (dm->iframe == IFRAME)
		Mix_PlayChannel(-1, dm->ishit, 0);
	if (dm->alive)
		SDL_RenderPresent(dm->rend);
	if (dm->iframe)
		dm->iframe--;
	dm->fps++;
}

/*
**	printf("Matrix:\nPOS %f %f %f\nDIR %f %f %f\nPLN %f %f %f\n",
**		dm->pos.z, dm->pos.y, dm->pos.x,
**		dm->dir.z, dm->dir.y, dm->dir.x,
**		dm->plane.z, dm->plane.y, dm->plane.x);
*/

void	render(t_doom *dm)
{
	threads(dm);
	if (dm->gamestarted)
	{
		if (dm->isoutline)
			post_effects(dm);
		draw_sprite(dm, 0, 0);
		draw_hud(dm);
		pickupitem(dm);
		//printf("POS %f %f %f\n", dm->pos.z, dm->pos.y, dm->pos.x);
		if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)dm->pos.x].b == 0)
			wingame(dm);
		render2(dm);
	}
	else
		gamestart(dm);
}
