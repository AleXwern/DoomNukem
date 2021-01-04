/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:31:21 by anystrom          #+#    #+#             */
/*   Updated: 2021/01/04 15:38:12 by vkeinane         ###   ########.fr       */
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
# include "value.h"
# include "../libax/libax.h"

# if _WIN64

/*
** Windows x64 OS spesific includes
** Mainly to get win spesific versions of C functions like open -> _open
** to work because of required flags.
*/

#  include "SDL.h"
#  include "SDL_net.h"
#  include "SDL_mixer.h"
#  include <windows.h>

# elif __APPLE__

/*
** Apple Mac OS specific includes
*/

#  include "../frameworks/SDL2.framework/Headers/SDL.h"
#  include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# endif

typedef float		t_fpoint;

typedef struct		s_key
{
	char			esc;
	char			one;
	char			two;
	char			three;
	char			four;
	char			five;
	char			six;
	char			seven;
	char			eight;
	char			nine;
	char			zero;
	char			q;
	char			w;
	char			e;
	char			r;
	char			t;
	char			y;
	char			u;
	char			i;
	char			o;
	char			p;
	char			a;
	char			s;
	char			d;
	char			f;
	char			g;
	char			h;
	char			j;
	char			k;
	char			l;
	char			z;
	char			x;
	char			c;
	char			v;
	char			b;
	char			n;
	char			m;
	char			space;
	char			left;
	char			right;
	char			down;
	char			up;
	char			plus;
	char			minus;

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
	t_uint32		*data;
}					t_img;

typedef struct		s_gfx
{
	t_uint32		*data;
	int				wid;
	int				hgt;
	int				bpp;
	int				pitch;
	int				x;
	int				y;
}					t_gfx;

/*
** Level editor struct
** Maybe not needed but my own reasoning at the time was to minimize the
** size of the main struct even is a little bit.
*/

typedef struct		s_editor
{
	t_uint8			flr;
	t_uint8			quit;
	t_vector		spawn;
	t_vector		end;
	int				cur;
	t_uint8			blk;
	t_uint8			spr;
	int				options[5];
	double			maxval[5];
	char			minval[5];
	char			*opt[12];
	SDL_Event		ev;
	char			marea;
	char			mslider;
	char			mblock;
	char			mcopy;
	int				ylev;
	int				tab;
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
	t_uint8			b;
	t_uint8			lgt;
	t_uint8			pt;
	t_uint8			pln;
	t_uint8			meta;
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
	int				x;
	int				y;
	int				frame;
	int				respawn;
	int				timer;
	t_vector		face;
	char			move;
	char			dead;
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
	char			dead;
	char			gfx;
}					t_bulk;

typedef struct		s_chunk
{
	t_bulk			plr[4];
	char			id;
}					t_chunk;

