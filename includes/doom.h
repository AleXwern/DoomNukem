/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:31:21 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/13 14:43:18 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

//DOOM

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

//# include <SDL.h>
//# include <SDL_image.h>
//# include <SDL_mixer.h>

#if _WIN64
/*
** Windows x64 OS spesific includes
** Mainly to get win spesific versions of C functions like open -> _sopen_s
** to work because of required flags.
*/
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include <windows.h>
# include <share.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <io.h>
# include <stdio.h>
# include <string.h>

# define main(X, Y)			wmain(X, Y)
//# define open(W, X, Y)		_sopen_s(W, X, Y, _SH_DENYWR, _S_IREAD);
#elif __APPLE__
/*
** Apple Mac OS specific includes
*/
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
#endif

typedef struct	s_key
{
	Sint8	esc;
	Sint8	one;
	Sint8	two;
	Sint8	three;
	Sint8	four;
	Sint8	five;
	Sint8	six;
	Sint8	seven;
	Sint8	eight;
	Sint8	nine;
	Sint8	zero;
	Sint8	q;
	Sint8	w;
	Sint8	e;
	Sint8	r;
	Sint8	t;
	Sint8	y;
	Sint8	u;
	Sint8	i;
	Sint8	o;
	Sint8	p;
	Sint8	a;
	Sint8	s;
	Sint8	d;
	Sint8	f;
	Sint8	g;
	Sint8	h;
	Sint8	j;
	Sint8	k;
	Sint8	l;
	Sint8	z;
	Sint8	x;
	Sint8	c;
	Sint8	v;
	Sint8	b;
	Sint8	n;
	Sint8	m;
	Sint8	left;
	Sint8	right;
	Sint8	down;
	Sint8	up;
	Sint8	plus;
	Sint8	minus;

}				t_key;

/*typedef struct	s_block
{
	uint	block	: 12,
			light	: 12,
			meta	: 4,
			l		: 1,
			r		: 1,
			f		: 1,
			b		: 1;
}				t_block;*/

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct	s_ivector
{
	int		x;
	int		y;
	int		z;
}				t_ivector;

/*
** Party member info
** name		= party member name
** maxhp	= max HP
** hp		= current hp
** defend	= 1 if defend option was chosen
** row		= front or back row
** DEFEND and BACK ROW reduce damage by half (stackable)
** BACK ROW reduce damage dealt
*/

typedef struct	s_chara
{
	char		*name;
	int			maxhp;
	int			hp;
	int			row;
	int			action;
	int			defend;
	int			target;
	int			gfxid;
}				t_chara;

/*
** GFX library
** 0 = Skybox
** 1 = Floor
** 2 = Wall
** 3 = Stairs up
** 4 = Stairs down
** 5 = Door
** 6 = Secret warp
*/

typedef struct	s_gfx
{
	SDL_Surface	*tex;
	SDL_Texture	*img;
	Uint32		*data;
	int			wid;
	int			hgt;
}				t_gfx;

typedef struct	s_editor
{
	Uint8		flr;
	Uint8		quit;
	Uint32		**level;
	t_vector	spawn;
	t_vector	end;
	Sint8		cur;
	Uint8		blk;
	Sint8		options[5];
	double		maxval[5];
	Sint8		minval[5];
	SDL_Event	ev;
	Sint8		marea;
	Sint8		mslider;
	Sint8		mblock;
}				t_editor;

typedef struct	s_block
{
	int			t;
	int			sid;
	int			meta;
	t_vector	p[3];
}				t_block;

