/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:13:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/14 14:12:54 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

// Remember to clear Windows spesific open functions for final version.

void	validate_map(t_doom *dm, int i, int a)
{
	while (++a < dm->mxflr)
	{
		i = -1;
		while (++i < dm->width)
		{
			if (dm->area[a][0][i] != 2)
				error_out(FIL_ERROR, dm);
			if (dm->area[a][dm->height - 1][i] != 2)
				error_out(FIL_ERROR, dm);
		}
		i = -1;
		while (++i < dm->height)
		{
			if (dm->area[a][i][0] != 2)
				error_out(FIL_ERROR, dm);
			if (dm->area[a][i][dm->width - 1] != 2)
				error_out(FIL_ERROR, dm);
		}
	}
}

void	fill_area(t_doom* dm, int y, int x)
{
	while (++x < 25)
		dm->area[dm->flr][y][x] = 2;
}

int		templen(char **temp)
{
	int		i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}

int		get_next_matrix(t_doom *dm, char **temp, int x, int y)
{
	int		wid;

	wid = templen(temp);
	//if (dm->width == -1)
	//dm->width = 25;
	if (wid < 4)
		return (0);
	if (temp[0][0] == 'z')
		return (0);
	if (!(dm->area[dm->flr][y] = (MAPTYPE*)malloc(sizeof(MAPTYPE) * 25)))
		error_out(MEM_ERROR, dm);
	while (temp[x] && x < 25)
	{
		dm->area[dm->flr][y][x] = ft_atoi(temp[x]);
		if (dm->area[dm->flr][y][x] == 7)
		{
			dm->spawn.x = x + 0.51;
			dm->spawn.y = y + 0.51;
			dm->spawn.z = dm->flr + 0.5;
			dm->area[dm->flr][y][x] = 1;
		}
		if (dm->area[dm->flr][y][x] > 7 || dm->area[dm->flr][y][x] < 1)
			dm->area[dm->flr][y][x] = 2;
		x++;
	}
	x--;
	while (++x < 25)
		dm->area[dm->flr][y][x] = 2;
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

void	comp_map(t_doom *dm)//, char *av)
{
	int		fd;
	char*	fpath;
	char*	path;

	dm->width = 25;
	if (!(dm->area = (MAPTYPE***)malloc(sizeof(MAPTYPE**) * 9)))
		error_out(MEM_ERROR, dm);
	path = SDL_GetBasePath();
	fpath = ft_strjoin(path, "map/1s");
	#if _WIN64
		_sopen_s(&fd, fpath, _O_RDONLY, _SH_DENYWR, _S_IREAD);
	#elif __APPLE__
		fd = open(fpath, O_RDONLY);
	#endif
	SDL_free(path);
	ft_putendl(fpath);
	free(fpath);
	if (fd == -1)
		error_out(FLR_ERROR, dm);
	while (dm->flr < dm->mxflr)
	{
		if (dm->flr >= dm->mxflr)
			return ;
		if (!(dm->area[dm->flr] = (MAPTYPE**)malloc(sizeof(MAPTYPE*) * 25)))
			error_out(MEM_ERROR, dm);
		//dm->flr += 49;
		//flrfl = ft_strjoin(av, (char*)&(dm->flr));
		/*if (dm->flr == 0)
			fpath = ft_strjoin(path, "map/1");
		else if (dm->flr == 1)
			fpath = ft_strjoin(path, "map/2");
		else if (dm->flr == 2)
			fpath = ft_strjoin(path, "map/3");
		else if (dm->flr == 3)
			fpath = ft_strjoin(path, "map/4");
		else if (dm->flr != dm->mxflr - 1)
			fpath = ft_strjoin(path, "map/5");
		else
			fpath = ft_strjoin(path, "map/6");*/
		//ft_putendl(flrfl);
		//fd = open(flrfl, O_RDONLY);
		//free(flrfl);
		//dm->flr -= 49;
		fileformat(fd, dm, 0);
		dm->flr++;
	}
	dm->height = 25;
	close(fd);
	//validate_map(dm, -1, -1);
}
