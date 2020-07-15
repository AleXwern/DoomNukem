/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:13:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/15 12:31:12 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	validate_map(t_doom *wlf, int i, int a)
{
	while (++a < wlf->mxflr)
	{
		i = -1;
		while (++i < wlf->width)
		{
			if (wlf->area[a][0][i] != 2)
				error_out(FIL_ERROR, wlf);
			if (wlf->area[a][wlf->height - 1][i] != 2)
				error_out(FIL_ERROR, wlf);
		}
		i = -1;
		while (++i < wlf->height)
		{
			if (wlf->area[a][i][0] != 2)
				error_out(FIL_ERROR, wlf);
			if (wlf->area[a][i][wlf->width - 1] != 2)
				error_out(FIL_ERROR, wlf);
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

int		get_next_matrix(t_doom *wolf, char **temp, int x, int y)
{
	int		wid;

	wid = templen(temp);
	if (wolf->width == -1)
		wolf->width = wid;
	if (wid < 4 || wid >= 35 || wolf->width != wid)
		return (0);
	if (!(wolf->area[wolf->flr][y] = (int*)malloc(sizeof(int) * wid)))
		error_out(MEM_ERROR, wolf);
	while (temp[x])
	{
		wolf->area[wolf->flr][y][x] = ft_atoi(temp[x]);
		if (wolf->area[wolf->flr][y][x] == 0)
			return (0);
		x++;
	}
	return (1);
}

void	fileformat(int fd, t_doom *wolf, int y)
{
	char	**temp;
	char	*gnl;

	while (get_next_line(fd, &gnl) == 1)
	{
		if (y >= 35)
			error_out(FIL_ERROR, wolf);
		temp = ft_strsplit(gnl, ' ');
		free(gnl);
		if (get_next_matrix(wolf, temp, 0, y) == 0)
		{
			free_memory(temp);
			error_out(FIL_ERROR, wolf);
		}
		y++;
		free_memory(temp);
	}
	if (wolf->height == -1)
		wolf->height = y;
	if (y != wolf->height || wolf->height < 4)
		error_out(FIL_ERROR, wolf);
}

void	comp_map(t_doom *wolf, char *av)
{
	int		fd;

	wolf->height = -1;
	wolf->width = -1;
	if (!(wolf->area = (int***)malloc(sizeof(int**) * 9)))
		error_out(MEM_ERROR, wolf);
	while (wolf->flr < wolf->mxflr)
	{
		if (wolf->flr >= wolf->mxflr)
			return ;
		if (!(wolf->area[wolf->flr] = (int**)malloc(sizeof(int*) * 35)))
			error_out(MEM_ERROR, wolf);
		//wolf->flr += 49;
		//flrfl = ft_strjoin(av, (char*)&(wolf->flr));
		char* path = SDL_GetBasePath();
		char* fpath;
		if (wolf->flr == 0)
			fpath = ft_strjoin(path, "map/1");
		else if (wolf->flr == 1)
			fpath = ft_strjoin(path, "map/2");
		else if (wolf->flr == 2)
			fpath = ft_strjoin(path, "map/3");
		else if (wolf->flr == 3)
			fpath = ft_strjoin(path, "map/4");
		else if (wolf->flr != wolf->mxflr - 1)
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
			error_out(FLR_ERROR, wolf);
		//wolf->flr -= 49;
		fileformat(fd, wolf, 0);
		wolf->flr++;
	}
	validate_map(wolf, -1, -1);
}
