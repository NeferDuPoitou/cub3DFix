/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/07 15:11:21 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_orientation(t_cub *cub)
{
	if (cub->dir == EA)
		cub->rotation_angle = EA * PI / 2;
	else if (cub->dir == SO)
		cub->rotation_angle = PI / 2;
	else if (cub->dir == WE)
		cub->rotation_angle = PI;
	else if (cub->dir == NO)
		cub->rotation_angle = 3 * PI / 2;
}

int	close_game(t_cub *cub, char *error, int status)
{
	printf("%sError\n%s", RED, END);
	printf("%s%s\n%s", MAUVE, error, END);
	if (cub->mlx)
	{
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
	}
	wclear(1);
	exit(status);
}

void	ft_display(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	ft_init_map(cub);
	ft_draw_4_rays(cub);
	ft_draw_walls(cub);
	ft_collision(cub);
}

int	start_game(t_cub *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!cub->mlx)
		return (close_game(cub, "mlx_init failed", 1));
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (close_game(cub, "mlx_new_image failed", 1));
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (close_game(cub, "mlx_image_to_window failed", 1));
	ft_orientation(cub);
	if (ft_init_textures(cub))
		close_game(cub, "ft_init_textures failed", 1);
	mlx_loop_hook(cub->mlx, ft_display, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	return (0);
}
