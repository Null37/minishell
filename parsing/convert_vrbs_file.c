/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_vrbs_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:37:01 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/28 16:15:46 by ssamadi          ###   ########.fr       */
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

void	half_convert(int *bl, t_tmp	**tmp)
{
	*bl = 0;
	*tmp = malloc(sizeof(t_tmp));
	(*tmp)->rstr = ft_strdup("");
	(*tmp)->i = -1;
}

char	*convert_vrbs(char *cmds, t_env *evp)
{
	t_tmp	*tmp;
	int		bl;

	half_convert(&bl, &tmp);
	while (cmds[++tmp->i])
	{
		if (cmds[tmp->i] == '\\')
		{
			tmp->rstr = ft_strjoinchar(tmp->rstr, '\\');
			tmp->rstr = ft_strjoinchar(tmp->rstr, cmds[tmp->i + 1]);
			(tmp->i)++;
			continue ;
		}
		if (bl == 0 && cmds[tmp->i] == '\'')
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
