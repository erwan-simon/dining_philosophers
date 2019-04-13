#ifndef PHILO_H_
# define PHILO_H_

typedef	enum {
  THINK,
  EAT,
  SLEEP
}	e_state;

typedef struct		s_philo {
  pthread_t		*philos;
  pthread_mutex_t	*chops;
  int			max_philos;
  int			max_eat;
  int			current;
}			t_philo;

void			create_ress(int, int, t_philo *);
void			my_exit(t_philo *);
void			*do_so(void *);

extern int		g_signal;
extern pthread_mutex_t	g_mutex;
extern pthread_cond_t	g_cond;
extern int		g_table;

#endif /* ! PHILO_H_ */
