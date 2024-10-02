/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:59:26 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/01 18:41:24 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int s)
{
	char	*ex;

	(void)s;
	write(2, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	ex = manage_exit_status(1, 1);
	free (ex);
}