typedef struct		s_doom
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Surface		*surf;
	SDL_Texture		*tex;
	t_img			img;
	SDL_Event		event;
	SDL_Thread		**threads;
	t_libax			*ax;
	t_ip			ip;
	t_socket		*sock;
	int				netstat;
	int				person;
	struct s_doom	*data_r;
	struct s_doom	*dm;
	int				id;
	t_fpoint		*wallarr;
	t_fpoint		*winarr;
	int				*maparr;
	t_uint32		*window;
	int				killthread;
	int				tile;
	t_gfx			*gfx;
	t_sprite		spr[SPR];
	t_sprite		prj[SPR];
	t_sprite		obj[OBJ];
	char			flag;
	int				dev;
	int				gfxcount;
	int				height;
	int				width;
	int				winh;
	int				winw;
	int				owinw;
	int				owinh;
	void			(*cycle)(struct s_doom*);
	void			(*keyck)(struct s_doom*);
	t_uint32		iframe;
	int				credits;
	int				creds;
	int				cur;
	int				sel;
	int				adj;
	int				wincol;
	int				rcol;
	int				lgt;
	int				x;
	int				y;
	int				flr;
	t_block			***area;
	t_block			blk;
	t_uint32		blkcol;
	int				blktx;
	int				selectedblk;
	int				ckflr;
	double			tmpx;
	double			tmpy;
	int				sldry;
	int				sldrx;
	t_uint32		sldrcol;
	int				texbool;
	int				rng;
	int				ismenu;
	int				sy;
	int				sx;
	t_uint32		black;
	int				xmax;
	int				stepx;
	int				stepy;
	int				stepz;
	int				hit;
	int				invincible;
	int				side;
	double			lineh;
	int				texnum;
	int				texx;
	int				texy;
	t_uint32		col;
	int				sbox;
	int				sboy;
	int				cellx;
	int				celly;
	int				cellz;
	int				tx;
	int				ty;
	int				tz;
	int				airbrn;
	t_vector		spw;
	t_vector		pos;
	double			truez;
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
	t_vector		min;
	t_vector		max;
	double			mina;
	double			maxa;
	double			walldist;
	double			movsp;
	double			rotsp;
	double			wallx;
	t_key			key;
	double			plrhight;
	int				crouching;
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
	t_uint32		fps;
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
	int				gamestarted;
	int				gamewon;
	int				keycard;
	int				chestopened;
	int				drawgunandkeycard;
	int				jetpack;
	int				money;
	int				datareadtype;
	char			*moneytemp;
	char			*moneytext;
	int				victoryplayed;

	char			slidedoor;
	t_block			*slideblock;
	int				doorani;
	int				doorfrm;

	int				volume;
	Mix_Music		*music;
	Mix_Chunk		*reload;
	Mix_Chunk		*gunshot;
	Mix_Chunk		*jetpacksound;
	Mix_Chunk		*doorsound;
	Mix_Chunk		*doorknob;
	Mix_Chunk		*teleport;
	Mix_Chunk		*ishit;
	Mix_Chunk		*death;
	Mix_Chunk		*mondeath;
	Mix_Chunk		*windowbrk;
	Mix_Chunk		*doorsliding;
	Mix_Chunk		*victory;
	Mix_Chunk		*jump;
}					t_doom;

t_uint32			avg_color(t_uint32 rcol, t_uint32 col);
t_uint32			color_shift(t_uint32 color, double shift, t_doom *dm,
						t_uint32 ret);
t_uint32			rl_color(int lgt, t_uint32 col);

double				dot_prd(t_vector v, t_vector u);
double				get_coll_down(t_block blk, t_vector pos);
double				spra_check(t_doom *dm, double spra);
double				tri_pythagor(t_vector f, t_vector s);

int					check_sprite_dist(t_doom *dm, double mov, int i);
int					connect_server(t_doom *dm);
int					foe_ismoving(t_sprite *spr);
int					fps_capper(void *ptr);
int					fps_counter(void *ptr);
int					ver_move(t_block blk, t_doom *dm);
int					gravity_slope(t_doom *dm);
int					get_blockstack(t_doom *dm, t_block blk, char dir);
int					get_objsmallsprite(int gfx);
int					interact(t_doom *dm);
int					key_hold(int key, t_doom *dm);
int					key_release(int key, t_doom *dm);
int					light_map(t_vector map, int side, t_block ***area);
int					get_blocklight(t_doom *dm, t_vector pos);
int					mouse_move(int x, int y, t_doom *dm);
int					move(t_doom *dm);
int					move_lr(t_doom *dm);
int					renthread(void *ptr);
int					save_file(t_doom *dm, int fd, char *file, int i);
int					send_pos(t_doom *dm);
int					set_objsmallsprite(int gfx);
int					slope_coll(t_block blk, t_doom *dm, char dir);
int					tex_check(t_doom *dm);
int					datatype_check(t_doom *dm, char **tmp);

