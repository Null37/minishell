/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mor_fun_env_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:21:56 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/26 18:22:16 by ssamadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

void	free_no(t_norm	*norm)
{
	free(norm->varibale);
	free(norm->ef);
	free(norm);
}