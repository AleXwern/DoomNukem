/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:13:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:33:49 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

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
	if (dm->width == -1)
		dm->width = wid;
	if (wid < 4 || wid >= 35 || dm->width != wid)
		return (0);
	if (!(dm->area[dm->flr][y] = (int*)malloc(sizeof(int) * wid)))
		error_out(MEM_ERROR, dm);
	while (temp[x])
	{
		dm->area[dm->flr][y][x] = ft_atoi(temp[x]);
		if (dm->area[dm->flr][y][x] == 0)
			return (0);
		x++;
	}
	return (1);
}

void	fileformat(int fd, t_doom *dm, int y)
{
	char	**temp;
	char	*gnl;

	while (get_next_line(fd, &gnl) == 1)
	{
		if (y >= 35)
			error_out(FIL_ERROR, dm);
		temp = ft_strsplit(gnl, ' ');
		free(gnl);
		if (get_next_matrix(dm, temp, 0, y) == 0)
		{
			free_memory(temp);
			error_out(FIL_ERROR, dm);
		}
		y++;
		free_memory(temp);
	}
	if (dm->height == -1)
		dm->height = y;
	if (y != dm->height || dm->height < 4)
		error_out(FIL_ERROR, dm);
}

void	comp_map(t_doom *dm)//, char *av)
{
	int		fd;

	dm->height = -1;
	dm->width = -1;
	if (!(dm->area = (int***)malloc(sizeof(int**) * 9)))
		error_out(MEM_ERROR, dm);
	while (dm->flr < dm->mxflr)
	{
		if (dm->flr >= dm->mxflr)
			return ;
		if (!(dm->area[dm->flr] = (int**)malloc(sizeof(int*) * 35)))
			error_out(MEM_ERROR, dm);
		//dm->flr += 49;
		//flrfl = ft_strjoin(av, (char*)&(dm->flr));
		char* path = SDL_GetBasePath();
		char* fpath;
		if (dm->flr == 0)
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
			fpath = ft_strjoin(path, "map/6");
		#if _WIN64
			_sopen_s(&fd, fpath, _O_RDONLY, _SH_DENYWR, _S_IREAD);
		#elif __APPLE__
			fd = open(fpath, O_RDONLY);
		#endif
		SDL_free(path);
		ft_putendl(fpath);
		free(fpath);
		//ft_putendl(flrfl);
		//fd = open(flrfl, O_RDONLY);
		//free(flrfl);
		if (fd == -1)
			error_out(FLR_ERROR, dm);
		//dm->flr -= 49;
		fileformat(fd, dm, 0);
		dm->flr++;
	}
	validate_map(dm, -1, -1);
}
