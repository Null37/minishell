/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouibao <fbouibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:31:12 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/27 20:17:08 by fbouibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

char	*get_env_name(char *envp)
{
	int		b;
	int		c;
	char	*varibale;

	b = 0;
	c = 0;
	while (envp[b])
	{
		if (envp[b] == '=')
			break ;
		b++;
	}
	varibale = malloc(sizeof(char) * b + 1);
	while (c != b)
	{
		varibale[c] = envp[c];
		c++;
	}
	varibale[c] = '\0';
	return (varibale);
}

char	**copy_envp(char **envp_l)
{
	char	**tmpr;
	int		lenp;
	int		z;

	lenp = len_of_args(envp_l);
	tmpr = malloc(sizeof(char *) * (lenp + 1));
	tmpr[lenp] = NULL;
	z = -1;
	while (envp_l[++z])
	{
		tmpr[z] = ft_strdup(envp_l[z]);
	}
	return (tmpr);
}

char	**half_edit_envp(char **envp_c, t_norm norm)
{
	int	j;

	j = 0;
	while (envp_c[norm.i][j])
	{
		if (envp_c[norm.i][j] == '=')
		{
			j += 1;
			while (norm.tee != norm.t)
			{
				envp_c[norm.i][j] = norm.newsh[norm.tee];
				j++;
				norm.tee++;
			}
			envp_c[norm.i][j] = '\0';
			free(norm.n_tmp);
			return (envp_c);
		}
		j++;
	}
	return (envp_c);
}

char	**edit_envp_shlvl(char **envp_c)
{
	int		lenp;
	t_norm	norm;

	norm.sh = search_in_env2("SHLVL", envp_c);
	if (norm.sh == NULL)
		return (NULL);
	norm.newsh = ft_itoa(ft_atoi(norm.sh) + 1);
	free(norm.sh);
	lenp = len_of_args(envp_c);
	norm.tee = 0;
	norm.t = ft_strlen(norm.newsh);
	norm.i = -1;
	while (++norm.i < lenp)
	{
		norm.n_tmp = get_env_name(envp_c[norm.i]);
		if (my_strcmp(norm.n_tmp, "SHLVL") == 0)
		{
			envp_c = half_edit_envp(envp_c, norm);
			free(norm.newsh);
			return (envp_c);
		}
		free(norm.n_tmp);
	}
	free(norm.newsh);
	return (envp_c);
}
