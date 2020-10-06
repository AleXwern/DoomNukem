/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:31:21 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/06 17:04:57 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# if _WIN64
#  define _CRT_SECURE_NO_WARNINGS
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdio.h> //remove when project is done!

# if _WIN64

/*
** Windows x64 OS spesific includes
** Mainly to get win spesific versions of C functions like open -> _sopen_s
** to work because of required flags.
*/
#  include "SDL.h"
#  include "SDL_net.h"
#  include "SDL_mixer.h"
#  include <windows.h>
#  include <share.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <io.h>
#  include <string.h>
#  include "windoom.h"
# elif __APPLE__

/*
** Apple Mac OS specific includes
*/
#  include "../frameworks/SDL2.framework/Headers/SDL.h"
#  include "../frameworks/SDL2_net.framework/Headers/SDL_net.h"
#  include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# endif

typedef struct		s_key
{
	Sint8			esc;
	Sint8			one;
	Sint8			two;
	Sint8			three;
	Sint8			four;
	Sint8			five;
	Sint8			six;
	Sint8			seven;
	Sint8			eight;
	Sint8			nine;
	Sint8			zero;
	Sint8			q;
	Sint8			w;
	Sint8			e;
	Sint8			r;
	Sint8			t;
	Sint8			y;
	Sint8			u;
	Sint8			i;
	Sint8			o;
	Sint8			p;
	Sint8			a;
	Sint8			s;
	Sint8			d;
	Sint8			f;
	Sint8			g;
	Sint8			h;
	Sint8			j;
	Sint8			k;
	Sint8			l;
	Sint8			z;
	Sint8			x;
	Sint8			c;
	Sint8			v;
	Sint8			b;
	Sint8			n;
	Sint8			m;
	Sint8			space;
	Sint8			left;
	Sint8			right;
	Sint8			down;
	Sint8			up;
	Sint8			plus;
	Sint8			minus;

}					t_key;

/*
** Vector structs
** Both have same XYZ variables to represent direction
** in 3D space.
** t_vector is double form to calculate precice positions and
** t_ivector is handier way to pull data from arrays without
** having to use typecasting.
*/

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_ivector
{
	int				x;
	int				y;
	int				z;
}					t_ivector;

/*
** GFX library
** 0 = Skybox
** 1 = Floor
** 2 = Wall
** 3 = Stairs up
** 4 = Stairs down
** 5 = Door
** 6 = Secret warp
**
** t_img is the screen data itself
** t_gfx is different graphics that will be used to render the world.
*/

typedef struct		s_img
{
	SDL_Surface		*tex;
	SDL_Texture		*img;
	Uint32			*data;
}					t_img;

typedef struct		s_gfx
{
	Uint32			*data;
	Uint32			wid;
	Uint32			hgt;
	Uint32			bpp;
	Uint32			pitch;
	Uint32			x;
	Uint32			y;
}					t_gfx;

/*
** Level editor struct
** Maybe not needed but my own reasoning at the time was to minimize the
** size of the main struct even is a little bit.
*/

typedef struct		s_editor
{
	Uint8			flr;
	Uint8			quit;
	t_vector		spawn;
	t_vector		end;
	Sint8			cur;
	Uint8			blk;
	//t_block		blk;
	Sint8			options[5];
	double			maxval[5];
	Sint8			minval[5];
	char			*opt[11];
	SDL_Event		ev;
	Sint8			marea;
	Sint8			mslider;
	Sint8			mblock;
	Sint8			mcopy;
}					t_editor;

/*
**	Datablock for well... blocks
**	b	- blocktype (main texture and main function)
**	lgt	- lightning of the block 0-15
**	pt	- planetype, how block is split
**	pln	- plane, where it's split 0-15
**	meta- extra data for misc features
**	hp	- used to determine block integrity
**	PLANE TYPE
**	0 - none
**	1 - Z, filled up
**	2 - Z, filled down
**	3 - Y, filled N
**	4 - Y, filled S
**	5 - X, filled W
**	6 - X, filled E
*/
typedef struct		s_block
{
	Uint8			b;
	Uint8			lgt;
	Uint8			pt;
	Uint8			pln;
	Uint8			meta;
	Uint8			hp;
}					t_block;

