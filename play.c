/*
** play.c for philo in /home/erwan/Code/teck/C/PSU_2016_philo
** 
** Made by Simon
** Login   <erwan.simon@epitech.eu>
** 
** Started on  Fri Mar 10 16:37:26 2017 Simon
** Last update Sun Mar 19 13:08:31 2017 Simon
*/

#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

int		g_signal = -1;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	g_cond = PTHREAD_COND_INITIALIZER;
int		g_table = 0;

static void	wait_other(t_philo *philo)
{
  int		a;

  pthread_mutex_lock(&g_mutex);
  g_table = 1;
  pthread_mutex_unlock(&g_mutex);
  a = 0;
  while (a <= philo->max_philos)
    {
      pthread_join(philo->philos[a], NULL);
      a++;
    }
}

void	create_ress(int nb_philo, int nb_eat, t_philo *philo)
{
  int	a;

  a = 0;
  if ((philo->philos = malloc(sizeof(pthread_t) * nb_philo)) == NULL ||
      (philo->chops = malloc(sizeof(pthread_mutex_t) * nb_philo)) == NULL)
    my_exit(philo);
  philo->max_eat = nb_eat;
  philo->max_philos = nb_philo - 1;
  while (a <= philo->max_philos)
    {
      pthread_mutex_lock(&g_mutex);
      g_signal = 0;
      pthread_mutex_unlock(&g_mutex);
      philo->current = a;
      philo->chops[a] = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
      if (pthread_create(&philo->philos[a], NULL, do_so, philo))
	my_exit(philo);
      pthread_mutex_lock(&g_mutex);
      while (g_signal != -1)
	pthread_cond_wait(&g_cond, &g_mutex);
      pthread_mutex_unlock(&g_mutex);
      a++;
    }
  wait_other(philo);
}
