/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 13:22:03 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/25 13:22:03 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H
# pragma pack(push, 1)

typedef	struct		s_bmphead
{
	unsigned short	bm;
	unsigned int	fsize;
	unsigned short	res1;
	unsigned short	res2;
	unsigned int	pdoff;
}					t_bmphead;

# pragma pack(pop)
# pragma pack(push, 1)

typedef struct		s_bmpinfo
{
	unsigned int	headsize;
	unsigned int	width;
	unsigned int	heigth;
	unsigned short	planes;
	unsigned short	bpp;
	unsigned int	compr;
	unsigned int	imgsize;
	unsigned int	xppm;
	unsigned int	yppm;
	unsigned int	colcount;
	unsigned int	impcol;
}					t_bmpinfo;

# pragma pack(pop)

#endif