t_gfx				memcpy_gfx(t_gfx chunck, int *pos, int *size);
t_gfx				read_bmp(char *file, int fd, int bread);
t_img				init_image(t_doom *dm);
t_vector			cross_prd(t_vector v, t_vector u);

void				alloc_vram(t_doom *dm);
void				fill_floor(t_doom *dm, int y);
void				fill_area(t_doom *dm, int y, int x);
void				cam_udy(t_doom *dm);
void				check_area(t_editor *le, t_doom *dm, SDL_Event ev);
int					check_hor_coll(t_block blk, t_doom *dm, char dir);
int					check_sprite_dist(t_doom *dm, double mov, int i);
int					check_yx(char dir, t_block tblk, t_doom *dm);
void				comp_gfx(t_doom *dm);
void				comp_map(t_doom *dm);
void				comp_sprite(t_doom *dm, int i, int fd);
void				comp_texpack(t_doom *dm);
void				crouch(t_doom *dm);
void				curt_down(t_doom *dm);
void				curt_up(t_doom *dm);
void				dda_prep(t_doom *dm);
void				dda_sys(t_doom *dm);
void				destroy_gfx(t_doom *dm, int i);
void				destroy_texpack(t_doom *dm);
void				dev_status(t_doom *dm, char *av);
void				doom_default(t_doom *dm);
void				draw_ammo(t_doom *dm);
void				draw_bg(t_doom *dm, t_gfx gfx);
void				draw_blk_select(t_doom *dm, t_editor *le, int x, int y);
void				draw_editor_cursor(t_doom *dm, t_editor *le, int x, int y);
void				draw_gfx(t_doom *dm, t_gfx gfx, int x, int y);
void				draw_gun(t_doom *dm);
void				draw_hp(t_doom *dm);
void				draw_hud(t_doom *dm);
void				draw_hud2(t_doom *dm);
void				draw_layerspr(t_doom *dm, t_editor *le, int x, int y);
void				draw_level_screen(t_doom *dm, t_editor *le, double x,
					double y);
void				draw_menu(t_doom *dm, int x, int y, int cur);
void				draw_object(t_doom *dm, int i, int y, int x);
void				draw_objects(t_doom *dm, int y, int x, int i);
void				draw_object_gfx(t_doom *dm, t_gfx gfx, int *yx,
					double size);
void				draw_part_gfx(t_doom *dm, t_gfx gfx, int *max,
					int *xy);
void				draw_pgfx_sc(t_doom *dm, t_gfx gfx, int *yx, double size);
void				draw_projectiles(t_doom *dm, int y, int x, int i);
void				draw_scaled_gfx(t_doom *dm, t_gfx gfx, int *yx,
					double size);
void				draw_screen(t_editor *le, t_doom *dm, int x, int y);
int					draw_screen_more(t_editor *le, t_doom *dm, int x, int y);
void				draw_sky(t_doom *dm);
void				draw_sliders(t_doom *dm, t_editor *le, int x, int y);
void				draw_sprite(t_doom *dm, int y, int x, int i);
void				draw_sprite_gfx(t_doom *dm, t_gfx gfx, int *yx,
					double size);
void				draw_sprselect(t_doom *dm, t_editor *le, int x, int i);
void				editor_defaults(t_editor *le, t_doom *dm);
void				editor_key_press(t_uint32 key, t_editor *le);
void				editor_key_release(t_uint32 key, t_editor *le, t_doom *dm);
void				editor_main(t_doom *dm);
void				error_out(char *msg, t_doom *dm);
void				ext_ray(t_doom *dm);
void				foe_ai(t_doom *dm, t_sprite *spr, int *yx, int i);
void				foe_dir(t_doom *dm, t_sprite *spr, double spra);
void				foe_passive_cycle(t_doom *dm, t_sprite *spr, int i);
void				foe_shooting(t_doom *dm, t_sprite *spr, t_sprite *prj);
void				free_map(t_doom *dm, int f, int y);
void				free_memory(char **arr);
void				free_vram(t_doom *dm);
void				game_loop(t_doom *dm);
void				gamestart(t_doom *dm);
void				get_doortype(t_doom *dm, t_vector pos, t_vector door,
					t_block blk);
