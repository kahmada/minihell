/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:59:26 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/14 10:21:08 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	SIGINT_handler(int s)
{
	char * ex;
	(void)s;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ex = manage_exit_status(1, 1);
	free (ex);
}
// void	SIGQUIT_ignore(int sig)
// {
// 	(void)sig;
// 	write(2, "\n^\\QUIT: 3\n",11);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }
