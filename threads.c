/*
** threads.c for philo in /home/erwan/Code/teck/C/PSU_2016_philo
** 
** Made by Simon
** Login   <erwan.simon@epitech.eu>
** 
** Started on  Tue Mar 14 21:05:58 2017 Simon
** Last update Sun Mar 19 13:07:45 2017 Simon
*/

#include <pthread.h>
#include <errno.h>
#include "extern.h"
#include "philo.h"

static void	left_free(pthread_mutex_t *left, pthread_mutex_t *right,
			  e_state *current_state, int *a)
{
  if (*current_state != EAT && pthread_mutex_trylock(right) != EBUSY)
    {
      lphilo_take_chopstick(left);
      lphilo_take_chopstick(right);
      lphilo_eat();
      lphilo_release_chopstick(right);
      lphilo_release_chopstick(left);
      *current_state = EAT;
      pthread_mutex_unlock(right);
      *a += 1;
    }
  else if (*current_state != THINK)
    {
      lphilo_take_chopstick(left);
      lphilo_think();
      lphilo_release_chopstick(left);
      *current_state = THINK;
    }
  pthread_mutex_unlock(left);
}

static void	chose_state(pthread_mutex_t *left, pthread_mutex_t *right,
			    e_state *current_state, int *a)
{
  if (pthread_mutex_trylock(left) != EBUSY)
    left_free(left, right, current_state, a);
  else if (pthread_mutex_trylock(right) != EBUSY)
    left_free(right, left, current_state, a);
  else if (*current_state == EAT)
    {
      *current_state = SLEEP;
      lphilo_sleep();
    }
}

static void	wait_for_death(pthread_mutex_t *left, pthread_mutex_t *right,
			       e_state current_state, t_philo *philo)
{
  int		a;

  if (current_state != EAT)
    {
      pthread_mutex_lock(left);
      pthread_mutex_lock(right);
      lphilo_take_chopstick(left);
      lphilo_take_chopstick(right);
      lphilo_eat();
      lphilo_release_chopstick(right);
      lphilo_release_chopstick(left);
      pthread_mutex_unlock(right);
      pthread_mutex_unlock(left);
    }
  a = 0;
  while (a < (((t_philo *) philo)->max_eat - 2))
    {
      lphilo_sleep();
      a++;
    }
  pthread_mutex_lock(&g_mutex);
  g_signal = 0;
  pthread_mutex_unlock(&g_mutex);
}

void			*do_so(void *philo)
{
  int			id;
  pthread_mutex_t	*right;
  pthread_mutex_t	*left;
  int			a;
  e_state		current_state;

  a = 0;
  id = ((t_philo *) philo)->current;
  pthread_mutex_lock(&g_mutex);
  g_signal = -1;
  pthread_cond_signal(&g_cond);
  pthread_mutex_unlock(&g_mutex);
  current_state = SLEEP;
  lphilo_sleep();
  left = &((t_philo *) philo)->chops[id];
  right = &((t_philo *) philo)->
    chops[(id == ((t_philo *) philo)->max_philos ? 0 : id + 1)];
  while (g_table != 1)
    ;
  while (a < (g_signal == 0 ? ((t_philo *) philo)->
	      max_eat - 1 : ((t_philo *) philo)->max_eat))
    chose_state(left, right, &current_state, &a);
  wait_for_death(left, right, current_state, philo);
  return (NULL);
}
