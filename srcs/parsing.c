/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:38:31 by MP9               #+#    #+#             */
/*   Updated: 2026/02/09 14:17:37 by MP9              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "includes/philosophers.h"

void check_input(char **input)
{
	int bi;
	int si;
	
	bi = 0;
	si = 0;
	while(input[bi] != NULL)
	{
		while(input[bi][si] != '\0')
		{
			if(ft_isalpha(input[bi][si]) == 1 || input[bi][si] == '-')
				error_exit(1);
			si++;
		}
		si = 0;
		bi++;
	}
}

void handle_input(t_table *table, char **input)
{
	check_input(input);
	table = malloc(sizeof(t_table) * 1);
	if (!table)
		error_exit(2);
	table->size = ft_atoi(input[0]);
	table->time_to_die = ft_atoi(input[1]);
	table->time_to_eat = ft_atoi(input[2]);
	table->time_to_sleep = ft_atoi(input[3]);
	if (input[4])
		table->max_meal = ft_atoi(input[4]);
	else
		table->max_meal = 0;
	
}
