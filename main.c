/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcomic <jcomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:35:22 by jcomic            #+#    #+#             */
/*   Updated: 2021/12/21 16:45:22 by jcomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_eating(t_ph *phil, t_settings *s, int goal)
{
	ft_phil_init(phil, s);
	while (s->start == 1)
	{
		phil->lifetime = ft_check_spoon(phil, s);
		if (phil->lifetime < 0)
			ft_printer(phil->id, 5, s);
		phil->lifetime = s->die;
		ft_printer(phil->id, 2, s);
		if (ft_set_timer(s->eat, phil, s))
			break ;
		s->spoons[phil->left_i] = 1;
		s->spoons[phil->right_i] = 1;
		phil->left_status = 0;
		phil->right_status = 0;
		if (goal == 0)
			break ;
		else if (goal > 0)
			goal--;
		ft_printer(phil->id, 3, s);
		if (ft_set_timer(s->slp, phil, s))
			break ;
		ft_printer(phil->id, 4, s);
		if (ft_set_timer((s->die - s->slp - s->eat) / 2, phil, s))
			break ;
	}
}

void	*ft_simulation(void *name)
{
	t_ph		phil;
	t_settings	*s;

	phil = *(t_ph *)name;
	s = ft_global_settings(0);
	if (s->num > 1)
		ft_eating(&phil, s, s->goal);
	s->threads[phil.id] = 0;
	return (NULL);
}

void	ft_read_args(t_settings *s, int argc, char **argv)
{
	int	i;

	s->num = ft_atoi(argv[1]);
	s->die = ft_atoi(argv[2]);
	s->eat = ft_atoi(argv[3]);
	s->slp = ft_atoi(argv[4]);
	if (argc == 6)
		s->goal = ft_atoi(argv[5]);
	if (s->num <= 0 || s->die <= 0 || s->eat <= 0 || s->slp <= 0)
		ft_print_error(4);
	s->spoons = malloc(sizeof(int ) * s->num);
	s->threads = malloc(sizeof(int ) * s->num);
	if (s->spoons == NULL || s->threads == NULL)
		ft_abort(s);
	i = 0;
	while (i < s->num)
	{
		s->spoons[i] = 1;
		s->threads[i] = 0;
		i++;
	}
}

void	ft_if_one_philosoph(t_settings	*settings)
{
	if (settings->num == 1)
	{
		usleep(settings->die);
		printf("%d 1 is dead\n", settings->die);
		ft_abort_with_mutex_destroy(settings);
	}
	if (settings->num > 199)
	{
		write(1, "more 199 philosophers\n", 22);
		ft_abort_with_mutex_destroy(settings);
	}
}

int	main(int argc, char **argv)
{
	pthread_t	thread_id;
	t_settings	*settings;
	int			name;
	int			i;

	if (argc < 5 || argc > 6)
		ft_print_error(1);
	settings = ft_global_settings(1);
	ft_read_args(settings, argc, argv);
	ft_mutex_init(settings);
	ft_if_one_philosoph(settings);
	settings->start = 1;
	settings->time_start = get_current_time_ms();
	i = 0;
	while (i < settings->num)
	{
		name = i;
		pthread_create(&thread_id, NULL, &ft_simulation, &name);
		usleep(1000);
		settings->threads[i] = 1;
		i++;
	}
	ft_check_finish(settings);
	ft_join_pthread(settings, thread_id);
	ft_abort_with_mutex_destroy(settings);
}
