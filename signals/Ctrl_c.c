/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:59:26 by kahmada           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/15 14:20:15 by kahmada          ###   ########.fr       */
=======
/*   Updated: 2024/09/15 13:39:31 by chourri          ###   ########.fr       */
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int s)
{
	char	*ex;

	(void)s;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ex = manage_exit_status(1, 1);
	free (ex);
}
