/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:24:47 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/11 16:57:28 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALUE_H
# define VALUE_H

/*
** Error messages.
*/
# define G_ERROR	"General error happened. Exiting program."
# define B_ARG		"Error: Bad argument."
# define USAGE		"Usage:	./wolf3d [tileset] [floors] [FOLDER name]"
# define MEM_ERROR	"Not enough memory to allocate space for ./wolf3d."
# define T_ERROR	"There was a threading problem."
# define OOPS		"This should never be shown. Everyone panic!"
# define FINE		"Successfully exiting program."
# define WIN_ERROR	"Could not create a window."
# define IMG_ERROR	"Could not create a image."
# define MLX_ERROR	"Could not cleate MLX pointer."
# define GFX_ERROR	"GFX doesn't exist. Put it back!"
# define FLR_ERROR	"Not enough floors in given folder."
# define STR_ERROR	"Stairs don't lead anywhere."
# define FIL_ERROR	"File incorrectly formated."
# define LAB_OUT	"Reached the end of the labyrinth. Clap clap!"
# define SPW_ERROR	"Spawn point is blocked."
# define WLF_ERROR	"Cannot create corestruct."
# define GAME_OVER	"Your party has fallen. Game over!"

# define HIT_OPP	" dealt damage to "
# define CHA_OPP	" charged at "
# define HEAL_OPP	" healed "
# define DEF_OPP	" defended"
# define LOST_HP	"Damage dealt: "
# define GET_HP		"Damage healed: "
# define DEF_HP		"'s damage taken will be reduced"

/*
** Static values.
*/
# define WINX		2000
# define WINY		700
# define MAXAGGRO	999999
# define GFXCOUNT	23

/*
** Tagged keys.
*/
# define ESC		53
# define KEY_R		15
# define KEY_C		8
# define KEY_T		17
# define KEY_ONE	18
# define KEY_TWO	19
# define KEY_TRE	20
# define KEY_FOU	21
# define SPACE		49
# define UP			126
# define DOWN		125
# define LEFT		124
# define RIGHT		123
# define SCR_UPH	4
# define SCR_DOWN	5
# define NUM_PLU	69
# define NUM_MIN	78
# define SLASH		75
# define STAR		67
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_Q		12
# define KEY_E		14
# define KEY_SHIFT	257

/*
** Keys for laptop if needed.
** # define ESC		65307
** # define KEY_R		15
** # define KEY_C		99
** # define KEY_T		116
** # define KEY_ONE	18
** # define KEY_TWO	19
** # define KEY_TRE	20
** # define KEY_FOU	21
** # define SPACE		32
** # define UP			65362
** # define DOWN		65364
** # define LEFT		65363
** # define RIGHT		65361
** # define SCR_UPH	4
** # define SCR_DOWN	5
** # define NUM_PLU	69
** # define NUM_MIN	78
** # define SLASH		75
** # define STAR		67
*/
#endif
