#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

int button_press(int keysym, t_window *mlx)
{
	if(keysym == XK_Escape)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		exit(0);
	}
	return (0);
}

int event_close(t_window *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}


void projecao_3d(int *x, int *y, int z, int offset_x, int offset_y) {
    int x3d, y3d;
    
    // Aplicando uma projeção isométrica simples (perspectiva)
    x3d = (*x - *y) * SCALE;
    y3d = (*x + *y - z) * SCALE * PERSPECTIVE_SCALE; // A altura afeta a posição Y com perspectiva

    *x = x3d + offset_x;
    *y = y3d + offset_y;
}

void bresenham(t_window *mlx, int x0, int y0, int x1, int y1, int cor) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx->ptr, mlx->win, x0, y0, cor); // Desenha o ponto
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void desenhar_mapa(t_window *mlx, t_matriz *matriz) {
    int offset_x = (WIDTH - matriz->x * 10) / 2;
    int offset_y = (HEIGHT - matriz->y * 10) / 2;

    for (int y = 0; y < matriz->y; y++) {
        for (int x = 0; x < matriz->x; x++) {
            int x0 = x;
            int y0 = y;
            int z0 = matriz->mapa[y][x].altura;

            projecao_3d(&x0, &y0, z0, offset_x, offset_y);

            // Linha horizontal
            if (x < matriz->x - 1) {
                int x1 = x + 1;
                int y1 = y;
                int z1 = matriz->mapa[y][x + 1].altura;
                projecao_3d(&x1, &y1, z1, offset_x, offset_y);
                bresenham(mlx, x0, y0, x1, y1, matriz->mapa[y][x].cor);
            }

            // Linha vertical
            if (y < matriz->y - 1) {
                int x1 = x;
                int y1 = y + 1;
                int z1 = matriz->mapa[y + 1][x].altura;
                projecao_3d(&x1, &y1, z1, offset_x, offset_y);
                bresenham(mlx, x0, y0, x1, y1, matriz->mapa[y][x].cor);
            }
        }
    }
}

int main() {
    t_window mlx;
    t_matriz matriz;

    mlx.ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "Mapa FDF");

    int fd = open("test_maps/42.fdf", O_RDONLY);
    if (fd < 0)
        return (-1);

    matriz.x = count_x(get_next_line(fd));
    matriz.y = count_y(fd);
    close(fd);

    fd = open("test_maps/42.fdf", O_RDONLY);
    creat_matriz(&matriz, fd);
    close(fd);

    desenhar_mapa(&mlx, &matriz);

    mlx_key_hook(mlx.win, button_press, &mlx);
    mlx_hook(mlx.win, 17, 0, event_close, &mlx);
    mlx_loop(mlx.ptr);

    free_matriz(&matriz);
    return (0);
}