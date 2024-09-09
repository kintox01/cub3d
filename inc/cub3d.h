
#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <time.h>
# include "../minilibx_macos/mlx.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

# define WIN_WIDTH 900
# define WIN_HEIGHT 680
# define MINIMAP_SIZE 200
# define MAP_SCALE 10

# define HUD "./res/hud/finalhud.xpm"
# define WEAPON0 "./res/animation/gun0.xpm"
# define WEAPON1 "./res/animation/gun1.xpm"
# define WEAPON2 "./res/animation/gun2.xpm"
# define WEAPON3 "./res/animation/gun3.xpm"
# define WEAPON4 "./res/animation/gun4.xpm"

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_item
{
	char	type;
	int		px;
	int		py;
}	t_item;

typedef struct s_file
{
	int		f1;
	int		f2;
	int		f3;
	int		f4;
	int		f5;
	int		f6;
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	size_t	map_start;
	size_t	tab_len;
}	t_file;

typedef struct l_sprite
{
	int		texx;
	int		texy;
	int		stripe;
	double	*buffer;
	double	invdet;
	double	transfx;
	double	transfy;
	int		vmovescreen;
	int		spritescreenx;
	int		spriteheight;
	int		drawstarty;
	int		drawendy;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;

}	t_sprite;

typedef struct l_time
{
	clock_t	start;
	int		n_frame;
	int		tmp;
}	t_time;

typedef struct l_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	plx;
	double	ply;
	double	rot;
	double	dex;
	double	dey;
	double	totalrots;
}	t_player;

typedef struct l_dda
{
	double		cam_x;
	int			screenx;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		walldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wallx;
	int			textx;
	int			texty;
	double		step;
	double		textpos;
}	t_dda;

typedef struct l_img
{
	char	*p_img;
	int		width;
	int		height;
	int		bt;
	int		s_line;
	int		endian;
}	t_img;

typedef struct l_map
{
	size_t	map_len;
	char	**map;

	void	*no;
	void	*so;
	void	*we;
	void	*ea;

	int		f;
	int		c;
	t_dlist	*spawn;
	t_list	*item;

	char	dirspawn;

}	t_map;

typedef struct l_weapon
{
	void	*p_img;
	int		width;
	int		height;
}	t_weapon;

typedef struct s_animation
{
	pthread_t	thread;
	pthread_mutex_t	lock;
	int			i;
}	t_animation;


typedef struct l_minimap
{
	int		x;
	int		y;
	int		visible_tiles_x;
	int		visible_tiles_y;
	double		offset_x;
	double		offset_y;
	int		map_x;
	int		map_y;
	char	**map;
	int		player_x;
	int		player_y;
	int		map_height;
	int		map_width;
}	t_minimap;

typedef struct l_data
{
	void		*p_img;
	float		x0;
	float		x1;
	float		y1;
	float		y0;
	void		*mlx;
	void		*mlx_win;
	int			n_taken;
	int			n_sprites;
	void		*hud;
	t_sprite	*sp;
	t_time		*t;
	t_img		**img;
	t_weapon	**weapon;
	t_map		*map;
	t_player	*pl;
	t_dda		*dda;
	t_animation	*anim;
	t_minimap	*minimap;
}	t_data;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		free_exit(t_data *data);
void	free_init_data(t_data *data);
void	trace_line_wall(t_img *img, int color, t_data *data);
int		splitlen(char **tab);
void	update_param(t_data *data, double rot);
void	ft_error(void *arg, int e);
void	set_spawn(t_data *data);
void	check_dist(t_data *ptr);
void	calc_dda(t_data *ptr);
void	check_side(t_data *ptr);
void	draw_verttext(t_data *data, int x, int y, t_img *text);
void	set_plane(t_data *ptr, char flag);
int		init_data(t_data *data);
void	put_spirtes(t_data *data);
void	run_draw(t_data *data);
int		key_handler(int key, t_data *data);
void	init_texture(t_data *ptr, int flag, char *path);
void	ft_free_tab(char **tab);
int		find_max(int num1, int num2);
int		find_mod(int num);
void	raycaster(t_data *data);
void	trace_line(t_img *img, int color, t_data *data);
char	*ft_free_join(char const *s1, char const *s2, int e);
void	put_spawn(t_data *data);
int		key_exit(int key, t_data *data);
void	draw_sprites(t_data *data, double x, double y);
int		parsing(t_data *data, t_map *map, char **argv);
void	ft_error(void *arg, int e);
char	*ft_free_join(char const *s1, char const *s2, int e);
int		ft_atoi_positive(const char *str);

t_dlist	*dlstnew(void *content);
void	dlstadd_back(t_dlist **lst, t_dlist *new);
void	dlst_free(t_dlist **lst);
char	**split1(char const *s, char c);
int		free_tab(char **tab, int ret);

void	set_spawn(t_data *data);
void	pl_init(t_data *data);
void	struct_init(t_file *file, t_map *map);

int		write_error(char *str);
int		isspawn(char c);
int		inmap(char c);
int		ismap(char c);

int		write_error(char *str);
int		are_printable(char *str);
int		are_space(char *str);
int		ft_free(void *a1, void *a2, void *a3, void *a4);
void	ft_tab_len(t_file *file, char **tab);

int		get_file(int fd, char ***tab);
int		map_elem(t_file *file, char **tab);
int		take_map(t_file *file, t_map *map, char **tab);
int		check_map(t_map *map);
int		conv_color(int *color, char *str);

void	*display_hud(void *dat);
void	init_hud(t_data *data);
void	draw_minimap(t_data *data);
void	init_minimap(t_data *data);
void	clear_screen(t_data *data);

#endif // !CUB3D_H