/*
** mlx	= MLX pointer
** win	= WIN pointer
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

typedef struct	s_doom
{
	SDL_Window	*win;
	SDL_Renderer *rend;
	SDL_Surface	*surf;
	SDL_Texture *tex;
	t_gfx		img;
	SDL_RWops	*rwops;
	SDL_Event	event;
	SDL_GameController *gpad;
	SDL_Thread	**threads;
	SDL_mutex	*joblist;
	SDL_mutex	*setdone;
	SDL_mutex	*lock;
	SDL_cond	*cond;
	struct s_doom		*data_r;
	struct s_doom		*wlf;
	int			id;
	int			*claimline;
	int			*done;
	double		*wallarr;
	int			*maparr;
	int			killthread;
	int			tile;
	t_gfx		*gfx;
	int			gfxcount;
	t_chara		*chara;
	int			height;
	int			width;
	int			winh;
	int			winw;
	int			owinw;
	int			owinh;
	void		(*cycle)(struct s_doom*);
	void		(*keyck)(struct s_doom*);
	char		*syssmg[2];
	int			cur;
	int			sel;
	int			health;
	int			plr;
	int			plrck;
	int			x;
	int			y;
	int			hold;
	int			flr;
	int			mxflr;
	int			mapset;
	int			***area;
	int			winb;
	int			texbool;
	double		rng;
	int			fcomb;
	int			aggro;
	int			iscombat;
	int			ismenu;
	int			xmax;
	int			stepx;
	int			stepy;
	int			stepz;
	int			hit;
	int			hithalf;
	t_vector	hitpos;
	int			side;
	double		lineh;
	int			start;
	int			end;
	int			texnum;
	int			texx;
	int			texy;
	Uint32		col;
	int			sbox;
	int			sboy;
	int			cellx;
	int			celly;
	int			cellz;
	int			tx;
	int			ty;
	int			tz;
	int			rotation;
	double		poszz;
	int			airbrn;
	t_vector	spawn;
	t_vector	pos;
	t_vector	gravity;
	t_vector	fallsp;
	t_vector	dir;
	t_vector	plane;
	t_vector	map;
	t_vector	cam;
	t_vector	rayd;
	t_vector	rmap1;
	t_vector	rmap2;
	t_vector	rtex;
	t_vector	rayd0;
	t_vector	rayd1;
	t_vector	sided;
	t_vector	deltad;
	t_vector	flstep;
	t_vector	floor;
	double		walldist;
	double		rowdist;
	double		movsp;
	double		rotsp;
	double		step;
	double		wallx;
	double		texpos;
	int			isclick;
	t_key		key;
	int			keycard;
	int			crouching;
	int			mouseprevx;
	int			mouseprevy;
	int			*options[25];
	double		maxvalue[25];
	int			isoptions;
	int			isfpscap;
	int			limit;
	int			isoutline;
	int			isgravity;
	int			shift;
	SDL_Thread	*fpsthread;
	Uint32		fps;
	int			trx;
	int			fpscap;
	int			prefps;
	int			buffer;
	double		camshift;
	int			mousemovement;

	SDL_Surface	*gunSurface;
	SDL_Texture	*gunTexture;
	SDL_Rect	gunRect[6][3];
	SDL_Rect	screenGunRect;
	int			shooting;
	int			reloading;
	int			ani;
	int			frm;
	int			magazine;

	SDL_Surface	*CHSurface;
	SDL_Texture	*CHTexture;
	SDL_Rect	CHRect;
	SDL_Rect	screenCHRect;

	SDL_Surface	*invSurface;
	SDL_Texture	*invTexture;
	SDL_Rect	invRect;
	SDL_Rect	screeninvRect;

	SDL_Surface	*keycardSurface;
	SDL_Texture	*keycardTexture;
	SDL_Rect	keycardRect;
	SDL_Rect	screenkeycardRect;

	SDL_Surface	*nbrsSurface;
	SDL_Texture	*nbrsTexture;
	SDL_Rect	nbrsRect[10];
	SDL_Rect	screennbrsRect;
	SDL_Rect	screennbrsTenRect;

	SDL_Surface	*spriteSurface;
	SDL_Texture	*spriteTexture;
	SDL_Rect	spriteRect[4][4];
	SDL_Rect	screenRect;
	int			anim;
	int			frame;

	double		depthbuffer[1080];
	double		disttosprite;
	t_vector	spriteLoc;
	t_vector	spriteRelLoc;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			spriteWidth;
	int			drawStartX;
	int			drawStartY;
	int			drawEndX;
	int			drawEndY;
	int			textureX;
	int			textureY;
	Uint32		spriteColor;

	/*
	**	Variables for playing some sounds and music!
	*/
	Mix_Music	*osrsMusic;
	Mix_Chunk	*reload;
	Mix_Chunk	*gunshot;
	Mix_Chunk	*jetpack;
	Mix_Chunk	*doorsound;
	Mix_Chunk	*doorknob;
	Mix_Chunk	*teleport;
}				t_doom;

t_gfx			init_image(t_doom *wolf);
t_gfx			gfx_get(t_doom *wolf, char *file, int x, int y);
t_chara			*generate_party(t_doom *wlf);
t_chara			generate_foe(t_doom *wlf);
t_vector		cross_prd(t_vector v, t_vector u);
t_vector		oper_vect(t_vector v, t_vector u, char o);

