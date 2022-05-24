/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcomic <jcomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:34:57 by jcomic            #+#    #+#             */
/*   Updated: 2021/12/21 16:34:59 by jcomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_settings	*ft_global_settings(int init)
{
	static t_settings	settings;

	if (init)
		settings = ft_init_settings();
	return (&settings);
}

t_settings	ft_init_settings(void)
{
	t_settings	settings;

	settings.num = 0;
	settings.die = 0;
	settings.eat = 0;
	settings.slp = 0;
	settings.goal = -1;
	settings.sp_status = -1;
	settings.pr_status = -1;
	settings.spoons = 0;
	settings.threads = 0;
	settings.start = 0;
	return (settings);
}

void	ft_check_finish(t_settings *settings)
{
	int	finished;
	int	i;

	if (settings->threads == NULL)
		return ;
	finished = 1;
	while (finished)
	{
		finished = 0;
		i = 0;
		while (i < settings->num)
		{
			if (settings->threads[i] == 1)
			{
				finished = 1;
				break ;
			}
			i++;
		}
		usleep(100000);
	}
}

void	ft_abort(t_settings *settings)
{
	free(settings->spoons);
	free(settings->threads);
	exit(0);
}

void	ft_abort_with_mutex_destroy(t_settings *settings)
{
	free(settings->spoons);
	free(settings->threads);
	if (settings->sp_status == 0)
		pthread_mutex_destroy(&settings->mutex_sp);
	if (settings->pr_status == 0)
		pthread_mutex_destroy(&settings->mutex_pr);
	exit(0);
}
