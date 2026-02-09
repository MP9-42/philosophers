/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:24:46 by MP9               #+#    #+#             */
/*   Updated: 2026/02/09 14:54:44 by MP9              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philosophers.h"

int main(int argc, char **argv)
{
	t_table	table;
	if (argc < 5 || argc > 6)
		error_exit(0);
	handle_input(&table, &argv[1]);
	return(0);
}