#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "extern.h"
#include "philo.h"

void	my_exit(t_philo *philo)
{
  if (philo != NULL)
    {
      if (philo->philos != NULL)
  	free(philo->philos);
      if (philo->chops != NULL)
  	free(philo->chops);
      free(philo);
    }
  RCFCleanup();
  exit(84);
}

int	check(int ac, char **av, int *nb_philos, int *nb_eat)
{
  if (ac != 5
      || strcmp(av[(strcmp(av[1], "-p") == 0 ? 3 : 1)], "-p") == 0
      || strcmp(av[(strcmp(av[1], "-e") == 0 ? 3 : 1)], "-e") == 0
      || atoi(av[2]) <= 0 || atoi(av[4]) <= 0)
    {
      fprintf(stderr, "Wrong parameters\nUsage: ./philo -p 3 -e 2");
      return (84);
    }
  if (strcmp(av[1], "-p") == 0)
    {
      if ((*nb_philos = atoi(av[2])) == 1)
	return (84);
      *nb_eat = atoi(av[4]);
    }
  else
    {
      if ((*nb_philos = atoi(av[4])) == 1)
	return (84);
      *nb_eat = atoi(av[2]);
    }
  return (0);
}

int		main(int ac, char **av)
{
  t_philo	*philo;
  int		nb_philos;
  int		nb_eat;

  RCFStartup(ac, av);
  if (check(ac, av, &nb_philos, &nb_eat) == 84 ||
      (philo = malloc(sizeof(t_philo))) == NULL)
    return (84);
  create_ress(nb_philos, nb_eat, philo);
  if (philo != NULL)
    {
      if (philo->philos != NULL)
  	free(philo->philos);
      if (philo->chops != NULL)
  	free(philo->chops);
      free(philo);
    }
  RCFCleanup();
  return (0);
}
