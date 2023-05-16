/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:29:45 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 00:33:31 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <string.h>
int	ft_lstsize(t_line *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

int	ft_lsttoarray(t_line *map, t_cub3D *cub)
{
	t_line	*list;
	int		i;
	size_t	len;

	i = 0;
	list = map;
	len = ft_lstsize(list) + 1;
	if (len == 1)
	{
		printf("Error : empty file.cub\n");
		return (1);
	}
	cub->map_arr = (char **)malloc(sizeof(char *) * len);
	if (!cub->map_arr)
		return (0);
	while (list)
	{
		cub->map_arr[i++] = list->line;
		list = list->next;
	}
	cub->map_arr[i] = NULL;
	return (0);
}

char	*rightpad(char *str, int n)
{
	char	*ptr;
	int		i;

	ptr = malloc(n + 1);
	ft_strcpy(ptr, str);
	i = ft_strlen(str) - 1;
	while (i < n)
		ptr[i++] = ' ';
	ptr[n] = '\n';
	ptr[n - 1] = '\0';
	return (ptr);
}

void	leftpad(char *str)
{
	while (*str == ' ')
	{
		*str = ' ';
		str++;
	}
}

void	fill_map(t_cub3D *cub, t_line *head)
{
	while (head)
	{
		head->line = rightpad(head->line, cub->max_lenght);
		head->line = ft_strjoin(head->line, "\n");
		head = head->next;
	}
}

int	ft_checkLine(char *line)
{
	int	i;

	i = 0;
	if (line[i] != '1' && line[i] != '0')
		return (1);
	return (0);
}

void	fill_map_back(t_cub3D *cub, t_line *head)
{
	cub->max_lenght = ft_strlen(head->line);
	while (head)
	{
		if (ft_checkLine(head->line))
			leftpad(head->line);
		head = head->next;
	}
}

int	ft_checkForSpaces(t_cub3D *cub)
{
	int	i;
	int	j;

	i = cub->first_line;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if(cub->map_arr[i][j] == '0')
			{
				if (cub->map_arr[i][j - 1] == ' ' || cub->map_arr[i][j + 1] == ' ' || cub->map_arr[i - 1][j] == ' ' )
					return (1);
				if (!cub->map_arr[i + 1])
					return (0);
				if (cub->map_arr[i + 1][j] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_checkWall(t_cub3D *cub)
{
	int	i;
	int	j;

	j = 0;
	i = cub->first_line ;
	while (cub->map_arr[cub->first_line][j])
	{
		if (cub->map_arr[cub->first_line][j] == '0')
			return (1);
		j++;
	}
	i = cub->first_line;
	while (cub->map_arr[i])
		i++;
	i--;
	j = 0;
	while (cub->map_arr[i][j])
	{
		if (cub->map_arr[i][j] == '0')
			return (1);
		j++;
	}
	return (0);
}

int ft_countPathTexture(t_cub3D *cub)
{
	int	i;
	int	j;
	int	count = 0;

	i = 0;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j] != '\n')
		{
			if (cub->map_arr[i][j] == ' ')
				j++;
			else
			{
				if ((cub->map_arr[i][j] == 'N' && cub->map_arr[i][j + 1] == 'O') || (cub->map_arr[i][j] == 'S' && cub->map_arr[i][j + 1] == 'O' )|| 
					(cub->map_arr[i][j] == 'W' && cub->map_arr[i][j + 1] == 'E') || (cub->map_arr[i][j] == 'E' && cub->map_arr[i][j + 1] == 'A')
					|| cub->map_arr[i][j] == 'F' || cub->map_arr[i][j] == 'C')
					count++;
				j++;
			}
		}
		i++;
	}
	if (count != 6)
		return (1);
	return (0);
}

int	ft_sortPathTexture(t_cub3D *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j] != '\n')
		{
			if (cub->map_arr[i][j] == ' ')
				j++;
			else
			{
				if (cub->map_arr[i][j] == 'N' && cub->map_arr[i][j + 1] == 'O')
					cub->north_texture = ft_strdup(ft_strtrim( &cub->map_arr[i], "\nNO "));
				else if (cub->map_arr[i][j] == 'S' && cub->map_arr[i][j + 1] == 'O')
					cub->south_texture = ft_strdup(ft_strtrim( &cub->map_arr[i], "\nSO "));
				else if (cub->map_arr[i][j] == 'W' && cub->map_arr[i][j + 1] == 'E')
					cub->west_texture = ft_strdup(ft_strtrim( &cub->map_arr[i], "\nWE "));
				else if (cub->map_arr[i][j] == 'E' && cub->map_arr[i][j + 1] == 'A')
					cub->east_texture = ft_strdup(ft_strtrim( &cub->map_arr[i], "\nEA "));
				else if (cub->map_arr[i][j] == 'F')
					cub->floor_color = ft_strdup(ft_strtrim( &cub->map_arr[i], "\nF "));
				else if (cub->map_arr[i][j] == 'C')
					cub->ceiling_color = ft_strdup(ft_strtrim( &cub->map_arr[i], "\nC "));
				else if (cub->map_arr[i][j] == '1' || cub->map_arr[i][j] == '0' || cub->map_arr[i][j] == ' ')
					break ;
				else
					return (1);
				break;
			}
		}
		i++;
	}
	return (0);
}

