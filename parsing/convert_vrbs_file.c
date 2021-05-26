/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_vrbs_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:37:01 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/26 19:43:54 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

int	norm_cnvr_vbs(int *bl, char *cmds, t_env *evp, t_tmp *tmp)
{
	if (*bl == 0 && cmds[tmp->i] == '\\' && cmds[tmp->i + 1] == '$')
	{
		tmp->rstr = ft_strjoinchar(tmp->rstr, '\\');
		tmp->rstr = ft_strjoinchar(tmp->rstr, '$');
		tmp->i++;
		return (1);
	}
	if (*bl == 0 && cmds[tmp->i] == '$' && cmds[tmp->i + 1] == '?')
	{
		tmp->ss = ft_itoa(g_all->staus_code);
		tmp->rstr = ft_strjoin1(tmp->rstr, tmp->ss);
		free(tmp->ss);
		tmp->i++;
	}
	else if (*bl == 0 && cmds[tmp->i] == '$')
		tmp->rstr = add_vrbs(evp->my_env, tmp->rstr, tmp, cmds);
	else
		tmp->rstr = ft_strjoinchar(tmp->rstr, cmds[tmp->i]);
	return (0);
}

char	*convert_vrbs(char *cmds, t_env *evp)
{
	t_tmp	*tmp;
	int		bl;

	bl = 0;
	tmp = malloc(sizeof(t_tmp));
	tmp->rstr = ft_strdup("");
	tmp->i = -1;
	while (cmds[++tmp->i])
	{
		if (bl == 0 && cmds[tmp->i] == '\''
			&& (tmp->i == 0 || cmds[tmp->i - 1] != '\\'))
			bl = 1;
		else if (bl == 1 && cmds[tmp->i] == '\'')
			bl = 0;
		if (norm_cnvr_vbs(&bl, cmds, evp, tmp) == 1)
			continue ;
	}
	cmds = tmp->rstr;
	free(tmp);
	return (cmds);
}
