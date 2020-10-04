/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:19:27 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/30 12:19:29 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	write_int(int num, int fd)
{
	char	*out;

	out = ft_itoa(num);
	write(fd, out, ft_strlen(out));
	free(out);
}

void	write_file(t_doom *dm, int fd, int x, int y)
{
	char	c;
	char	*data;

	while (++y < 25)
	{
		x = -1;
		while (++x < 25)
		{
			write_int(dm->area[dm->flr][y][x].b, fd);
			write(fd, ",", 1);
			write_int(dm->area[dm->flr][y][x].lgt, fd);
			write(fd, ",", 1);
			write_int(dm->area[dm->flr][y][x].pt, fd);
			write(fd, ",", 1);
			write_int(dm->area[dm->flr][y][x].pln, fd);
			write(fd, ",", 1);
			write_int(dm->area[dm->flr][y][x].meta, fd);
			write(fd, " ", 1);
		}
		write(fd, "\n", 1);
	}
}

void	write_sprite(t_doom *dm, int fd, int i)
{
	while (++i < 9)
	{
		write_int(dm->spr[i].gfx, fd);
		write(fd, ",", 1);
		write_int(dm->spr[i].size * 10, fd);
		write(fd, ",", 1);
		write_int(dm->spr[i].hp, fd);
		write(fd, ",", 1);
		write_int(dm->spr[i].pos.z * 10, fd);
		write(fd, ",", 1);
		write_int(dm->spr[i].pos.y * 10, fd);
		write(fd, ",", 1);
		write_int(dm->spr[i].pos.x * 10, fd);
		write(fd, "\n", 1);
	}
}

int		save_file(t_doom *dm, int fd, char *file, int i)
{
	char	*path;
	char	*bpath;

	bpath = SDL_GetBasePath();
	path = ft_quadjoin(bpath, "map/", file, "");
	fd = open(path, O_WRONLY | O_TRUNC);
	free(path);
	SDL_free(bpath);
	if (fd == -1)
	{
		ft_putendl("Error saving the map!");
		return (0);
	}
	validate_map(dm, -1, -1, (t_block){.b = 2, .lgt = 15, .pln = 15, .pt = 0});
	while (++i < dm->mxflr)
	{
		dm->flr = i;
		write_file(dm, fd, -1, -1);
		write(fd, "z\n", 2);
	}
	write_sprite(dm, fd, -1);
	close(fd);
	ft_putendl("Saving successful!");
	return (1);
}
