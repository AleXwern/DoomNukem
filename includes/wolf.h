/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:31:21 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/16 16:57:37 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define THREADS 24

//DOOM

# include "/usr/local/include/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

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
	void		*img;
	int			*data;
	int			sizel;
	int			bpp;
	int			endn;
	int			wid;
	int			hgt;
}				t_gfx;

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

typedef struct	s_wolf
{
	void		*mlx;
	void		*win;
	int			tile;
	t_gfx		*gfx;
	int			gfxcount;
	t_gfx		img;
	t_chara		*chara;
	int			height;
	int			width;
	void		(*cycle)(struct s_wolf*);
	char		*syssmg[2];
	int			cur;
	int			sel;
	int			plr;
	int			plrck;
	int			x;
	int			y;
	int			pos;
	int			hold;
	int			flr;
	int			mxflr;
	int			mapset;
	int			***map;
	int			winb;
	int			texbool;
	double		rng;
	int			fcomb;
	int			aggro;
	int			iscombat;
	int			ismenu;
	int			mapx;
	int			xmax;
	int			mapy;
	int			mapz;
	int			stepx;
	int			stepy;
	int			stepz;
	int			hit;
	int			side;
	int			lineh;
	int			start;
	int			end;
	int			texnum;
	int			texx;
	int			texy;
	int			testcolor;
	int			sbox;
	int			cellx;
	int			celly;
	int			cellz;
	int			tx;
	int			ty;
	int			tz;
	double		posx;
	double		posy;
	double		posz;
	double		poszz;
	double		dirx;
	double		diry;
	double		dirz;
	double		planex;
	double		planey;
	double		planez;
	double		camx;
	double		camy;
	double		raydx;
	double		raydy;
	double		raydz;
	double		raydx0;
	double		raydy0;
	double		raydz0;
	double		raydx1;
	double		raydy1;
	double		raydz1;
	double		sidedx;
	double		sidedy;
	double		sidedz;
	double		deltadx;
	double		deltady;
	double		deltadz;
	double		walldist;
	double		rowdist;
	double		flstepx;
	double		flstepy;
	double		flstepz;
	double		floorx;
	double		floory;
	double		floorz;
	double		movsp;
	double		rotsp;
	double		step;
	double		wallx;
	double		texpos;
	int			isclick;
	int			keyleft;
	int			keyright;
	int			keyup;
	int			keydown;
	int			keyplus;
	int			keyminus;
	int			keyw;
	int			keys;
	int			keya;
	int			keyd;
	int			keyone;
	int			keytwo;
	int			keyq;
	int			keye;
	int			keym;
	int			keyi;
	int			accesscard;
	int			crouching;
	int			mouseprevx;
	int			mouseprevy;
}				t_wolf;

t_gfx			init_image(t_wolf *wolf, int x, int y);
t_gfx			gfx_get(t_wolf *wolf, char *file, int x, int y);
t_chara			*generate_party(t_wolf *wlf);
t_chara			generate_foe(t_wolf *wlf);

int				get_x(int pc);
int				get_y(int pc);
int				interact(t_wolf *wlf);
int				key_hold(int key, t_wolf *wlf);
int				key_press(int key, t_wolf *wolf);
int				key_release(int key, t_wolf *wolf);
int				mouse_move(int x, int y, t_wolf *wlf);
int				move(t_wolf *wlf);
int				move_fb(t_wolf *wlf);
void			strafe(t_wolf *wlf, double dirxtemp, double dirytemp);
int				move_lr(t_wolf *wlf);
int				x_press(t_wolf *wolf);

char			*get_syssmgone(t_wolf *wlf, int pc);
char			*get_syssmgtwo(t_wolf *wlf, int pc);

void			anim_shift(t_wolf *wlf, int frame);
void			cam_udy(t_wolf *wlf, double olddiry, double oldplaney);
void			combat_key(int key, t_wolf *wlf);
void			comp_foe(t_wolf *wlf, char *bpath, int i);
void			comp_gfx(t_wolf *wolf, int i);
void			comp_map(t_wolf *wolf, char *av);
void			destroy_gfx(t_wolf *wlf, int i);
void			draw_gfx(t_wolf *wlf, t_gfx gfx, int x, int y);
void			encounter(t_wolf *wlf);
void			error_out(char *msg, t_wolf *wolf);
void			exit_combat(t_wolf *wlf);
void			free_map(t_wolf *wlf, int f, int y);
void			free_memory(char **arr);
void			gen_att_ai(t_wolf *wlf);
void			health_check(t_wolf *wlf, int pc, int thp);
void			lab_move(t_wolf *wlf, int obj);
void			place_pc(t_wolf *wlf, int pc);
void			render(t_wolf *wlf);
void			render_floor(t_wolf *wlf);
void			wall_stripe(t_wolf *wlf);

#endif
