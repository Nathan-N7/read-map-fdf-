# ifndef FDF_H
# define FDF_H
#include <stdio.h>
#include <math.h>
#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
# include <stdlib.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>

# define HEIGHT 800
# define WIDTH 800
# define SCALE 10
#define PERSPECTIVE_SCALE 0.5

typedef struct s_window
{
    void *ptr;
    void *win;
    int zoom;
    int offset_x;
    int offset_y;           // Fator de zoom
} t_window;


typedef struct s_ponto
{
    int	altura;
    long int	cor;
} t_ponto;

typedef struct s_matriz
{
	int	x;
	int	y;
	t_ponto	**mapa;
}	t_matriz;

typedef struct s_app
{
    t_window *mlx;
    t_matriz *matriz;
} t_app;

int	count_x(char	*str);
int	count_y(int	fd);
t_ponto	*mapa_line(char	*line, int x);
void	creat_matriz(t_matriz *ptr, int fd);
void	free_matriz(t_matriz	*ptr);
long int	convert_base(char *s);
int abs2(int p);
void rotacionar_mapa(t_window *mlx, int tecla);
void mover_mapa(t_window *mlx, int tecla);
void desenhar_mapa(t_window *mlx, t_matriz *matriz);

#endif
