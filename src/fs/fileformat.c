/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:13:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/18 13:26:58 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

// Remember to clear Windows spesific open functions for final version.

void	validate_flr(t_doom *dm, int y, int x, t_block blk)
{
	while (++y < dm->height)
	{
		x = -1;
		while (++x < dm->width)
			dm->area[dm->mxflr - 1][y][x] = blk;
	}
}

void	validate_map(t_doom *dm, int i, int a, t_block blk)
{
	while (++a < dm->mxflr)
	{
		i = -1;
		while (++i < dm->width)
		{
			dm->area[a][0][i] = blk;
			dm->area[a][dm->height - 1][i] = blk;
		}
		i = -1;
		while (++i < dm->height)
		{
			dm->area[a][i][0] = blk;
			dm->area[a][i][dm->width - 1] = blk;
		}
	}
	validate_flr(dm, -1, -1, blk);
}

void	fill_area(t_doom* dm, int y, int x)
{
	while (++x < 25)
		dm->area[dm->flr][y][x].b = 2;
}

int		templen(char **temp)
{
	int		i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}

void	comp_block(t_doom *dm, char **temp, int x, int y)
{
	dm->area[dm->flr][y][x].b = ft_atoi(temp[0]);
	dm->area[dm->flr][y][x].lgt = ft_atoi(temp[1]);
	dm->area[dm->flr][y][x].pt = ft_atoi(temp[2]);
	dm->area[dm->flr][y][x].pln = ft_atoi(temp[3]);
	dm->area[dm->flr][y][x].meta = ft_atoi(temp[4]);
	dm->area[dm->flr][y][x].hp = 100;
	if (dm->area[dm->flr][y][x].b == 7)
	{
		dm->spawn.x = x + 0.51;
		dm->spawn.y = y + 0.51;
		dm->spawn.z = dm->flr + 0.5;
		dm->area[dm->flr][y][x].b = 1;
	}
	if (dm->area[dm->flr][y][x].b > 8 || dm->area[dm->flr][y][x].b < 1)
		dm->area[dm->flr][y][x].b = 2;
	free_memory(temp);
}

int		get_next_matrix(t_doom *dm, char **temp, int x, int y)
{
	int		wid;

	wid = templen(temp);
	if (wid < 4)
		return (0);
	if (temp[0][0] == 'z')
		return (0);
	if (!(dm->area[dm->flr][y] = (MAPTYPE*)ft_memalloc(sizeof(MAPTYPE) * 25)))
		error_out(MEM_ERROR, dm);
	while (temp[x] && x < 25)
	{
		comp_block(dm, ft_strsplit(temp[x], ','), x, y);
		x++;
	}
	x--;
	while (++x < 25)
		dm->area[dm->flr][y][x].b = 2;
	return (1);
}

void	fileformat(int fd, t_doom *dm, int y)
{
	char	**temp;
	char	*gnl;

	while (get_next_line(fd, &gnl) == 1)
	{
		if (y > 25)
			error_out(FIL_ERROR, dm);
		temp = ft_strsplit(gnl, ' ');
		free(gnl);
		if (get_next_matrix(dm, temp, 0, y) == 0)
		{
			free_memory(temp);
			break;
		}
		y++;
		free_memory(temp);
		dm->height = y;
	}
	y--;
	while (++y < 25)
		fill_area(dm, y, 0);
	if (dm->height < 4)
		error_out(FIL_ERROR, dm);
}

void	comp_map(t_doom *dm)
{
	int		fd;
	char*	fpath;
	char*	path;

	dm->width = 25;
	if (!(dm->area = (MAPTYPE***)ft_memalloc(sizeof(MAPTYPE**) * 9)))
		error_out(MEM_ERROR, dm);
	path = SDL_GetBasePath();
	fpath = ft_strjoin(path, "map/1s");
	fd = open(fpath, O_RDONLY);
	SDL_free(path);
	ft_putendl(fpath);
	free(fpath);
	if (fd == -1)
		error_out(FLR_ERROR, dm);
	while (dm->flr < dm->mxflr)
	{
		//if (dm->flr >= dm->mxflr)
		//	break ;
		if (!(dm->area[dm->flr] = (MAPTYPE**)ft_memalloc(sizeof(MAPTYPE*) * 25)))
			error_out(MEM_ERROR, dm);
		fileformat(fd, dm, 0);
		dm->flr++;
	}
	//comp_sprites(dm);
	dm->height = 25;
	close(fd);
	validate_map(dm, -1, -1, (t_block){.b = 2, .lgt = 15, .pln = 15, .pt = 0});
}
