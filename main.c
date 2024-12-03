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

int	count_y(int fd)
{
	char	*line;
	int		i;

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

long int	convert_base(char *s)
{
	int			i;
	long int	content;

	i = 0;
	content = 0;
	if (s[0] == '0' && s[1] == 'x')
		i = 2;
	while (s[i] != '\0' && s[i] != '\n')
	{
		content *= 16;
		if (s[i] >= '0' && s[i] <= '9')
			content += (s[i] - '0');
		else if (s[i] >= 'A' && s[i] <= 'F')
			content += (s[i] - 'A' + 10);
		else if (s[i] >= 'a' && s[i] <= 'f')
			content += (s[i] - 'a' + 10);
		else
		{
			printf("Erro na conversão: caractere inválido\n");
			return (16777215);
		}
		i++;
	}
	return (content);
}

void	free_matriz(t_matriz	*ptr)
{
	int	i;

	i = -1;
	if (ptr == NULL)
		return ;
	if (ptr->mapa)
	{
		while (++i < ptr->y)
		{
			if (ptr->mapa[i] != NULL)
				free(ptr->mapa[i]);
		}
		free(ptr->mapa);
	}
	free(ptr);
}
/*void	print(t_matriz *ptr)
{
	int    i;
	int    k;

	i = 0;
	k = 0;
	while (i < ptr->y)
	{
		while (k < ptr->x)
		{
			printf("Altura: %d, Cor: 0x%06lX\n", ptr->mapa[i][k].altura, ptr->mapa[i][k].cor);
			k++;
		}
		printf("\n");
		k = 0;
		i++;
	}
}*/

int	main(void)
{
	int			fd;
	char		*line;
	t_matriz	*ptr;

	fd = open("test_maps/julia.fdf", O_RDONLY);
	if (fd < 0)
		return (-1);
	ptr = malloc(sizeof(t_matriz));
	if (ptr == NULL)
		return (-1);
	line = get_next_line(fd);
	ptr->x = count_x(line);
	ptr->y = count_y(fd);
	close(fd);
	fd = open("test_maps/julia.fdf", O_RDONLY);
	if (fd < 0)
	{
		free(ptr);
		return (-1);
	}
	creat_matriz(ptr, fd);
	//print(ptr);
	free_matriz(ptr);
	free(line);
	close(fd);
}	
