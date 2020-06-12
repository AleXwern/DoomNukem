/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/12 14:13:25 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

#include <stdio.h>

void	wolf_default(t_wolf *wlf)
{
	wlf->flr = 0;
	wlf->posx = 2.5;
	wlf->posy = 2.5;
	wlf->posz = 2.5;
	wlf->dir.x = 1.0;
	wlf->dir.y = 0.0;
	wlf->dir.z = 0.0;
	//wlf->dirx = 1.0;
	//wlf->diry = 0.0;
	//wlf->dirz = 0.0;
	wlf->plane.x = 0.0;
	wlf->plane.y = 0.5 / ((double)WINY / (double)WINX);
	wlf->plane.z = 0.5;
	//wlf->planex = 0.0;
	//wlf->planey = 0.5 / ((double)WINY / (double)WINX);
	//wlf->planez = 0.5;
	wlf->rotation = 0;
	wlf->rotsp = 0.05;
	wlf->movsp = 0.06;
	wlf->fcomb = 0;
	wlf->rng = 0.0;
	wlf->texbool = 1;
	wlf->sbox = WINX / 2;
	wlf->mxflr--;
	wlf->cur = 0;
	wlf->sel = -1;
	wlf->plr = 0;
	wlf->plrck = 0;
	wlf->keyminus = 0;
	wlf->keyplus = 0;
	wlf->cycle = &render;
}

void	error_out(char *msg, t_wolf *wolf)
{
	ft_putendl(msg);
	if (!ft_strcmp(msg, WLF_ERROR))
		exit(0);
	if (!ft_strcmp(msg, FLR_ERROR))
		wolf->mxflr = wolf->flr - 49;
	wolf->fcomb = 1;
	if (wolf->gfx)
		destroy_gfx(wolf, -1);
	if (wolf->map)
		free_map(wolf, -1, -1);
	if (wolf->winb == 1)
		mlx_destroy_window(wolf->mlx, wolf->win);
	system("leaks doomdemo");
	exit(0);
}

void	free_memory(char **arr)
{
	int y;

	y = 0;
	while (arr[y])
		y++;
	while (y >= 0)
		ft_strdel(&arr[y--]);
	free(arr);
	arr = NULL;
}

void	setup(t_wolf *wolf)
{
	wolf_default(wolf);
	if (wolf->map[2][(int)wolf->posy][(int)wolf->posx] != 1)
		error_out(SPW_ERROR, wolf);
	mlx_hook(wolf->win, 2, 0, key_hold, wolf);
	mlx_hook(wolf->win, 3, 0, key_release, wolf);
	mlx_hook(wolf->win, 17, 0, x_press, wolf);
	mlx_loop_hook(wolf->mlx, move, wolf);
	wolf->cycle(wolf);
	mlx_loop(wolf->mlx);
}

int		main(int ac, char **av)
{
	t_wolf	*wolf;

	if (!(wolf = (t_wolf*)malloc(sizeof(t_wolf))))
		error_out(WLF_ERROR, wolf);
	wolf->winb = 0;
	wolf->flr = 0;
	if (ac != 4)
		error_out(USAGE, wolf);
	wolf->tile = ft_atoi(av[1]);
	if (wolf->tile < 1 || wolf->tile > 6)
		error_out(USAGE, wolf);
	wolf->mxflr = ft_atoi(av[2]);
	if (wolf->mxflr < 1 || wolf->mxflr > 9)
		error_out(USAGE, wolf);
	if (!(wolf->mlx = mlx_init()))
		error_out(MLX_ERROR, wolf);
	if (!(wolf->win = mlx_new_window(wolf->mlx, WINX, WINY, WINDOW)))
		error_out(WIN_ERROR, wolf);
	wolf->winb = 1;
	comp_map(wolf, av[3]);
	comp_gfx(wolf, 0);
	setup(wolf);
	return (0);
}
