# ifndef FDF_H
# define FDF_H
# include <stdlib.h>

# define height 900
# define width 600

typedef struct s_window
{
	void *ptr;
	void *win;
}	t_window;

typedef struct s_ponto
{
    int altura;
    long int cor;
} t_ponto;

typedef struct s_matriz
{
	int	x;
	int	y;
	t_ponto	**mapa;
}	t_matriz;

int	count_x(char	*str);
int	count_y(int	fd);
t_ponto *mapa_line(char	*line, int x);
void	creat_matriz(t_matriz *ptr, int fd);
void	free_matriz(t_matriz	*ptr);
long int	convert_base(char *s);

#endif
