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

#pragma pack(push, 1)

typedef	struct		s_bmphead
{
	unsigned short	bm;
	unsigned int	fsize;
	unsigned short	res1;
	unsigned short	res2;
	unsigned int	pdoff;
}					t_bmphead;

#pragma pack(pop)

#pragma pack(push, 1)

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

#pragma pack(pop)

#define	FTL32(X)	(X & 0xff000000) >> 24
#define	STT32(X)	(X & 0xff0000) >> 8
#define	TTS32(X)	(X & 0xff00) << 8
#define	LTF32(X)	(X & 0xff) << 24
#define	END32(X)	(FTL32(X) | STT32(X) | TTS32(X) | LTF32(X))
#define	FTL16(X)	(X & 0xf000) >> 12
#define	STT16(X)	(X & 0xf00) >> 4
#define	TTS16(X)	(X & 0xf0) << 4
#define	LTF16(X)	(X & 0xf) << 12
#define	END16(X)	(FTL16(X) | STT16(X) | TTS16(X) | LTF16(X))
