/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:50:13 by msedeno-          #+#    #+#             */
/*   Updated: 2026/02/14 21:58:57 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

/* ************************************************************************** */
/*                               DEFINES                                      */
/* ************************************************************************** */

# define PHILO_MAX 200
# define ERR_ARGS "Error: Invalid arguments\n"
# define ERR_MALLOC "Error: Malloc failed\n"
# define ERR_MUTEX "Error: Mutex initialization failed\n"
# define ERR_THREAD "Error: Thread creation failed\n"

// Colors
# define USE_COLORS 1
# if USE_COLORS
#  define RED "\033[0;31m"
#  define GREEN "\033[0;32m"
#  define YELLOW "\033[0;33m"
#  define ORANGE "\033[38;5;208m"
#  define BLUE "\033[0;34m"
#  define CYAN "\033[0;36m"
#  define RESET "\033[0m"
# else
#  define RED ""
#  define GREEN ""
#  define YELLOW ""
#  define ORANGE ""
#  define BLUE ""
#  define CYAN ""
#  define RESET ""
# endif

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	int				is_eating;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				mutex_count;
	int				fork_mut_count;

	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				has_num_must_eat;
	int				simulation_stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;

typedef enum s_err
{
	FALSE,
	TRUE,
}			t_err;

/* ************************************************************************** */
/*                            FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

/* ========================================== */
/*               Args_init.c                  */
/* ========================================== */

/**
 * @brief Validates the input arguments to ensure they are valid integers.
 * @param ac Argument count.
 * @param av Argument vector.
 * @return TRUE if an error occurs, FALSE otherwise.
 */
int			parse_args(int ac, char **av);

/**
 * @brief Initializes the main data structure with the provided arguments.
 * @param data Pointer to the shared data structure.
 * @param ac Argument count.
 * @param av Argument vector.
 */
void		init_data(t_data *data, int ac, char **av);

/**
 * @brief Allocates memory for philosophers and assigns forks to them.
 * @param data Pointer to the shared data structure.
 */
void		init_philo(t_data *data);

/**
 * @brief Initializes all necessary mutexes (forks, write, meal, death).
 * @param data Pointer to the shared data structure.
 * @return 0 on success, non-zero on failure.
 */
int			init_mutex(t_data *data);


/* ========================================== */
/*               Args_utils.c                 */
/* ========================================== */

/**
 * @brief Checks if a character is a whitespace.
 * @param c The character to check.
 * @return 1 if true, 0 otherwise.
 */
int			ft_isspace(int c);

/**
 * @brief Checks if a character is a numeric digit.
 * @param n The character code to check.
 * @return 1 if true, 0 otherwise.
 */
int			ft_isdigit(int n);

/**
 * @brief Converts a string to an integer with strict error checking.
 * @param str The string to convert.
 * @return The converted integer, or -1 on error/overflow.
 */
int			ft_atoi_strict(const char *str);

/**
 * @brief Locates the first occurrence of string `finder` in `s`.
 * @param s The string to be searched.
 * @param finder The substring to search for.
 * @return 0 if found, 1 if not found (custom non-standard return).
 */
int			ft_strstr(char *s, char *finder);

/**
 * @brief Returns the ANSI color code corresponding to a status message.
 * @param status The status message string.
 * @return The color string.
 */
char		*get_color(char *status);


/* ========================================== */
/*               Big_sister.c                 */
/* ========================================== */

/**
 * @brief Thread-safe update of the simulation stop flag.
 * @param data Pointer to the shared data structure.
 * @param value The value to set (0 or 1).
 */
void		set_sim_stop(t_data *data, int value);

/**
 * @brief Monitor thread routine checking for deaths or completed meals.
 * @param arg Pointer to the shared data structure.
 * @return NULL.
 */
void		*big_sister(void *arg);

/**
 * @brief Checks if all philosophers have eaten the required number of times.
 * @param data Pointer to the shared data structure.
 * @return 1 if all finished, 0 otherwise.
 */
int			is_all_ate_enough(t_data *data);

/* ========================================== */
/*               Errors_free.c                */
/* ========================================== */

