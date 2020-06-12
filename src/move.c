/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:01:53 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/12 15:50:20 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/value.h"
#include "../includes/wolf.h"

#include <stdio.h>//

void	cam_udy(t_wolf *wlf, double olddiry, double oldplaney)
{
	double		olddirx;
	double		oldplanex;

	if (wlf->keyw)
	{
		olddiry = wlf->diry;
		wlf->diry = wlf->diry * cos(wlf->rotsp) - wlf->dirz * sin(wlf->rotsp);
		wlf->dirz = olddiry * sin(wlf->rotsp) + wlf->dirz * cos(wlf->rotsp);
		oldplaney = wlf->planey;
		wlf->planey = wlf->planey * cos(wlf->rotsp) - wlf->planez *
				sin(wlf->rotsp);
		wlf->planez = oldplaney * sin(wlf->rotsp) + wlf->planez *
				cos(wlf->rotsp);
		wlf->sbox += WINX / 64;
	}
	if (wlf->keys)
	{
		olddiry = wlf->diry;
		wlf->diry = wlf->diry * cos(-wlf->rotsp) - wlf->dirz * sin(-wlf->rotsp);
		wlf->dirz = olddiry * sin(-wlf->rotsp) + wlf->dirz * cos(-wlf->rotsp);
		oldplaney = wlf->planey;
		wlf->planey = wlf->planey * cos(-wlf->rotsp) - wlf->planez *
				sin(-wlf->rotsp);
		wlf->planez = oldplaney * sin(-wlf->rotsp) + wlf->planez *
				cos(-wlf->rotsp);
		wlf->sbox += WINX / 64;
	}
	if (wlf->keya)
	{
		olddirx = wlf->dirx;
		wlf->dirx = wlf->dirx * cos(wlf->rotsp) + wlf->dirz * sin(wlf->rotsp);
		wlf->dirz = -olddirx * sin(wlf->rotsp) + wlf->dirz * cos(wlf->rotsp);
		oldplanex = wlf->planex;
		wlf->planex = wlf->planex * cos(wlf->rotsp) + wlf->planez *
				sin(wlf->rotsp);
		wlf->planez = -oldplanex * sin(wlf->rotsp) + wlf->planez *
				cos(wlf->rotsp);
		wlf->sbox += WINX / 64;
	}
	if (wlf->keyd)
	{
		olddirx = wlf->dirx;
		wlf->dirx = wlf->dirx * cos(-wlf->rotsp) + wlf->dirz * sin(-wlf->rotsp);
		wlf->dirz = -olddirx * sin(-wlf->rotsp) + wlf->dirz * cos(-wlf->rotsp);
		oldplanex = wlf->planex;
		wlf->planex = wlf->planex * cos(-wlf->rotsp) + wlf->planez *
				sin(-wlf->rotsp);
		wlf->planez = -oldplaney * sin(-wlf->rotsp) + wlf->planez *
				cos(-wlf->rotsp);
		wlf->sbox += WINX / 64;
	}
	printf("Matrices:\n	DIR		PLANE\nX	%f	%f\nY	%f	%f\nZ	%f	%f\n", wlf->dirx, wlf->planex, wlf->diry, wlf->planey, wlf->dirz, wlf->planez);
}

void	move_l(t_wolf *wlf, double olddirx, double oldplanex)
{
	if (wlf->keyleft)
	{
		olddirx = wlf->dirx;
		wlf->dirx = wlf->dirx * cos(wlf->rotsp) - wlf->diry * sin(wlf->rotsp);
		wlf->diry = olddirx * sin(wlf->rotsp) + wlf->diry * cos(wlf->rotsp);
		oldplanex = wlf->planex;
		wlf->planex = wlf->planex * cos(wlf->rotsp) - wlf->planey *
				sin(wlf->rotsp);
		wlf->planey = oldplanex * sin(wlf->rotsp) + wlf->planey *
				cos(wlf->rotsp);
		wlf->sbox += WINX / 64;
	}
}

