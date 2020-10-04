/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:24:47 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/04 22:56:03 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALUE_H
# define VALUE_H

# define WINDOW		"DoomNukem"

# include "doom.h"

# define G_ERROR	"General error happened. Exiting program."
# define B_ARG		"Error: Bad argument."
# define USAGE		"Usage:	./doomnukem"
# define MEM_ERROR	"Not enough memory to allocate space for ./doomnukem."
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
# define DOOM_ERROR	"Cannot create corestruct."
# define PAD_ERROR	"Game controller was not found!"
# define LOD_ERROR	"Could not load the level"
# define VOID_OVER	"You fell off the world. Game over!"
# define NET_ERROR	"Could not start SDLNet."
# define CON_ERROR	"There was and issue with server connection!"

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
# define GFXCOUNT	43
# define THREADS	6
# define BUFFER		6
# define LIM		0.999999
# define LIMN		0.000001
# define IFRAME		50
# define DFRAME		35
# define PCOLL		0.2
# define OP			12
# define IP			"10.13.1.1"
# define BACKS		111
# define FRONTS		0
# define LEFTS		37
# define RIGHTS		74
# ifdef __APPLE__
#  define MUSIC		"Audio/Music/str4E.ogg"
# elif _WIN64
/*
** Missing some dll file so I'll just use the massive wav file for now.
*/
#  define MUSIC		"Audio/Music/str4E.wav"
# endif
/*
**# define IP		"10.13.1.1" Use this with Macs
**# define IP		"192.168.1.16"
*/

/*
** Keycodes - SDL defines by platform, ours is to fit old system
** and flat laziness not to replace the old ones + there are few
** platform specific keys we just standardized.
*/
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
# define KEY_SHIFT	SDL_SCANCODE_LSHIFT
# if __APPLE__
#  define OSCAM		1
#  define KEY_MIN	27
#  define KEY_PLU	24
#  define SCR_UPH	4
#  define SCR_DOWN	5
#  define NUM_PLU	69
#  define NUM_MIN	78
#  define SLASH		75
#  define STAR		67
#  define KEY_CTRL	256
# elif _WIN64
#  define OSCAM		10
#  define KEY_MIN	56
#  define KEY_PLU	45
#  define NUM_PLU	87
#  define NUM_MIN	86
#  define SLASH		84
#  define STAR		85
#  define KEY_CTRL	224
# endif

/*
** Colors
*/
# define COLOR_RED		16711680
# define COLOR_GREEN	65280
# define COLOR_YELLOW	16776960
# define COLOR_BLUE		255
# define COLOR_WHITE	16777215
# define COLOR_ORANGE	16742400
# define COLOR_SKIP		0xffff00ff
# define DARKEN			0xff7f7f7f
# define DARKEN2		0xff3f3f3f
# define DARKEN3		0xff1F1F1F

#endif