void			load_animsprite(t_doom *wlf);
void			draw_sprite(t_doom *wlf);
void			load_gun(t_doom *wlf);
void			draw_gun(t_doom *wlf);
void			reloading_gun(t_doom *wlf);
void			draw_crosshair(t_doom *wlf);
void			load_numbers(t_doom *wlf);
void			draw_ammo(t_doom *wlf);
void			load_inventory(t_doom *wlf);
void			draw_inventory(t_doom *wlf);
void			load_keycard(t_doom *wlf);
void			draw_keycard(t_doom *wlf);

Uint32			color_shift(Uint32 color, double shift, t_doom *wlf, Uint32 ret);

int				tex_check(t_doom *wlf);
int				fps_capper(void* ptr);
int				fps_counter(void* ptr);
int				get_x(int pc);
int				get_y(int pc);
int				interact(t_doom *wlf);
int				key_hold(int key, t_doom *wlf);
int				key_press(int key, t_doom *wolf);
int				key_release(int key, t_doom *wolf);
int				load_level(t_editor *le, t_doom *dm);
int				mouse_move(int x, int y, t_doom *wlf);
void			mouse_movex(int dir, t_doom *wlf);
void			mouse_movey(int dir, t_doom *wlf);
int				move(t_doom *wlf);
int				move_fb(t_doom *wlf);
int				move_lr(t_doom *wlf);
int				renthread(void *ptr);
int				save_file(t_doom* dm, int fd, char* file, int i);
int				x_press(t_doom *wolf);

char			*get_syssmgone(t_doom *wlf, int pc);
char			*get_syssmgtwo(t_doom *wlf, int pc);

void			anim_shift(t_doom *wlf, int frame);
void			cam_udy(t_doom *wlf);
void			check_area(t_editor* le, SDL_Event ev);
void			combat_key(int key, t_doom *wlf);
void			comp_foe(t_doom *wlf, char *bpath, int i);
void			comp_gfx(t_doom *wolf, int i);
void			comp_map(t_doom *wolf);//, char *av);
void			destroy_gfx(t_doom *wlf, int i);
void			doom_default(t_doom *wlf);
void			draw_bg(t_doom *wlf, t_gfx gfx);
void			draw_blk_select(t_doom* dm, t_editor* le, int x, int y);
void			draw_editor_cursor(t_doom *dm, t_editor *le, int x, int y);
void			draw_gfx(t_doom *wlf, t_gfx gfx, int x, int y);
void			draw_level_screen(t_doom *wlf, t_editor *le, double x, double y);
void			draw_menu(t_doom *wlf, int x, int y, int cur);
void			draw_scaled_gfx(t_doom *wlf, t_gfx gfx, int x, int y);
void			draw_screen(t_editor* le, t_doom* dm, int x, int y);
void			draw_sliders(t_doom *dm, t_editor *le, int x, int y);
void			draw_sky(t_doom *wlf);
void			editor_key_press(Uint32 key, t_editor *le);
void			editor_key_release(Uint32 key, t_editor *le, t_doom* dm);
void			editor_main(t_doom *wlf);
void			encounter(t_doom *wlf);
void			error_out(char *msg, t_doom *wolf);
void			exit_combat(t_doom *wlf);
void			free_map(t_doom *wlf, int f, int y);
void			free_memory(char **arr);
void			game_loop(t_doom *wlf);
void			gen_att_ai(t_doom *wlf);
void			gravity(t_doom *wlf);
void			health_check(t_doom *wlf, int pc, int thp);
void			key_release_menu(int key, t_doom *wlf);
void			key_state_editor(t_editor *le, t_doom *dm);
void			key_state_game(t_doom *wlf);
void			key_state_menu(t_doom* wlf);
void			lab_move(t_doom *wlf, int obj, t_vector stair);
void			main_menu(t_doom *wlf);
void			options_menu(t_doom *wlf);
void			place_pc(t_doom *wlf, int pc);
void			post_effects(t_doom *wlf);
void			render(t_doom *wlf);
void			render_floor(t_doom *wlf);
void			reset_position(t_doom *wlf);
void			reset_window(t_doom *wlf, Uint8 arg);
void			resize_window(t_doom *wlf);
void			strafe(t_doom *wlf, double dirxtemp, double dirytemp);
void			wall_stripe(t_doom *wlf);
void			wind_default(t_doom *wlf);

double			dot_prd(t_vector v, t_vector u);

#endif
