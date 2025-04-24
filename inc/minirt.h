/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/04/24 20:11:28 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./struct.h"
# include "../lib/mlx_linux/mlx.h"
# include "../lib/libft/src/libft.h"
# include "../lib/gnl/get_next_line.h"

# define WIDTH 800
# define HEIGHT 600

int	ft_error(char *message);

int	ft_init_mlx(t_mlx *mlx);

#endif

