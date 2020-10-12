/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:25:10 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/07 16:50:54 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

/*
** This header file is preserved for BMP file reading related utilities.
** First off we define 2 typedefs: WORD and DWORD.
** t_word is 16-bit and t_dword is 32-bit typedefs of respective integer types
** (short int and int). Typedefs are done with already renamed uintX_t just in
** case in some very specific intance the sizes of short int and/or int
** are not 16 and 32 bits.
** *******************************
** We also define 2 structs to handle the BMP file header part and pull out the
** necessary infomation in order to compile the file reading right.
** Key here is pragma pack which packs the struct so that we can read the file
** straight into the struct and not lose data BUT at the expense of code
** exploding in size.
** BMP reading is only ever used at the start of the program and in the instances
** where chooses to change texture pack so I'll justify the usage here.
*/
typedef uint16_t t_word;
typedef uint32_t t_dword;

# pragma pack(push, 1)

typedef	struct	s_bmphead
{
	t_word		bm;
	t_dword		fsize;
	t_word		res1;
	t_word		res2;
	t_dword		pdoff;
}				t_bmphead;

# pragma pack(pop)
# pragma pack(push, 1)

typedef struct	s_bmpinfo
{
	t_dword		headsize;
	t_dword		width;
	t_dword		heigth;
	t_word		planes;
	t_word		bpp;
	t_dword		compr;
	t_dword		imgsize;
	t_dword		xppm;
	t_dword		yppm;
	t_dword		colcount;
	t_dword		impcol;
}				t_bmpinfo;

# pragma pack(pop)

#endif