typedef struct		s_sprite
{
	int				id;
	int				gfx;
	t_vector		pos;
	t_vector		dir;
	t_vector		mov;
	int				hp;
	int				size;
	double			dist;
	int				iframe;
	Uint32			x;
	Uint32			y;
	int				frame;
	t_vector		face;
	char			move;
}					t_sprite;

/*
** Structs to pass data to and back with server.
** We want to minimize the traffic so we only send our position aka t_bulk
** but we want everyone's positions so t_chunck is list of those + our server
** ID at that given transmission.
*/

typedef struct		s_bulk
{
	t_vector		pos;
	t_vector		dir;
	t_vector		prj;
	int				hp;
	int				gfx;
}					t_bulk;

typedef struct		s_chunk
{
	t_bulk			plr[5];
	int				id;
}					t_chunk;

/*
** win	= Window pointer
** pc	= player info
** tile	= graphic set
** gfx	= library of graphics
** menucur	= COMBAT: cursor position
** menugfx	= COMBAT: menu gfx
** img	= current scene render
** chara	= list of party members
** x	= screen X pos
** y	= screen Y pos
** spawn	= spawn XY pos
** hold
** flr
** mapset
** map
** winb
** rng
** fcomb
** aggro
** iscombat
** ismenu
*/

typedef struct		s_doom
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Surface		*surf;
	SDL_Texture		*tex;
	t_img			img;
	SDL_Event		event;
	SDL_Thread		**threads;
	IPaddress		ip;
	TCPsocket		sock;
	int				netstat;
	int				person;
	struct s_doom	*data_r;
	struct s_doom	*dm;
	int				id;
	int				*claimline;
	int				*done;
	float			*wallarr;
	float			*winarr;
	int				*maparr;
	Uint32			*window;
	int				killthread;
	int				tile;
	t_gfx			*gfx;
	t_sprite		spr[9];
	t_sprite		prj[9];
	t_sprite		obj[9];
	Uint32			gfram;
	int				gfxcount;
	int				height;
	int				width;
	int				winh;
	int				winw;
	int				owinw;
	int				owinh;
	void			(*cycle)(struct s_doom*);
	void			(*keyck)(struct s_doom*);
	char			*syssmg[2];
	Uint32			iframe;
	int				cur;
	int				sel;
	int				plr;
	int				plrck;
	int				adj;
	int				wincol;
	int				rcol;
	int				lgt;
	int				x;
	int				y;
	int				hold;
	int				flr;
	int				mxflr;
	int				mapset;
	t_block			***area;
	t_block			blk;
	int				winb;
	int				texbool;
	int				rng;
	int				fcomb;
	int				aggro;
	int				iscombat;
	int				ismenu;
	int				sy;
	int				sx;
	Uint32			black;
	int				xmax;
	int				stepx;
	int				stepy;
	int				stepz;
	int				hit;
	int				hithalf;
	int				invincible;
	t_vector		hitpos;
	int				side;
	double			lineh;
	int				start;
	int				end;
	int				texnum;
	int				texx;
	int				texy;
	Uint32			col;
	int				sbox;
	int				sboy;
	int				cellx;
	int				celly;
	int				cellz;
	int				tx;
	int				ty;
	int				tz;
	int				rotation;
	double			poszz;
	int				airbrn;
	t_vector		spw;
	t_vector		pos;
	t_vector		gravity;
	t_vector		fallsp;
	t_vector		dir;
	t_vector		plane;
	t_vector		map;
	t_vector		tmap;
	t_vector		cam;
	t_vector		rayd;
	t_vector		rmap1;
	t_vector		rmap2;
	t_vector		rtex;
	t_vector		rayd0;
	t_vector		rayd1;
	t_vector		sided;
	t_vector		tsided;
	t_vector		deltad;
	t_vector		flstep;
	t_vector		floor;
	t_ivector		texshift;
	t_vector		sprite;
	t_vector		transf;
	t_vector		min;
	t_vector		max;
	double			mina;
	double			maxa;
	int				drwspr;
	double			invdet;
	double			walldist;
	double			rowdist;
	double			movsp;
	double			rotsp;
	double			step;
	double			wallx;
	double			texpos;
	int				isclick;
	t_key			key;
	int				crouching;
	int				uncrouch;
	int				mouseprevx;
	int				mouseprevy;
	int				*options[25];
	double			maxvalue[25];
	char			*optext[25];
	int				minopt;
	int				isoptions;
	int				isfpscap;
	int				limit;
	int				isoutline;
	int				isgravity;
	int				shift;
	SDL_Thread		*fpsthread;
	Uint32			fps;
	char			*fpschar;
	int				trx;
	int				fpscap;
	int				prefps;
	int				buffer;
	double			camshift;
	int				mousemovement;

	int				gun;
	int				shooting;
	int				reloading;
	int				ani;
	int				frm;
	int				magazine;
	int				hp;
	int				alive;
	int				keycard;
	int				chestopened;
	int				drawgunandkeycard;

	char			slidedoor;
	t_block			*slideblock;
	int				doorani;
	int				doorfrm;

	int				volume;
	Mix_Music		*music;
	Mix_Chunk		*reload;
	Mix_Chunk		*gunshot;
	Mix_Chunk		*jetpack;
	Mix_Chunk		*doorsound;
	Mix_Chunk		*doorknob;
	Mix_Chunk		*teleport;
	Mix_Chunk		*ishit;
	Mix_Chunk		*death;
	Mix_Chunk		*mondeath;
	Mix_Chunk		*windowbrk;
	Mix_Chunk		*doorsliding;
}					t_doom;

