/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:19:27 by anystrom          #+#    #+#             */
/*   Updated: 2020/12/07 14:59:02 by vkeinane         ###   ########.fr       */
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

void	write_sprite(t_sprite *spr, int fd, int i, int len)
{
	while (++i < len)
	{
		write_int(spr[i].gfx, fd);
		write(fd, ",", 1);
		if (len == SPR)
			write_int(spr[i].dead, fd);
		else
			write_int(0, fd);
		write(fd, ",", 1);
		write_int(spr[i].hp, fd);
		write(fd, ",", 1);
		write_int(spr[i].pos.z * 10, fd);
		write(fd, ",", 1);
		write_int(spr[i].pos.y * 10, fd);
		write(fd, ",", 1);
		write_int(spr[i].pos.x * 10, fd);
		write(fd, ",", 1);
		write_int(spr[i].respawn, fd);
		write(fd, "\n", 1);
	}
	if (len == SPR)
		write(fd, "Object\n", 7);
	else
		write(fd, "end\n", 4);
}

int		save_file(t_doom *dm, int fd, char *file, int i)
{
	char	*path;
	char	*bpath;

	fd = save_init(&path, &bpath, &file);
	if (fd == -1)
	{
		ft_putendl("Error saving the map!");
		return (0);
	}
	validate_map(dm, -1, -1, (t_block){.b = 2, .lgt = 15, .pln = 15, .pt = 0});
	while (++i < MXFLR)
	{
		dm->flr = i;
		write_file(dm, fd, -1, -1);
		if (i == MXFLR - 1)
			write(fd, "Sprite\n", 7);
		else
			write(fd, "z\n", 2);
	}
	write_sprite(dm->spr, fd, -1, SPR);
	write_sprite(dm->obj, fd, -1, OBJ);
	close(fd);
	ft_putendl("Saving successful!");
	return (1);
}