/**
 * @brief Prints the program usage guide to stdout.
 */
void		error(void);

/**
 * @brief Destroys all initialized mutexes to prevent resource leaks.
 * @param data Pointer to the shared data structure.
 */
void		destroy_mutex(t_data *data);

/**
 * @brief Frees all allocated memory and destroys mutexes.
 * @param data Pointer to the shared data structure.
 */
void		free_the_chain(t_data *data);

/**
 * @brief Wrapper to free resources and print "error" message using printf.
 * @param data Pointer to the shared data structure.
 */
void		msg_error(t_data *data);


/* ========================================== */
/*                 Main.c                     */
/* ========================================== */

/**
 * @brief Orchestrates the simulation startup, execution, and cleanup.
 * @param data Pointer to the shared data structure.
 * @param ac Argument count.
 * @param av Argument vector.
 */
void		philos_at_table(t_data *data, int ac, char **av);

/**
 * @brief Main entry point of the philosopher program.
 */
int			main(int ac, char **av);


/* ========================================== */
/*               Routine.c                    */
/* ========================================== */

/**
 * @brief Creates a POSIX thread for each philosopher.
 * @param data Pointer to the shared data structure.
 */
void		create_threads(t_data *data);

/**
 * @brief Joins all philosopher threads, waiting for their completion.
 * @param data Pointer to the shared data structure.
 */
void		wait_threads(t_data *data);

/**
 * @brief Handles the special case simulation for a single philosopher.
 * @param philo Pointer to the philosopher struct.
 * @return NULL.
 */
void		*one_philo(t_philo *philo);

/**
 * @brief The main life cycle loop for a philosopher (Eat, Sleep, Think).
 * @param arg Pointer to the philosopher struct.
 * @return NULL.
 */
void		*philo_routine(void *arg);

/**
 * @brief Safely checks the simulation stop flag with a mutex.
 * @param philo Pointer to the philosopher struct.
 * @return The value of simulation_stop.
 */
int			should_stop(t_philo *philo);

/**
 * @brief Thread entry point wrapper to route to single or multi routine.
 * @param arg Pointer to the philosopher struct.
 * @return NULL.
 */
void		*routine(void *arg);

/* ========================================== */
/*            Routine_utils.c                 */
/* ========================================== */

/**
 * @brief Gets the current time in milliseconds since the Epoch.
 * @return Time in milliseconds.
 */
long long	get_time(void);

/**
 * @brief Prints a timestamped status message in a thread-safe manner.
 * @param philo Pointer to the philosopher struct.
 * @param status Description of the action ("is eating", etc.).
 * @param force_print If true, prints even if simulation has stopped (for death).
 * @return 0 on success, 1 if mutex fails or simulation stopped.
 */
int			print_status(t_philo *philo, char *status, int force_print);

/**
 * @brief Checks if a specific philosopher has died of starvation.
 * @param philo Pointer to the philosopher struct.
 * @return 1 if died, 0 otherwise.
 */
int			check_death(t_philo *philo);

/**
 * @brief High-precision sleep function that checks for simulation stop.
 * @param t_ms Time to sleep in milliseconds.
 * @param philo Pointer to the philosopher struct.
 */
void		ft_usleep(long long t_ms, t_philo *philo);


/* ========================================== */
/*                Table.c                     */
/* ========================================== */

/**
 * @brief Locks the left and right forks in an order that prevents deadlocks.
 * @param philo Pointer to the philosopher struct.
 */
void		take_forks(t_philo *philo);

/**
 * @brief Unlocks both forks held by the philosopher.
 * @param philo Pointer to the philosopher struct.
 */
void		drop_forks(t_philo *philo);

/**
 * @brief Execution of the eating action: take forks, update time, eat, drop.
 * @param philo Pointer to the philosopher struct.
 */
void		philo_eat(t_philo *philo);

/**
 * @brief Execution of the sleeping action.
 * @param philo Pointer to the philosopher struct.
 */
void		philo_sleep(t_philo *philo);

/**
 * @brief Execution of the thinking action (printing status).
 * @param philo Pointer to the philosopher struct.
 */
void		philo_think(t_philo *philo);

#endif
