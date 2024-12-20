/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:34 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/12/20 14:44:20 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	valid_char_info(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'C' || c == 'F')
		return (1);
	return (0);
}

void	extract_line_info(t_cub *cub)
{
	char	*line;
	int		i;

	line = (char *)cub->cub_info->data;
	i = skip_blank(line);
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		cub->no = ft_strdup(line + i + 2, 0);
		if (!cub->no)
			printf("%sError Malloc\n%s", MAUVE, END);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		cub->so = ft_strdup(line + i + 2, 0);
		if (!cub->so)
			printf("%sError Malloc\n%s", MAUVE, END);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		cub->ea = ft_strdup(line + i + 2, 0);
		if (!cub->ea)
			printf("%sError Malloc\n%s", MAUVE, END);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		cub->we = ft_strdup(line + i + 2, 0);
		if (!cub->we)
			printf("%sError Malloc\n%s", MAUVE, END);
	}
	else if (line[i] == 'F')
	{
		cub->floor[0] = ft_atoi(line + i + 1);
		cub->floor[1] = ft_atoi(line + i + 2);
		cub->floor[2] = ft_atoi(line + i + 3);
	}
	else if (line[i] == 'C')
	{
		cub->ceiling[0] = ft_atoi(line + i + 1);
		cub->ceiling[1] = ft_atoi(line + i + 2);
		cub->ceiling[2] = ft_atoi(line + i + 3);
	}
}

int	valid_char_map(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'C'
		|| c == 'F' || c == 'R' || c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

void	extract_info(t_cub *cub)
{
	t_list	*lst;
	char	*line;
	int		i;

	i = 0;
	lst = cub->cub_info;
	while (lst)
	{
		line = (char *)lst->data;
		i = skip_blank(line);
		if (valid_char_info(line[i]))
		{
			extract_line_info(cub);
			lst = lst->next;
		}
		else if (valid_char_map)
			check_other_info_and_get_map(cub);
		lst = lst->next;
	}
}

void	get_cub_info(t_cub *cub)
{
	t_list	*lst;
	char	*node;
	int		first_read;

	first_read = 1;
	while (1)
	{
		node = get_next_line(cub->fd, cub->gnl_free, 0);
		if (!node && first_read == 1)
			printf("%sError empty\n%s", MAUVE, END);
		first_read = 0;
		if (node == NULL)
			break ;
		lst = ft_lstnew(node, 0);
		if (!lst)
		{
			cub->gnl_free = 1;
			free(node);
			printf("%sError Malloc\n%s", MAUVE, END);
		}
		ft_lstadd_back(&cub->cub_info, lst);
	}
	extract_info(cub);
}

int	parsing(int argc, char *map_file, t_cub *cub)
{
	if (argc != 2)
	{
		printf("%sError\n%s", MAUVE, END);
		printf("%sToo many arguments\n%s", MAUVE, END);
		printf("Usage: ./cub3d [map.cub]\n");
		return (0);
	}
	get_cub_info(cub);
	(void)map_file;
	return (0);
}

	// penser a limite la taille du jeu
	// exemple so long :
	// 	if (game.width > 110 || game.height > 55)
	// 		ft_error(ERROR_SIZE, &game);