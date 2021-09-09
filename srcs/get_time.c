/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:50:09 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:50:09 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

unsigned int	get_time(unsigned int start_usec, unsigned int start_sec)
{
	struct timeval	current_time;
	int				sec;

	gettimeofday(&current_time, NULL);
	sec = current_time.tv_sec - start_sec;
	return (((unsigned int)(sec * 1000000 + current_time.tv_usec) - start_usec)
	/ 1);
}