int init_width_height(t_cub3D *cub)
{
    int i = cub->first_line;
    int a = 0;
    while (cub->map_arr[i] && cub->map_arr[i][0] != '\n' && cub->map_arr[i][0] != '\0')
    {
	    a++;
        i++;
    }
    cub->map_height = a;
	if (a == 0)
	{
		printf("Error : empty map\n");
		return (1);
	}
    i = cub->first_line;
    int j = 0;
    while (cub->map_arr[i])
    {
        j = 0;
        while (cub->map_arr[i][j])
            j++;
        if (j > cub->map_width)
            cub->map_width = j;
        i++;
    }
	return (0);
}

int ft_checkIfClosed(t_cub3D *cub, t_line *head)
{ 
    int i = 0;
    int j = 0;

    while (head)
    {
		j = 0;
		while (head->line[j] && head->line[j] == ' ')
			j++;
        if (head->line[j] == '0' || head->line[j] == '1')
        {
            cub->first_line = i;
            break;
        }
        head = head->next;
        i++;
        cub->first_line = i;
    }
	if(init_width_height(cub))
		return (1);	
    i = cub->first_line;
    while (cub->map_arr[i])
    {
        j = 0;
        if (ft_checkWall(cub))
            return 1;
        if(cub->map_arr[i][j] == '0')
            return 1;
        while (cub->map_arr[i][j])
            j++;
		if (j >= 2)
		{
			if (cub->map_arr[i][j - 2] == '0')
			{
				printf("Error: map is not closed.\n");
				return 1;
			}
		}
        i++;
    }
    return 0;
}

void printMap(t_cub3D *cub)
{
	int i = 0;
	int j = 0;
	while (cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			printf("%c", cub->map_arr[i][j]);
			j++;
		}
		i++;
	}
}

int ft_checkForMultipleMap(t_cub3D *cub)
{
	int i = 0;
	int j = 0;
	int a = 0;
	int map_height = 0;

	map_height = cub->map_height;
	i = cub->first_line;
	while ( cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (cub->map_arr[i][j] == '1' || cub->map_arr[i][j] == '0')
			{
				a++;
				break;
			}
			j++;
		}
		i++;
	}
	if (map_height != a)
	{
		printf("Error: multiple maps.\n");
		return 1;
	}
	return 0;
}

int ft_check_position(t_cub3D *cub)
{
	int i = 0;
	int j = 0;

	i = cub->first_line;
	while ( cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (cub->map_arr[i][j] == 'N' || cub->map_arr[i][j] == 'S' || cub->map_arr[i][j] == 'E' || cub->map_arr[i][j] == 'W')
			{
				if(i == cub->first_line || i == cub->map_height + cub->first_line - 1 || j == 0 || j == cub->map_width)
				{
					printf("Error: player is not in the middle of the map.\n");
					return 1;
				}
				printf("i %d ,j %d ,height %d, width %d\n", i, j, cub->map_height , cub->map_width);
				if ((cub->map_arr[i - 1][j] != '1' && cub->map_arr[i - 1][j] != '0' )|| (cub->map_arr[i + 1][j] != '1' && cub->map_arr[i + 1][j] != '0' ))
					return 1;
				if ((cub->map_arr[i][j - 1] != '1' && cub->map_arr[i][j - 1] != '0' )|| (cub->map_arr[i][j + 1] != '1' && cub->map_arr[i][j + 1] != '0' ))
					return 1;

			}
			j++;
		}
		i++;
	}
	return 0;

}

int ft_checkForPlayer(t_cub3D	*cub)
{
	int i = 0;
	int j = 0;
	int a = 0;

	i = cub->first_line;
	while ( cub->map_arr[i])
	{
		j = 0;
		while (cub->map_arr[i][j])
		{
			if (cub->map_arr[i][j] == 'N' || cub->map_arr[i][j] == 'S' || cub->map_arr[i][j] == 'E' || cub->map_arr[i][j] == 'W')
				a++;
			else if (cub->map_arr[i][j] != '1' && cub->map_arr[i][j] != '0' && cub->map_arr[i][j] != ' ' && cub->map_arr[i][j] != '\n')
				return (1);
			j++;
		}
		i++;
	}
	if (a != 1)
	{
		printf("Error: multiple players or no player.\n");
		return 1;
	}
	return (ft_check_position(cub));
}
int convert_floor_color(t_cub3D *cub)
{
	cub->floor_color_int = malloc(sizeof(int) * 3);
	cub->floor_color_int[0] = ft_atoi(cub->floor_color_r);
	cub->floor_color_int[1] = ft_atoi(cub->floor_color_g);
	cub->floor_color_int[2] = ft_atoi(cub->floor_color_b);
	if (cub->floor_color_int[0] > 255 || cub->floor_color_int[1] > 255 || cub->floor_color_int[2] > 255)
	{
		printf("Error: wrong color format.\n");
		return 1;
	}
	if (cub->floor_color_int[0] < 0 || cub->floor_color_int[1] < 0 || cub->floor_color_int[2] < 0)
	{
		printf("Error: wrong color format.\n");
		return 1;
	}
	return 0;
}