int		move_lr(t_wolf *wlf)
{
	double	olddirx;
	double	oldplanex;

	if (wlf->keyright)
	{
		olddirx = wlf->dirx;
		wlf->dirx = wlf->dirx * cos(-wlf->rotsp) - wlf->diry * sin(-wlf->rotsp);
		wlf->diry = olddirx * sin(-wlf->rotsp) + wlf->diry * cos(-wlf->rotsp);
		oldplanex = wlf->planex;
		wlf->planex = wlf->planex * cos(-wlf->rotsp) - wlf->planey *
				sin(-wlf->rotsp);
		wlf->planey = oldplanex * sin(-wlf->rotsp) + wlf->planey *
				cos(-wlf->rotsp);
		wlf->sbox -= WINX / 64;
	}
	move_l(wlf, olddirx, oldplanex);
	printf("Matrices:\n	DIR		PLANE\nX	%f	%f\nY	%f	%f\nZ	%f	%f\n", wlf->dirx, wlf->planex, wlf->diry, wlf->planey, wlf->dirz, wlf->planez);
	return (0);
}

int		move_fb(t_wolf *wlf)
{
	if (wlf->keyup)
	{
		if (wlf->map[(int)wlf->posz][(int)(wlf->posy + wlf->diry
				* wlf->movsp)][(int)wlf->posx] <= 1)
			wlf->posy += wlf->diry * wlf->movsp;
		if (wlf->map[(int)wlf->posz][(int)wlf->posy][(int)(wlf->posx
				+ wlf->dirx * wlf->movsp)] <= 1)
			wlf->posx += wlf->dirx * wlf->movsp;
	}
	if (wlf->keydown)
	{
		if (wlf->map[(int)wlf->posz][(int)(wlf->posy - wlf->diry
				* wlf->movsp)][(int)wlf->posx] <= 1)
			wlf->posy -= wlf->diry * wlf->movsp;
		if (wlf->map[(int)wlf->posz][(int)wlf->posy][(int)(wlf->posx
				- wlf->dirx * wlf->movsp)] <= 1)
			wlf->posx -= wlf->dirx * wlf->movsp;
	}
	return (0);
}

void	strafe(t_wolf *wlf, double dirxtemp, double dirytemp)
{
	if (wlf->keyq)
	{
		if (wlf->diry < 0)
		{
			if (wlf->map[(int)wlf->posz][(int)(wlf->posy - wlf->diry
					* wlf->movsp)][(int)wlf->posx] <= 1)
				wlf->posy -= (wlf->diry + 1) * wlf->movsp;
		}
		else
		{
			if (wlf->map[(int)wlf->posz][(int)(wlf->posy - wlf->diry
					* wlf->movsp)][(int)wlf->posx] <= 1)
				wlf->posy += (wlf->diry - 1) * wlf->movsp;
		}
		if (wlf->dirx < 0)
		{
			if (wlf->map[(int)wlf->posz][(int)wlf->posy][(int)(wlf->posx
					- wlf->dirx * wlf->movsp)] <= 1)
				wlf->posx -= (wlf->dirx + 1) * wlf->movsp;
		}
		else
		{
			if (wlf->map[(int)wlf->posz][(int)wlf->posy][(int)(wlf->posx
					- wlf->dirx * wlf->movsp)] <= 1)
				wlf->posx += (wlf->dirx - 1) * wlf->movsp;
		}
	}
	if (wlf->keye)
	{
		if (wlf->diry >= 0)
		{
			dirxtemp = wlf->dirx - 1;
		}
		else if (wlf->diry < 0)
		{
			dirxtemp = wlf->dirx + 1;
		}
		if (wlf->dirx >= 0)
		{
			dirytemp = wlf->diry - 1;
		}
		else if (wlf->dirx < 0)
		{
			dirytemp = wlf->diry + 1;
		}
		wlf->posx += dirxtemp * wlf->movsp;
		wlf->posy += dirytemp * wlf->movsp;
	}
}
