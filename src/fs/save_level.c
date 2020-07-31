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

int		save_file(t_doom* dm, int fd, char file, int i)
{
	char*	path;

	while (++i < dm->mxflr)
	{
		path = ft_strjoin("maps/", &file);
		#if _WIN64
		_sopen_s(&fd, path, _O_WRONLY, _SH_DENYRD, _S_IWRITE);
		#elif __APPLE__
		fd = open(path, O_RDONLY, O_CREAT);
		#endif

	}
}