Uint32				avg_color(Uint32 rcol, Uint32 col);
Uint32				color_shift(Uint32 color, double shift, t_doom *dm,
						Uint32 ret);
Uint32				rl_color(int lgt, Uint32 col);

double				dot_prd(t_vector v, t_vector u);
double				tri_pythagor(t_vector f, t_vector s);

int					check_sprite_dist(t_doom *dm, double mov, int i);
int					connect_server(t_doom *dm);
int					foe_ismoving(t_sprite *spr);
int					fps_capper(void *ptr);
int					fps_counter(void *ptr);
int					get_x(int pc);
int					get_y(int pc);
int					interact(t_doom *dm);
int					key_hold(int key, t_doom *dm);
int					key_release(int key, t_doom *dm);
int					light_map(t_vector map, int side, t_block ***area);
int					get_blocklight(t_doom *dm, t_vector pos);
int					load_level(t_editor *le, t_doom *dm);
int					mouse_move(int x, int y, t_doom *dm);
int					move(t_doom *dm);
int					move_lr(t_doom *dm);
int					renthread(void *ptr);
int					save_file(t_doom *dm, int fd, char *file, int i);
int					send_pos(t_doom *dm);
int					tex_check(t_doom *dm);
int					x_press(t_doom *dm);

t_gfx				read_bmp(char *file, int fd, int bread);
t_img				init_image(t_doom *dm);
t_vector			cross_prd(t_vector v, t_vector u);
t_vector			oper_vect(t_vector v, t_vector u, char o);

void				ai_shooting(t_doom *dm, int i);
void				alloc_vram(t_doom *dm);
void				cam_udy(t_doom *dm);
void				check_area(t_editor *le, SDL_Event ev);
void				check_hit(t_doom *dm, int i, int x);
void				chest_object(t_doom *dm, int i, int y, int x);
void				comp_gfx(t_doom *dm);
void				comp_map(t_doom *dm);
void				curt_down(t_doom *dm);
void				curt_up(t_doom *dm);
void				demodraw_sprite(t_doom *dm);
void				destroy_gfx(t_doom *dm, int i);
void				doom_default(t_doom *dm);
void				draw_ammo(t_doom *dm);
void				draw_bg(t_doom *dm, t_gfx gfx);
void				draw_blk_select(t_doom *dm, t_editor *le, int x, int y);
void				draw_crosshair(t_doom *dm);
void				draw_editor_cursor(t_doom *dm, t_editor *le, int x, int y);
void				draw_gfx(t_doom *dm, t_gfx gfx, Uint32 x, Uint32 y);
void				draw_gun(t_doom *dm);
void				draw_hp(t_doom *dm);
void				draw_hud(t_doom *dm);
void				draw_level_screen(t_doom *dm, t_editor *le, double x,
						double y);
