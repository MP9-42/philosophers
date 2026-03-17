/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:24:46 by MP9               #+#    #+#             */
/*   Updated: 2026/03/17 21:07:30 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		error_exit(0, NULL);
	ft_memset(&table, 0, sizeof(t_table));
	handle_input(&table, &argv[1]);
	init_philos(&table);
	kill_threads(&table);
	free_all(&table);
	return (0);
}
