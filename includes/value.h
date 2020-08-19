/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:24:47 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/17 15:50:37 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALUE_H
# define VALUE_H

# define WINDOW		"DoomNukem"

# include "doom.h"

//Data block is used to test how plane cuts. Replaced by t_block.zhal when ready.
#define	DATA_BLK	(11 / 15.0)
//#define	DATA_BLK	(0.5)

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
# define SDL_ERROR	"Could not initialize SDL library"
# define REN_ERROR	"Could not create renderer"
# define SPW_ERROR	"Spawn point is blocked."
# define WLF_ERROR	"Cannot create corestruct."
# define PAD_ERROR	"Game controller was not found!"
# define LOD_ERROR	"Could not load the level"
# define VOID_OVER	"You fell off the world. Game over!"

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
# define WINX		1080
# define WINY		720
# define MAXAGGRO	999999
# define GFXCOUNT	26
# define THREADS	6
# define BUFFER		6
# define LIM		0.999999

#if __APPLE__
# define OSCAM		1

# define ESC		SDL_SCANCODE_ESCAPE
# define KEY_ONE	SDL_SCANCODE_1
# define KEY_TWO	SDL_SCANCODE_2
# define KEY_TRE	SDL_SCANCODE_3
# define KEY_FOU	SDL_SCANCODE_4
# define KEY_FIV	SDL_SCANCODE_5
# define KEY_SIX	SDL_SCANCODE_6
# define KEY_SEV	SDL_SCANCODE_7
# define KEY_EIG	SDL_SCANCODE_8
# define KEY_NIN	SDL_SCANCODE_9
# define KEY_ZER	SDL_SCANCODE_0
# define KEY_MIN	27
# define KEY_PLU	24
# define KEY_Q		SDL_SCANCODE_Q
# define KEY_W		SDL_SCANCODE_W
# define KEY_E		SDL_SCANCODE_E
# define KEY_R		SDL_SCANCODE_R
# define KEY_T		SDL_SCANCODE_T
# define KEY_Y		SDL_SCANCODE_Y
# define KEY_U		SDL_SCANCODE_U
# define KEY_I		SDL_SCANCODE_I
# define KEY_O		SDL_SCANCODE_O
# define KEY_P		SDL_SCANCODE_P
# define KEY_A		SDL_SCANCODE_A
# define KEY_S		SDL_SCANCODE_S
# define KEY_D		SDL_SCANCODE_D
# define KEY_F		SDL_SCANCODE_F
# define KEY_G		SDL_SCANCODE_G
# define KEY_H		SDL_SCANCODE_H
# define KEY_J		SDL_SCANCODE_J
# define KEY_K		SDL_SCANCODE_K
# define KEY_L		SDL_SCANCODE_L
# define KEY_Z		SDL_SCANCODE_Z
# define KEY_X		SDL_SCANCODE_X
# define KEY_C		SDL_SCANCODE_C
# define KEY_V		SDL_SCANCODE_V
# define KEY_B		SDL_SCANCODE_B
# define KEY_N		SDL_SCANCODE_N
# define KEY_M		SDL_SCANCODE_M
# define SPACE		SDL_SCANCODE_SPACE
# define UP			SDL_SCANCODE_UP
# define DOWN		SDL_SCANCODE_DOWN
# define LEFT		SDL_SCANCODE_LEFT
# define RIGHT		SDL_SCANCODE_RIGHT
# define SCR_UPH	4
# define SCR_DOWN	5
# define NUM_PLU	69
# define NUM_MIN	78
# define SLASH		75
# define STAR		67
# define KEY_SHIFT	SDL_SCANCODE_LSHIFT
# define KEY_CTRL	256// dont use this. its a shortcut key on mac which just messes up the program.
#elif _WIN64
# define OSCAM		4

# define ESC		SDL_SCANCODE_ESCAPE
# define KEY_ONE	SDL_SCANCODE_1
# define KEY_TWO	SDL_SCANCODE_2
# define KEY_TRE	SDL_SCANCODE_3
# define KEY_FOU	SDL_SCANCODE_4
# define KEY_FIV	SDL_SCANCODE_5
# define KEY_SIX	SDL_SCANCODE_6
# define KEY_SEV	SDL_SCANCODE_7
# define KEY_EIG	SDL_SCANCODE_8
# define KEY_NIN	SDL_SCANCODE_9
# define KEY_ZER	SDL_SCANCODE_0
# define KEY_MIN	56
# define KEY_PLU	45
# define KEY_Q		SDL_SCANCODE_Q
# define KEY_W		SDL_SCANCODE_W
# define KEY_E		SDL_SCANCODE_E
# define KEY_R		SDL_SCANCODE_R
# define KEY_T		SDL_SCANCODE_T
# define KEY_Y		SDL_SCANCODE_Y
# define KEY_U		SDL_SCANCODE_U
# define KEY_I		SDL_SCANCODE_I
# define KEY_O		SDL_SCANCODE_O
# define KEY_P		SDL_SCANCODE_P
# define KEY_A		SDL_SCANCODE_A
# define KEY_S		SDL_SCANCODE_S
# define KEY_D		SDL_SCANCODE_D
# define KEY_F		SDL_SCANCODE_F
# define KEY_G		SDL_SCANCODE_G
# define KEY_H		SDL_SCANCODE_H
# define KEY_J		SDL_SCANCODE_J
# define KEY_K		SDL_SCANCODE_K
# define KEY_L		SDL_SCANCODE_L
# define KEY_Z		SDL_SCANCODE_Z
# define KEY_X		SDL_SCANCODE_X
# define KEY_C		SDL_SCANCODE_C
# define KEY_V		SDL_SCANCODE_V
# define KEY_B		SDL_SCANCODE_B
# define KEY_N		SDL_SCANCODE_N
# define KEY_M		SDL_SCANCODE_M
# define SPACE		SDL_SCANCODE_SPACE
# define UP			SDL_SCANCODE_UP
# define DOWN		SDL_SCANCODE_DOWN
# define LEFT		SDL_SCANCODE_LEFT
# define RIGHT		SDL_SCANCODE_RIGHT
# define NUM_PLU	87
# define NUM_MIN	86
# define SLASH		84
# define STAR		85
# define KEY_SHIFT	SDL_SCANCODE_LSHIFT
# define KEY_CTRL	224

# define SCR_UPH	-1
# define SCR_DOWN	-1
#endif

/*
** Colors
*/
# define			COLOR_RED 16711680
# define			COLOR_GREEN 65280
# define			COLOR_YELLOW 16776960
# define			COLOR_BLUE 255
# define			COLOR_WHITE 16777215
# define			COLOR_ORANGE 16742400
# define			COLOR_SKIP	0xffff00ff
# define			DARKEN	0xff7f7f7f
# define			DARKEN2	0xff3f3f3f
# define			DARKEN3	0xff1F1F1F

# define DARK1(X)	(X >> 1) & DARKEN;
# define DARK2(X)	(X >> 2) & DARKEN2;
# define DARK3(X)	(X >> 3) & DARKEN3;
# define ARGB(R, B, G)	(0xff000000 | (R << 16) | (B << 8) | G)
# define R(X)		((X >> 16) & 0xff)
# define G(X)		((X >> 8) & 0xff)
# define B(X)		(X & 0xff)

#endif
