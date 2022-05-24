/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcomic <jcomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:35:16 by jcomic            #+#    #+#             */
/*   Updated: 2021/12/21 16:37:43 by jcomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_settings
{
	int				num;
	int				die;
	int				eat;
	int				slp;
	int				goal;
	pthread_mutex_t	mutex_sp;
	pthread_mutex_t	mutex_pr;
	int				sp_status;
	int				pr_status;
	int				time_start;
	int				*spoons;	
	int				*threads;
	int				start;
}					t_settings;
typedef struct s_ph
{
	int				id;
	long			time_start;
	int				lifetime;
	int				left_i;
	int				left_status;
	int				right_i;
	int				right_status;
}t_ph;
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
t_settings	*ft_global_settings(int init);
t_settings	ft_init_settings(void);
void		ft_abort(t_settings *settings);
void		ft_abort_with_mutex_destroy(t_settings *settings);
void		ft_check_finish(t_settings *settings);
void		ft_printer(int name, int stage, t_settings *settings);
void		ft_print_error(int er_no);
int			ft_time_calc(t_settings *settings);
long		get_current_time_ms(void);
int			ft_set_timer(int time, t_ph *phil, t_settings *settings);
int			ft_check_spoon(t_ph *phil, t_settings *s);
int			ft_take_both(t_ph *phil, t_settings *settings);
void		ft_mutex_init(t_settings *settings);
void		ft_phil_init(t_ph *phil, t_settings *settings);
void		ft_join_pthread(t_settings *settings, pthread_t thread_id);
#endif
