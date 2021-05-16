/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssamadi <ssamadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 13:31:12 by ssamadi           #+#    #+#             */
/*   Updated: 2021/05/16 10:40:10 by ssamadi          ###   ########.fr       */
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

char	**edit_envp_shlvl(char **envp_c)
{
	char	*sh;
	char *tmp;
	char	*newsh;
	int		lenp;
	int		j;
	int		t;
	int		i;
	int		tee;

	sh = search_in_env2("SHLVL", envp_c);
	newsh = ft_itoa(ft_atoi(sh) + 1);
	lenp = len_of_args(envp_c);
	tee = 0;
	t = ft_strlen(newsh);
	i = -1;
	while(++i < lenp)
	{
		tmp = get_env_name(envp_c[i]);
		if (my_strcmp(tmp, "SHLVL") == 0)
		{
			j = 0;
			while (envp_c[i][j])
			{
				if(envp_c[i][j] == '=')
				{
					j += 1;
					while(tee != t)
					{
						envp_c[i][j] = newsh[tee];
						j++;
						tee++;
					}
					envp_c[i][j] ='\0';
					free(tmp);
					free(newsh);
					return (envp_c);
				}
				j++;
			}	
		}
		free(tmp);
	}
	free(newsh);
	return (envp_c);
}
