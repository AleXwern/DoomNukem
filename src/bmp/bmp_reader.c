/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 13:21:45 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/25 13:21:45 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"
#include "../../includes/bmp.h"

int		read_to_pixdata(t_bmphead bmp, int bread, int fd)
{
	int		toread;
	char	dummy[2000];

	while (bread < bmp.pdoff)
	{
		toread = bmp.pdoff - bread;
		if (toread > 2000)
			toread = 2000;
		read(fd, dummy, toread);
		bread += toread;
		if (toread == 0)
			return (0);
	}
	if (bread > bmp.pdoff)
		return (0);
	return (1);
}

Uint32	*flip_arr(t_gfx gfx, char *corr)
{
	int		y;
	char	*dummy;

	y = gfx.hgt;
	if (!(dummy = (char*)ft_memalloc(gfx.wid * gfx.hgt * 4)))
		return (NULL);
	while (--y >= 0)
	{
		ft_memcpy(dummy + (gfx.hgt - y - 1) * (gfx.wid * 4), corr + (gfx.wid * y * 4), gfx.wid * 4);
	}
	free(corr);
	return ((Uint32*)dummy);
}

Uint32	*xbit_to_32(t_gfx gfx, int fd, int i, int b)
{
	char	*dummy;
	char	*corr;

	dummy = (char*)malloc(gfx.wid * gfx.hgt * 4);
	corr = (char*)malloc(gfx.wid * gfx.hgt * (gfx.bpp / 8));
	read(fd, corr, gfx.wid * gfx.hgt * (gfx.bpp / 8));
	while (i < gfx.wid * gfx.hgt * (gfx.bpp / 8))
	{
		if (b % 4 >= (gfx.bpp / 8))
		{
			dummy[b] = 0xff;
			b++;
		}
		dummy[b] = corr[i];
		i++;
		b++;
	}
	free(corr);
	return (flip_arr(gfx, dummy));
}

t_gfx	read_bmp(char *file, int fd, int bread)
{
	t_bmphead	bmp;
	t_bmpinfo	head;
	t_gfx		gfx;

	ft_bzero(&gfx, sizeof(t_gfx));
	fd = open(file, O_RDONLY);
	free(file);
	ft_putendl(file);
	//_sopen_s(&fd, file, _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
	if (fd == -1)
		return (gfx);
	bread = read(fd, &bmp, sizeof(bmp));
	printf("bm %04x\nfsize %d\nres1 %d\nres2 %d\npdoff %d\n", bmp.bm, bmp.fsize, bmp.res1, bmp.res2, bmp.pdoff);
	if (bmp.bm != 0x4d42)
		return (gfx);
	bread += read(fd, &head, sizeof(head));
	printf("hsize %d\nw %d\nh %d\npln %d\nbpp %d\ncmpr %d\nimgs %d\nxppm %d\nyppm %d\ncolc %d\nimpc %d\n", head.headsize, head.width, head.heigth, head.planes, head.bpp, head.compr, head.imgsize, head.xppm, head.yppm, head.colcount, head.impcol);
	if (!read_to_pixdata(bmp, bread, fd))
		return (gfx);
	gfx.wid = head.width;
	gfx.hgt = head.heigth;
	gfx.bpp = head.bpp;
	gfx.pitch = head.width * (gfx.bpp / 8);
	if (!(gfx.data = xbit_to_32(gfx, fd, 0, 0)))
		return (gfx);
	close(fd);
	return (gfx);
}