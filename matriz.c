#include "fdf.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int	count_x(char	*str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			count++;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			i++;
	}
	return (count);
}

int	count_y(int	fd)
{
	char	*line;
	int	i;
	
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{	
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i + 1);
}

void map_error(t_matriz *ptr, int i, char *line)
{
	int	j;

	j = 0;
	free(line);
	while (j < i)
		free(ptr->mapa[j++]);
	free(ptr->mapa);
	return ;
}

t_ponto	*mapa_line(char	*line, int x)
{
	char	**num;
	char    **color_hex;
	t_ponto	*linem;
	int	i;
	
	i = 0;
	num = ft_split(line, ' ');
	if (num == NULL)
	    return (NULL);
	linem = malloc(sizeof(t_ponto) * x);
	if (linem == NULL)
	{
		free (num);
	    return (NULL);
	}
	while  (num[i] != NULL && i < x)
	{
		linem[i].altura = ft_atoi(num[i]);
		color_hex = ft_split(num[i], ',');
		if (color_hex != NULL && color_hex[1] != NULL)
			linem[i].cor = convert_base(color_hex[1]);
		else
		    linem[i].cor = convert_base("0xFFFFFF");
		free(num[i]);
        free(color_hex[0]);
		free(color_hex[1]);
		i++;
	}
	free (color_hex);
	free (num[i]);
	free(num);
	return (linem);
}

void	creat_matriz(t_matriz *ptr, int fd)
{
	char	*line;
	int	i;
	
	ptr->mapa = (t_ponto **)malloc(sizeof(t_ponto *) * ptr->y);

	if (ptr->mapa == NULL)
		return ;
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		if (i < ptr->y)
		{
			ptr->mapa[i] = mapa_line(line, ptr->x);
			if (ptr->mapa[i] == NULL)
				map_error(ptr, i, line);
		}
		free (line);
		line = get_next_line(fd);
		i++;
	}
}