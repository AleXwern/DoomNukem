/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:13:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/30 12:51:22 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"
//todo crash
//fill empty block information
//general check different situations
//check value ranges
void	comp_block(t_doom *dm, char **temp, int x, int y)
{
	if (is_block_info_present(temp))
		fill_block(dm, x, y);
	else
	{
		if (*temp[0] < '0' || *temp[0] > '9')
			dm->area[dm->flr][y][x].b = 2;
		else//in case there are letters atoi returns 0 ugly fix
			dm->area[dm->flr][y][x].b = ft_atoi(temp[0]);
		dm->area[dm->flr][y][x].lgt = ft_atoi(temp[1]);
		dm->area[dm->flr][y][x].pt = ft_atoi(temp[2]);
		dm->area[dm->flr][y][x].pln = ft_atoi(temp[3]);
		dm->area[dm->flr][y][x].meta = ft_atoi(temp[4]);
	}
	if (dm->area[dm->flr][y][x].b == 7)
	{
		dm->spw.x = x + 0.51;
		dm->spw.y = y + 0.51;
		dm->spw.z = dm->flr + 0.5;
		dm->area[dm->flr][y][x].b = 1;
	}
	force_validate_block(dm, x, y);
	free_memory(temp);
}

int		rowformat(t_doom *dm, char **temp, int x, int y)
{
	if (temp[0][0] == 'z')
		return (0);
	if (!(dm->area[dm->flr][y] = (t_block*)ft_memalloc(sizeof(t_block) * 25)))
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

void	fill_area(t_doom *dm, int y, int x)
{
	if (!(dm->area[dm->flr][y] = (t_block*)ft_memalloc(sizeof(t_block) * 25)))
		error_out(MEM_ERROR, dm);
	while (++x < 25)
		fill_block(dm, x, y);
	dm->height = y;
}

void	floorformat(int fd, t_doom *dm, int y)
{
	char	**temp;
	char	*gnl;

	while (get_next_line(fd, &gnl) == 1)
	{
		if (y > 25)
			break ;
		temp = ft_strsplit(gnl, ' ');
		free(gnl);
		if (rowformat(dm, temp, 0, y) == 0)
		{
			free_memory(temp);
			break ;
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
	char	*fpath;
	char	*path;

	dm->width = 25;
	if (!(dm->area = (t_block***)ft_memalloc(sizeof(t_block**) * 9)))
		error_out(MEM_ERROR, dm);
	path = SDL_GetBasePath();
	fpath = ft_strjoin(path, "map/1s");
	fd = open(fpath, O_RDONLY);
	SDL_free(path);
	free(fpath);
	if (fd == -1)
		error_out(FLR_ERROR, dm);
	while (dm->flr < dm->mxflr)// If maxfloor shouldn't be modified in runtime, maybe change mxfloor to define
	{
		if (!(dm->area[dm->flr] = (t_block**)ft_memalloc(sizeof(t_block*)
			* 25)))
			error_out(MEM_ERROR, dm);
		floorformat(fd, dm, 0);
		dm->flr++;
	}
	comp_sprite(dm, -1, fd);
	dm->height = 25;
	close(fd);
	validate_map(dm, -1, -1, (t_block){.b = 2, .lgt = 15, .pln = 15, .pt = 0});
}
