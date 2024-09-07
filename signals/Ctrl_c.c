/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:59:26 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/03 18:24:06 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	SIGINT_handler(int s)
{
	(void)s;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	SIGQUIT_handler(int signal)
{
	(void)signal;
	write(2, "\n^\\QUIT: 3\n",11);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
