/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spoons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcomic <jcomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:35:45 by jcomic            #+#    #+#             */
/*   Updated: 2021/12/21 16:42:15 by jcomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_mutex_init(t_settings	*settings)
{
	settings->sp_status = pthread_mutex_init(&settings->mutex_sp, NULL);
	settings->pr_status = pthread_mutex_init(&settings->mutex_pr, NULL);
	if (settings->sp_status != 0 || settings->pr_status != 0)
		ft_abort_with_mutex_destroy(settings);
}

void	ft_phil_init(t_ph	*phil, t_settings	*settings)
{
	if (phil->id == 0)
		phil->right_i = settings->num;
	else
		phil->right_i = phil->id - 1;
	phil->left_i = phil->id;
	phil->lifetime = settings->die;
	phil->left_status = 0;
	phil->right_status = 0;
}

int	ft_check_spoon(t_ph *phil, t_settings *s)
{
	int	start;
	int	timer;

	if (phil->id == 0)
		phil->right_i = s->num;
	else
		phil->right_i = phil->id - 1;
	phil->left_i = phil->id;
	start = get_current_time_ms();
	while (phil->left_status != 1 || phil->right_status != 1)
	{
		if (s->spoons[phil->left_i] == 1 || s->spoons[phil->right_i] == 1)
			ft_take_both(phil, s);
		timer = get_current_time_ms() - start;
		if (timer > phil->lifetime || s->start != 1)
			return (0);
		usleep(100);
	}
	return (phil->lifetime - timer);
}

int	ft_take_both(t_ph *phil, t_settings *s)
{
	pthread_mutex_lock(&s->mutex_sp);
	if (s->spoons[phil->left_i] == 1 && s->spoons[phil->right_i] == 1)
	{
		s->spoons[phil->left_i] = 0;
		s->spoons[phil->right_i] = 0;
		pthread_mutex_unlock(&s->mutex_sp);
		phil->left_status = 1;
		phil->right_status = 1;
		ft_printer(phil->id, 1, s);
		ft_printer(phil->id, 1, s);
		return (1);
	}
	pthread_mutex_unlock(&s->mutex_sp);
	return (0);
}

void	ft_join_pthread(t_settings *settings, pthread_t thread_id)
{
	int	i;

	i = 0;
	while (i < settings->num)
	{
		pthread_join(&thread_id[i], NULL);
		i++;
	}
}
