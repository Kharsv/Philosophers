/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcomic <jcomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:35:36 by jcomic            #+#    #+#             */
/*   Updated: 2021/12/21 16:41:28 by jcomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_time_calc(t_settings *settings)
{
	int	time;

	time = get_current_time_ms() - settings->time_start;
	return (time);
}

long	get_current_time_ms(void)
{
	struct timeval	t;
	long			time_ms;

	gettimeofday(&t, NULL);
	time_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time_ms);
}

int	ft_set_timer(int time, t_ph *phil, t_settings *settings)
{
	if (phil->lifetime - time <= 0)
	{
		usleep(phil->lifetime * 1000);
		ft_printer(phil->id, 5, settings);
		return (1);
	}
	phil->lifetime = phil->lifetime - time;
	usleep(time * 1000);
	return (0);
}

void	ft_printer(int name, int stage, t_settings *settings)
{
	name++;
	pthread_mutex_lock(&settings->mutex_pr);
	if (settings->start == 1)
	{
		if (stage == 1)
			printf("%d %d has taken a fork\n", ft_time_calc(settings), name);
		else if (stage == 2)
			printf("%d %d is eating\n", ft_time_calc(settings), name);
		else if (stage == 3)
			printf("%d %d is sleeping\n", ft_time_calc(settings), name);
		else if (stage == 4)
			printf("%d %d is thinking\n", ft_time_calc(settings), name);
		else if (stage == 5)
		{
			printf("%d %d died\n", ft_time_calc(settings), name);
			settings->start = -1;
		}
	}
	pthread_mutex_unlock(&settings->mutex_pr);
}

void	ft_print_error(int er_no)
{
	if (er_no == 1)
		write(1, "need 4 or 5 arguments\n", 22);
	if (er_no == 2)
		write(1, "memory allocation error\n", 24);
	if (er_no == 3)
		write(1, "more 199 philosophers?!\n", 24);
	if (er_no == 4)
		write(1, "invalid argument\n", 17);
	if (er_no == 5)
		write(1, "error thread create\n", 20);
	if (er_no == 6)
		write(1, "error thread join\n", 18);
	if (er_no == 7)
		write(1, "error mutex init\n", 17);
	if (er_no == 8)
		write(1, "error mutex destroy\n", 20);
	exit(1);
}
