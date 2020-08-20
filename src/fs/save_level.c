/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:01:11 by AleXwern          #+#    #+#             */
/*   Updated: 2020/07/31 15:01:11 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

// Remember to clear Windows spesific open functions for final version.

void	write_file(t_doom* dm, int fd, int x, int y)
{
	char	c;
	char	*data;

	while (++y < 25)
	{
		x = -1;
		while (++x < 25)
		{
			if (x >= dm->width || y >= dm->height)
				write(fd, "2 ", 2);
			else
			{
				c = dm->area[dm->flr][y][x].b + 48;
				write(fd, &c, 1);
				write(fd, ",", 1);
				data = ft_itoa(dm->area[dm->flr][y][x].lgt);
				write(fd, data, ft_strlen(data));
				write(fd, ",", 1);
				c = dm->area[dm->flr][y][x].pt + 48;
				write(fd, &c, 1);
				write(fd, ",", 1);
				free(data);
				data = ft_itoa(dm->area[dm->flr][y][x].pln);
				write(fd, data, ft_strlen(data));
				write(fd, ",", 1);
				free(data);
				c = dm->area[dm->flr][y][x].meta + 48;
				write(fd, &c, 1);
				write(fd, " ", 1);
			}
		}
		write(fd, "\n", 1);
	}
}

int		save_file(t_doom* dm, int fd, char* file, int i)
{
	char*	path;
	char*	bpath;

	bpath = SDL_GetBasePath();
	path = ft_quadjoin(bpath, "map/", file, "");
	#if _WIN64
		errno_t err = _sopen_s(&fd, path, O_WRONLY | O_CREAT | O_TRUNC, _SH_DENYNO, _S_IREAD | _S_IWRITE);
	#elif __APPLE__
		fd = open(path, O_WRONLY/* | O_CREAT | O_EXCL, 0644*/);
	#endif
	//printf("%s FD %d %d %d\n", path, fd, ft_strlen(file), err);
	free(path);
	SDL_free(bpath);
	if (fd == -1)
	{
		ft_putendl("Error saving the map!");
		return (0);
	}
	while (++i < dm->mxflr)
	{
		dm->flr = i;
		write_file(dm, fd, -1, -1);
		write(fd, "z\n", 2);
	}
	close(fd);
	ft_putendl("Saving successful!");
	return (1);
}