int convert_ceiling_color(t_cub3D *cub)
{
	cub->ceiling_color_int = malloc(sizeof(int) * 3);
	cub->ceiling_color_int[0] = ft_atoi(cub->ceiling_color_r);
	cub->ceiling_color_int[1] = ft_atoi(cub->ceiling_color_g);
	cub->ceiling_color_int[2] = ft_atoi(cub->ceiling_color_b);
	if (cub->ceiling_color_int[0] > 255 || cub->ceiling_color_int[1] > 255 || cub->ceiling_color_int[2] > 255)
	{
		printf("Error: wrong color format.\n");
		return 1;
	}
	if (cub->ceiling_color_int[0] < 0 || cub->ceiling_color_int[1] < 0 || cub->ceiling_color_int[2] < 0)
	{
		printf("Error: wrong color format.\n");
		return 1;
	}
	return 0;
}
int ft_checkColor(char *str)
{
	int i = 0;
	int a = 0;
	if (!str)
		return 1;
	while (str[i])
	{
		if (str[i] == ',')
		{
			a++;
			i++;
		}
		if (!ft_isdigit(str[i]))
		{
			printf("Error: wrong color format.\n");
			return 1;
		}
		i++;
	}
	if (a != 2)
	{
		printf("Error: wrong color format.\n");
		return 1;
	}
	return 0;
}

int ft_colorParce(t_cub3D *cub)
{
	char **arr = NULL;
	char **arr2 = NULL;
	// printf("floor color: %s\n", cub->floor_color);
	// printf("ceiling color: %s\n", cub->ceiling_color);
	if (ft_checkColor(cub->floor_color) || ft_checkColor(cub->ceiling_color))
		return 1;
	arr = ft_split(cub->floor_color, ',');
	arr2 = ft_split(cub->ceiling_color, ',');
	cub->floor_color_r = arr[0];
	cub->floor_color_g = arr[1];
	cub->floor_color_b = arr[2];
	cub->ceiling_color_r = arr2[0];
	cub->ceiling_color_g = arr2[1];
	cub->ceiling_color_b = arr2[2];
	if (convert_floor_color(cub) || convert_ceiling_color(cub))
		return 1;
	return 0;
}

// int	exit_game(t_var *data)
// {
// 	if (data)
// 	{
// 		if (data->map_widths)
// 			free(data->map_widths);
// 		if (data->map)
// 			free(data->map);
// 	}
// 	exit(0);
// }

int is_valid_map( char *filename)
{
	t_var *data = malloc(sizeof(t_var));
	t_cub3D *cub = malloc(sizeof(t_cub3D));
	t_line *head = NULL;
	t_line *current = NULL;
	char *line = NULL;
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: could not open file.\n");
		return 0;
	}
	while ((line = get_next_line(fd)))
	{
		t_line *new_node = (t_line *)malloc(sizeof(t_line));
		new_node->line = (char *)malloc(ft_strlen(line) + 1); // +1 for null terminator
		new_node->line = ft_strdup(line);
		new_node->next = NULL;
		if (head == NULL) {
			head = new_node;
			current = new_node;
		} else {
			current->next = new_node;
			current = new_node;
		}
		free(line);
	}
	
	close(fd);
	t_line *tmp = head;
	cub->max_lenght = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->line) > cub->max_lenght)
			cub->max_lenght = ft_strlen(tmp->line);
		tmp = tmp->next;
	}
	tmp = head;
	if (ft_lsttoarray(head, cub))
		return (0);
	// ft_sortPathTexture(cub);
	if (ft_sortPathTexture(cub) || ft_checkIfClosed(cub, tmp) )
	{
		printf("Error: ddewdwedwedwedwedwdwed.\n");
		return (0);
	}
	if (ft_checkForMultipleMap(cub))
	{
		printf("Error: multiple maps.\n");
		return (0);
	}
	fill_map(cub, tmp);
	fill_map_back(cub, tmp);
	ft_lsttoarray(head, cub);
	if (ft_checkForSpaces(cub) || ft_countPathTexture(cub) || ft_checkForPlayer(cub) || ft_colorParce(cub))
	{
		printf("Error: map is not cdlosed.\n");
		return (0);
	}
	data = init_data(cub);
	if (data == NULL)
		return (1);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_release, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
	return 1;
}

