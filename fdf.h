# ifndef FDF_H
# define FDF_H

typedef struct s_matriz
{
	int	x;
	int	y;
	int	**mapa;
}	t_matriz;

int	count_x(char	*str);
int	count_y(int	fd);
int	*mapa_line(char	*line, int x);
void	creat_matriz(t_matriz *ptr, int fd);
void	free_matriz(t_matriz	*ptr);

#endif