void				draw_menu(t_doom *dm, Uint32 x, Uint32 y, int cur);
void				draw_object_gfx(t_doom *dm, t_gfx gfx, int *yx,
						double size);
void				draw_part_gfx(t_doom *dm, t_gfx gfx, Uint32 *max, Uint32 *xy);
void				draw_pgfx_sc(t_doom *dm, t_gfx gfx, int *yx, double size);
void				draw_scaled_gfx(t_doom *dm, t_gfx gfx, int *yx,
						double size);
void				draw_screen(t_editor *le, t_doom *dm, int x, int y);
int					draw_screen_more(t_editor *le, t_doom *dm, int x, int y);
void				draw_sky(t_doom *dm);
void				draw_sliders(t_doom *dm, t_editor *le, int x, int y);
void				draw_sprite(t_doom *dm, int y, int x);
void				draw_sprite_gfx(t_doom *dm, t_gfx gfx, int *yx,
						double size);
void				editor_key_press(Uint32 key, t_editor *le);
void				editor_key_release(Uint32 key, t_editor *le, t_doom *dm);
void				editor_main(t_doom *dm);
void				error_out(char *msg, t_doom *dm);
void				ext_ray(t_doom *dm);
void				foe_ai(t_doom *dm, t_sprite *spr, int *yx, int i);
void				foe_dir(t_doom* dm, t_sprite* spr, double spra);
void				foe_passive_cycle(t_doom *dm, t_sprite *spr, int i);
void				free_map(t_doom *dm, int f, int y);
void				free_memory(char **arr);
void				free_vram(t_doom *dm);
void				game_loop(t_doom *dm);
void				gravity(t_doom *dm);
void				key_release_menu(int key, t_doom *dm);
void				key_state_editor(t_editor *le, t_doom *dm);
void				key_state_game(t_doom *dm);
void				key_state_menu(t_doom *dm);
void				lab_move(t_doom *dm, int obj, t_vector stair);
void				main_menu(t_doom *dm);
void				menu_keys(int key, t_doom *dm);
void				menu_keys_hold(int key, t_doom *dm);
void				mouse_movex(int dir, t_doom *dm);
void				mouse_movey(int dir, t_doom *dm);
void				move_fb(t_doom *dm);
void				options_menu(t_doom *dm);
void				options_menu_create(t_doom *dm);
void				part_check(t_doom *dm);
void				part_dda_xn(t_doom *dm, double plane);
void				part_dda_xp(t_doom *dm, double plane);
void				part_dda_yn(t_doom *dm, double plane);
void				part_dda_yp(t_doom *dm, double plane);
void				part_dda_zn(t_doom *dm, double plane);
void				part_dda_zp(t_doom *dm, double plane);
void				pickupitem(t_doom *dm);
void				player_shooting(t_doom *dm, int i);
void				plr_status(t_doom *dm, t_sprite *spr, int *yx, int i);
void				pokemon_trainer(t_doom *dm, int y, int x, int i);
void				post_effects(t_doom *dm);
void				recv_pos(t_doom *dm);
void				reloading_gun(t_doom *dm);
void				render(t_doom *dm);
void				render_floor(t_doom *dm);
void				reset_position(t_doom *dm);
void				reset_window(t_doom *dm, Uint8 arg);
void				resize_window(t_doom *dm);
void				set_text(t_doom *dm, char *str, int *xy, double size);
void				set_variables(t_doom *dm);
void				side_check(t_doom *dm);
void				single_loop_x(t_doom *dm);
void				single_loop_y(t_doom *dm);
void				single_loop_z(t_doom *dm);
void				slide_door(t_doom *dm);
void				slope_dda_xzn(t_doom *dm);
void				slope_dda_xzp(t_doom *dm);
void				sprite_set(t_doom *dm, int i);
void				strafe(t_doom *dm, double dirxtemp, double dirytemp);
void				suffrocate(t_doom *dm, t_block blk, t_vector bpos);
void				validate_map(t_doom *dm, int i, int a, t_block blk);
void				wall_stripe(t_doom *dm);
void				wind_default(t_doom *dm);

#endif