void				get_sprite(t_doom *dm, t_editor *le);
void				grab_sprite(t_doom *dm, t_editor *le, int spr, int cury);
void				gravity(t_doom *dm);
void				intersect(t_vector *plane, t_vector *ray, t_vector *p);
void				jump(t_doom *dm);
void				key_release_menu(int key, t_doom *dm);
void				key_state_editor(t_editor *le, t_doom *dm);
void				key_state_game(t_doom *dm);
void				key_state_menu(t_doom *dm);
void				lab_move(t_doom *dm, int obj, t_vector stair);
void				main_menu(t_doom *dm);
void				menu_keys(int key, t_doom *dm);
void				menu_keys_hold(int key, t_doom *dm);
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
void				post_effects(t_doom *dm);
void				rc_init(t_doom *dm);
void				recv_pos(t_doom *dm);
void				reloading_gun(t_doom *dm);
void				render(t_doom *dm);
void				render_floor(t_doom *dm);
void				reset_crouching(t_doom *dm);
void				reset_position(t_doom *dm);
void				resize_window(t_doom *dm);
void				renthread2(t_doom *dm);
void				set_ftext(t_doom *dm, char *str, int *xy, double size);
void				set_sprite_tomap(t_editor *le, t_doom *dm, int x, int y);
void				set_text(t_doom *dm, char *str, int *xy, double size);
void				set_variables(t_doom *dm);
void				side_check(t_doom *dm);
void				single_loop_neg(t_doom *dm);
void				single_loop_x(t_doom *dm);
void				single_loop_x_more(t_doom *dm);
void				single_loop_y(t_doom *dm);
void				single_loop_y_more(t_doom *dm);
void				single_loop_z(t_doom *dm);
void				single_loop_z_more(t_doom *dm);
void				slide_door(t_doom *dm);
void				slope_dda_xyb(t_doom *dm, int side);
void				slope_dda_xybr(t_doom *dm, int side);
void				slope_dda_xyt(t_doom *dm, int side);
void				slope_dda_xytr(t_doom *dm, int side);
void				slope_dda_xzb(t_doom *dm, int side);
void				slope_dda_xzbr(t_doom *dm, int side);
void				slope_dda_xzt(t_doom *dm, int side);
void				slope_dda_xztr(t_doom *dm, int side);
void				slope_dda_yzb(t_doom *dm, int side);
void				slope_dda_yzbr(t_doom *dm, int side);
void				slope_dda_yzt(t_doom *dm, int side);
void				slope_dda_yztr(t_doom *dm, int side);
void				strafe(t_doom *dm);
void				suffocate(t_doom *dm, t_block blk, t_vector bpos);
void				tab_change(t_editor *le);
int					templen(char **temp);
void				update_sprite(t_doom *dm, t_editor *le);
void				validate_map(t_doom *dm, int i, int a, t_block blk);
void				wall_stripe(t_doom *dm);
void				wind_default(t_doom *dm);
void				wingame(t_doom *dm);
void				xy_wall_ppos(t_doom *dm, t_block blk, int bbool);
void				comp_block(t_doom *dm, char **temp, int x, int y);
int					is_block_info_present(char **tmp);
int					save_init(char **path, char **bpath, char **file);
void				fill_block(t_doom *dm, int x, int y);
void				force_validate_block(t_doom *dm, int x, int y);
void				sprite_validation(t_sprite *spr, int type);
void				read_objectinfo(t_doom *dm, int i, int fd, int *objdone);
void				read_spriteinfo(t_doom *dm, int i, int fd, int *sprdone);
t_sprite			fill_spriteinfo(void);
t_sprite			fill_objectinfo(void);
t_sprite			set_sprite(char **arr, int len);

#endif
